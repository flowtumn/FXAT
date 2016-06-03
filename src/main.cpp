#include <array>
#include <iostream>
#include <tuple>
#include <functional>
#include <fstream>
#include <regex>
#include <sstream>

#include "define.h"
#include "fx/algorithm/RateStrategy.h"
#include "fx/data/FXInfo.h"
#include "fx/client/EvaluateStrategyClient.h"

#if defined(UNICODE) || defined(_UNICODE)
  #define _tmain	wmain
  #define err		std::wcerr
#else
  #define _tmain	main
  #define err		std::cerr
#endif

namespace {
	const auto SIMULATION_HIGH_RATE = 0.3;
	const auto SIMULATION_LOW_RATE = 0.3;
	const auto RATE_OPEN = 1;
	const auto RATE_LOW = 2;
	const auto RATE_HIGH = 3;
	const auto RATE_CLOSE = 4;
};

/**
 * split
 */
std::vector <std::string> split(const std::string& s, std::string::value_type ch) {
	std::vector <std::string> r;
	std::string tmp;

	for (auto&& each : s) {
		if (ch != each) {
			tmp += each;
		} else {
			r.emplace_back(tmp);
			tmp.erase();
		}
	}

	if (!tmp.empty()) {
		r.emplace_back(tmp);
	}

	return r;
}

/**
 * FXInfoへConvert
 */
flowTumn::FXInfo convert(const std::string& s) {
	auto r = split(s, ',');
	return flowTumn::factoryFXInfo(
		std::atof(r.at(RATE_OPEN).data()),
		std::atof(r.at(RATE_CLOSE).data()),
		std::atof(r.at(RATE_HIGH).data()),
		std::atof(r.at(RATE_LOW).data())
	);
}

/**
 * 過去のデータを用いてsimulationを実施する。
 */
void simulation(const flowTumn::tstr& csv) {
	flowTumn::EvaluateStrategyClient <flowTumn::RateStrategy> evaluate(SIMULATION_HIGH_RATE, SIMULATION_LOW_RATE);
	std::ifstream iif(csv);

	if (iif.good()) {
		while (!iif.eof()) {
			std::string lineBuffer;
			if (std::getline(iif, lineBuffer)) {
				auto r = convert(lineBuffer);
				evaluate.simulation(
					flowTumn::factoryFXBidAsk(r.rateOpen, r.rateOpen)
				);
			}
		}

		std::cout << " totalBuy: " << evaluate.operationBuy() << std::endl;
		std::cout << " sellHigh: " << evaluate.operationSellHigh() << std::endl;
		std::cout << "  sellLow: " << evaluate.operationSellLow() << std::endl;
		std::cout << "  profit: " << evaluate.profit() << std::endl;
		std::cout << "highPercent: " << evaluate.highPercent() << std::endl;
		std::cout << "lowPercent: " << evaluate.lowPercent() << std::endl;
	}
}

int _tmain(int argc, flowTumn::tstr::value_type** argv) {

	if (2 == argc) {
		simulation(argv[1]);
	}

	return 0;

}
