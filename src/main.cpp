#include <array>
#include <iostream>
#include <map>
#include <tuple>
#include <functional>
#include <fstream>
#include <regex>
#include <sstream>
#include <unordered_map>

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
	//スプレッド(5銭)
	const auto BID_SPREAD = 0.05;

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
	auto v = flowTumn::factoryFXInfo(
		std::atof(r.at(RATE_OPEN).data()),
		std::atof(r.at(RATE_CLOSE).data()),
		std::atof(r.at(RATE_HIGH).data()),
		std::atof(r.at(RATE_LOW).data())
	);
	v.description = r.at(0);
	return v;
}

/**
 * 過去のデータを用いてsimulationを実施する。
 */
void simulation(const flowTumn::tstr& csv, double H, double L) {

	struct simulationRepository : flowTumn::IFXRepository {
		std::string convDate(const std::string& s) {
			auto r = split(s, '/');
			return r[0] + "-" + r[1];
		}

		//記録を更新。
		void updateRecord(double rate, const std::string& description) {
			int64_t i;
			double v;
			auto s = convDate(description);

			std::tie(i, v) = this->record_[s];
			++i;
			v += rate;
			this->record_[s] = std::make_tuple(i, v);
		}

		void bought(double rate, uint32_t, const std::string& description) override {
			this->updateRecord(rate, description);
			//std::cout << "[B] " << rate << "  " << description << std::endl;
		}

		void sold(double rate, uint32_t, const std::string& description) override {
			this->updateRecord(rate * -1.0, description);
			//std::cout << "[S] " << rate << "  " << description << std::endl;
		}

		void dumpRecord() {
			std::map<std::string, std::tuple <int64_t, double>> ordered(record_.begin(), record_.end());
			for (auto&& each : ordered) {
				int64_t v;
				double total;
				std::tie(v, total) = each.second;
				std::cout << each.first << ": " << " numberTimes: " << v << "   profit: " << total << std::endl;
			}
		}

	private:

		std::unordered_map <std::string, std::tuple <int64_t, double>> record_;
	};

	flowTumn::EvaluateStrategyClient <
		flowTumn::RateStrategy,
		simulationRepository
	> evaluate(H, L);

	std::ifstream iif(csv);

	if (iif.good()) {
		evaluate.info();
		while (!iif.eof()) {
			std::string lineBuffer;
			if (std::getline(iif, lineBuffer)) {
				auto r = convert(lineBuffer);
				evaluate.simulation(
					//始値が買値、始値にBID_SPREADを引いたのが売値
					flowTumn::factoryFXBidAsk(r.rateOpen, r.rateOpen - BID_SPREAD),
					r.description
				);
			}
		}

		std::cout << " totalBuy: " << evaluate.operationBuy() << std::endl;
		std::cout << " sellHigh: " << evaluate.operationSellHigh() << std::endl;
		std::cout << "  sellLow: " << evaluate.operationSellLow() << std::endl;
		std::cout << "  profit: " << evaluate.profit() << std::endl;
		std::cout << "highPercent: " << evaluate.highPercent() << std::endl;
		std::cout << "lowPercent: " << evaluate.lowPercent() << std::endl;
		std::cout << "------------------------" << std::endl;

		dynamic_cast <simulationRepository&> (evaluate.repository()).dumpRecord();
	}
}

int _tmain(int argc, flowTumn::tstr::value_type** argv) {

	if (4 == argc) {
		simulation(argv[1], flowTumn::toDouble(argv[2]), flowTumn::toDouble(argv[3]));
	}

	return 0;

}
