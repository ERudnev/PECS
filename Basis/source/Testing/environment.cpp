#include <Basis/Testing/environment.h>

#include <chrono>
#include <map>

#include <Basis/logger.h>

namespace basis::testing {

	Logger logger("tests");

	struct Result {
		bool passed = false;
		std::chrono::duration<long, std::micro> timeSpent;
	};

	std::map<std::string, Result> test_results;


	Statistics::Statistics()
	{
		test_results.clear();
	}

	Statistics::~Statistics()
	{
		std::vector<std::string> failedList;
		std::vector<std::string> goodList;
		for (const auto& result : test_results)
		{
			if (not result.second.passed)
				failedList.push_back(result.first);
			else
				goodList.push_back(result.first);
		}

		logger.print("\n...all tests done");
		if (failedList.empty())
		{
			logger.print("OK: All tests passed, exiting...");
		}
		else
		{
			logger.print(std::format("FAILED: {} tests:", failedList.size()));
			for (const auto& failed : failedList)
				logger.print(std::format("name: \"{}\"", failed));
		}
	}

	void doTest(const std::string& name, void (*func)(void))
	{
		try {
			logger.print(std::format("Running test \"{}\"", name));
			test_results[name].passed = true;
			const auto before = std::chrono::high_resolution_clock::now();
			func();
			const auto after = std::chrono::high_resolution_clock::now();
			//const std::chrono::duration<long, std::milli> timePassed = (after - before);
			const auto res = std::chrono::duration_cast<std::chrono::microseconds>(after - before);
			test_results[name].timeSpent = res;
			logger.print(std::format("...test is done at {}", res));
		}
		catch (std::exception& e) {
			test_results[name].passed = false;
			logger.print(std::format("...FAILED: \"{}\" : {}", name, e.what()));
		}
	}


}