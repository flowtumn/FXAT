#include <algorithm>
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

void testSimpleRate() {
	const auto H = 0.1;
	const auto L = 0.2;
	flowTumn::RateStrategy s(H, L);

	//この値段で買ったとする。
	auto v = flowTumn::factoryFXBid(100.00);

	//現値を更新。
	s.updateBidAsk(v);

	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.99) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.98) && "assert judge sell in the currentRate.");

	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(99.001) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(99.000 * H) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(99.000 * (H - 0.01)) && "assert judge sell in the currentRate.");

	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(99.000 - (99.000 * (H - 0.1))) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(99.000 * (1.0 - H)) && "assert judge sell in the currentRate.");

	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.1)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H)) && "assert judge sell in the currentRate.");

	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 + L - 0.1)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 + L - 0.01)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 + L - 0.001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 + L - 0.0001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 + L - 0.00001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 + L - 0.000001)) && "assert judge sell in the currentRate.");

	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.1)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.01)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.0001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.00001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.0000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.00000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.0000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.00000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.000000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(100.000 * (1.0 + L + 0.0000000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 + L - 0.1)) && "assert judge sell in the currentRate.");


	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.1)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.01)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.0001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.00001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.0000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.00000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.0000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.00000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(100.000 * (1.0 - H + 0.000000000001)) && "assert judge sell in the currentRate.");

	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.1)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.01)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.0001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.00001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.0000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.00000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.0000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.00000000001)) && "assert judge sell in the currentRate.");
	__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(100.000 * (1.0 - H - 0.000000000001)) && "assert judge sell in the currentRate.");
}

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
	std::vector <double> correctRate{
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
		0.00000000000001,
		0.000000000000001,
		0.0000000000000001,
		0.00000000000000001,
		0.000000000000000001,
	};

	//テストRateから非対応のPercentageを除外。
	correctRate.erase(
		std::remove_if(
				std::begin(correctRate)
			,	std::end(correctRate)
			,	[](double v) {
				return v <= flowTumn::RateStrategy{0.0, 0.0}.supportPercentage();
			}
		),
		std::end(correctRate)
	);

	for (auto&& eachH : testRate) {
		for (auto&& eachL : testRate) {
			auto H = eachH * 100.0;
			auto L = eachL * 100.0;
			
			flowTumn::RateStrategy s(H, L);

			__ASSERT(s.highRate() == H && "assert high Rate.");
			__ASSERT(s.lowRate() == L && "assert low Rate.");

			//いつでも買って良い
			__ASSERT(true == s.judgeBuy(H) && "assert judge Buy.");
			__ASSERT(true == s.judgeBuy(L) && "assert judge Buy.");

			//現値が80.0～130.0でテストを行う。
			for (auto i = 80.05; i <= 130.00; i += 0.01) {
				auto v = flowTumn::factoryFXBid(i);

				//この値段で買ったとする。
				const auto ASK = v.bid;

				//現値を更新。
				s.updateBidAsk(v);

				//現値では売らない。
				__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(ASK) && "assert judge sell in the currentRate.");

				////////////////////////////////////
				// 売りのテスト
				////////

				//境界(売ってはダメ)
				//(HighRateをやや減らしているため)
				for (auto&& each : correctRate) {
					__ASSERT(flowTumn::IFXStrategy::SellResult::None== s.jedgeSell(ASK * (1.0 - H + each)) && "assert judge sell in the currentRate.");
				}

				//売ってよい
				__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate== s.jedgeSell(ASK * (1.0 - H)) && "assert judge sell in the currentRate.");

				//HigtRateを大きくしているので、これも当然売ってよい。
				for (auto&& each : correctRate) {
					__ASSERT(flowTumn::IFXStrategy::SellResult::OverHighRate == s.jedgeSell(ASK * (1.0 - H - each)) && "assert judge sell in the currentRate.");
				}

				////////////////////////////////////
				// 買いのテスト
				////////

				//境界(売っはダメ)
				//(LowRateをやや減らしているため)
				for (auto&& each : correctRate) {
					__ASSERT(flowTumn::IFXStrategy::SellResult::None == s.jedgeSell(ASK * (1.0 + L - each)) && "assert judge sell in the currentRate.");
				}

				//損切してよい。
				__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate== s.jedgeSell(ASK * (1.0 + L)) && "assert judge sell in the currentRate.");

				//LowRateを大きくしているので、これも当然売ってよい。
				for (auto&& each : correctRate) {
					__ASSERT(flowTumn::IFXStrategy::SellResult::OverLowRate == s.jedgeSell(ASK * (1.0 + L + each)) && "assert judge sell in the currentRate.");
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

int main() {
	testSimpleRate();
	testRateStrategy();
	testLearningStrategy();
	return 0;
}
