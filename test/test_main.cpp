#include <iostream>
#include <cassert>
#include <functional>
#include <stdexcept>
#include <vector>
#include "fx/algorithm/RateStrategy.h"
#include "fx/algorithm/LearningStrategy.h"

#if defined(_DEBUG)
  #define __ASSERT(x) assert(x)
#else
  inline void assertR(bool v) {
	if (!v) {
		throw std::runtime_error("assert");
	}
  }
  #define __ASSERT(x) assertR(x)
#endif

namespace flowTumn {
	inline double calcPercentage(double base, double percent) {
		return base * (percent / 100.0);
	}
};

//Rateで売りを判断する戦略のテスト。
void testRateStrategy() {
	//テストレート
	std::vector <double> testRate{
		0.290197 / 100.0,
		1.234059 / 100.0,
		1.879112 / 100.0,
		2.193251 / 100.0,
		2.908776 / 100.0,
		3.817992 / 100.0,
		7.219482 / 100.0,
		8.190398 / 100.0,
		19.24817 / 100.0,
		30.29911 / 100.0,
		1.111111 / 100.0,
		2.222222 / 100.0,
		3.333333 / 100.0,
		4.444444 / 100.0,
		5.555555 / 100.0,
		6.666666 / 100.0,
		7.777777 / 100.0,
		8.888888 / 100.0,
	};

	//テストで使用する境界値用レート。
	const std::vector <double> correctRate{
		0.05,
		0.03,
		0.5,
		0.3,
		0.1,
		0.01,
		0.001,
		0.0001,
		0.00001,
		0.000001,
		0.0000001,
		0.00000001,
		0.000000001,
		0.0000000001,
		0.00000000001,
		0.000000000001,
		0.0000000000001,
	};

	for (auto&& eachH : testRate) {
		for (auto&& eachL : testRate) {
			auto H = eachH * 100.0;
			auto L = eachL * 100.0;
			
			flowTumn::RateStrategy s(H, L);

			__ASSERT(s.highRate() == H && "assert high Rate.");
			__ASSERT(s.lowRate() == L && "assert low Rate.");

			//いつでも買って良い
			__ASSERT(true == s.judgeBuy() && "assert judge Buy.");

			//現値が80.0～130.0でテストを行う。
			for (auto i = 80.00; i <= 130.00; i += 0.01) {
				auto v = flowTumn::factoryFXBid(i);
				const auto C = v.bid;

				//現値を更新。
				s.updateBidAsk(v);

				//現値では売らない。
				__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(C) && "assert judge sell in the currentRate.");

				// *** 高値で売るかのチェック。 ***

				// まずは売っては行けない。
				for (auto&& each : correctRate) {
					__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(C + flowTumn::calcPercentage(C, H - each)) && "assert miss judge sell");
				}

				// 指定レートにまで上がった、売る。
				__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(C + flowTumn::calcPercentage(C, H)) && "assert miss judge sell");

				// レート以上は売る。
				for (auto&& each : correctRate) {
					__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(C + flowTumn::calcPercentage(C, H + each)) && "assert miss judge sell");
				}

				// *** 低音で売るかのチェック。 ***

				// これは売っては行けない。
				for (auto&& each : correctRate) {
					__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(C - flowTumn::calcPercentage(C, L - each)) && "assert miss judge sell");
				}

				//売って良い。(損切り)
				__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(C - flowTumn::calcPercentage(C, L)) && "assert miss judge sell");

				//指定レートより下がってるのなら、売るべき。
				for (auto&& each : correctRate) {
					__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(C - flowTumn::calcPercentage(C, L + each)) && "assert miss judge sell");
				}
			}
		}
	}
}

//過去の情報を元にする戦略のテスト
void testLearningStrategy() {
	flowTumn::LearningStrategy l(1.00, 2.00);

	for (int i = 0 ; i < 10 ; ++i) {
		l.learning(flowTumn::factoryFXInfo(100.10, 102.20, 105.55, 99.912));
	}

	__ASSERT(false == l.isObeyRules() && "assert LearningStrategy isObeyRules.");

	auto info = flowTumn::LearningStrategy::learningInfo(l);
	__ASSERT(10 == info.learningCount && "assert Learning counter.");

}

#include <unordered_map>
int main() {
	std::unordered_map <double, int64_t> v1, v2, v3, v4;

	for (double i = 70.000; i <= 150.00; i += 0.001) {
		++v1[i];
		++v2[i];
		++v3[i];
		++v4[i];
	}
	testRateStrategy();
	testLearningStrategy();
	return 0;
}
