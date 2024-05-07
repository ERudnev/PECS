#pragma once

#include <format>
#include <Basis/Math/tolerance.h>

namespace basis::testing {

	template<typename T>
	std::string type_decoration(const T& value) {
		return to_string(value);
	}

	template<>
	inline std::string type_decoration<std::string>(const std::string& value) {
		return std::format("\"{}\"", value);
	}

#define TEST(x) basis::testing::doTest(#x, x);
	//#define EXPECT_EQ(x,y) { if (not common::testing::compare_operation(x, y)) throw std::logic_error(std::format("check \"{} == {}\" failed with {} != {}", #x, #y, common::testing::type_decoration(x), common::testing::type_decoration(y))); }
#define EXPECT_EQ(x,y) { if (not basis::testing::compare_operation(x, y)) throw std::logic_error(std::format("check \"{} == {}\" failed with {} != {}", #x, #y, common::testing::type_decoration(x), common::testing::type_decoration(y))); }


	struct Statistics {
		Statistics();
		~Statistics();
	};

	void doTest(const std::string& name, void(*func)(void));

	// wrapping comparison
	template<typename T, typename K>
	bool compare_operation(const T& lhs, const K& rhs) { return lhs == rhs; }

	template<typename T>
	requires std::is_floating_point<T>
	bool compare_operation(const float& lhs, const float& rhs) { return basis::math::equal<T>(lhs, rhs); }

}