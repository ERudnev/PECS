#pragma once

#include <string>

#define _INCOMPLETE_ common::defaultLogger.print(__FUNCTION__" incomplete");

namespace basis {

	struct Logger {
		const std::string prefix;

		void print(const std::string& message) const;
		void error(const std::string& message) const;
		void critical(const std::string& message) const;

	private:
		void printInternal(const std::string& message, const std::string& severity) const;
	};

	inline static Logger defaultLogger{ "log" };
}