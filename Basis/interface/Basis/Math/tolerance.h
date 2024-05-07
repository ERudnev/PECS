#pragma once

namespace basis::math {

	inline constexpr double tolerance = 0.0000001;

	template<typename FloatingType>
	bool equal(FloatingType a, FloatingType b) { return std::abs(a - b) < static_cast<FloatingType>(tolerance); }
};