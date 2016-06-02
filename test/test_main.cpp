#include <cassert>
#include <functional>
#include <stdexcept>
#include <vector>
#include "fx/algorithm/RateStrategy.h"

namespace flowTumn {
	inline double calcPercentage(double base, double percent) {
		return base * (percent / 100.0);
	}
};

//Rateで売りを判断する戦略のテスト。
void testRateStrategy() {
	//高値・低値
	const auto H = 8.12;
	const auto L = 10.26;

	//テストで使用するレート。
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

	flowTumn::RateStrategy s(H, L);

	assert(s.highRate() == H && "assert high Rate.");
	assert(s.lowRate() == L && "assert low Rate.");

	//いつでも買って良い
	assert(true == s.judgeBuy() && "assert judge Buy.");

	//現値が80.0～130.0でテストを行う。
	for (auto i = 8000; i < 13000; ++i) {
		auto v = flowTumn::factoryFXInfoCurrentRate(i / 100.0);
		const auto C = v.rateCurrent;

		//現値を更新。
		s.update(flowTumn::factoryFXInfoCurrentRate(C));

		//現値では売らない。
		assert(false == s.jedgeSell(C) && "assert judge sell in the currentRate.");

		// *** 高値で売るかのチェック。 ***

		// まずは売っては行けない。
		for (auto&& each : correctRate) {
			assert(false == s.jedgeSell(C + flowTumn::calcPercentage(C, H - each)) && "assert miss judge sell");
		}

		// 指定レートにまで上がった、売る。
		assert(true == s.jedgeSell(C + flowTumn::calcPercentage(C, H)) && "assert miss judge sell");

		// レート以上は売る。
		for (auto&& each : correctRate) {
			assert(true == s.jedgeSell(C + flowTumn::calcPercentage(C, H + each)) && "assert miss judge sell");
		}

		// *** 低音で売るかのチェック。 ***

		// これは売っては行けない。
		for (auto&& each : correctRate) {
			assert(false == s.jedgeSell(C - flowTumn::calcPercentage(C, L - each)) && "assert miss judge sell");
		}

		//売って良い。
		assert(true == s.jedgeSell(C - flowTumn::calcPercentage(C, L)) && "assert miss judge sell");

		//指定レートより下がってるのなら、売るべき。
		for (auto&& each : correctRate) {
			assert(true == s.jedgeSell(C - flowTumn::calcPercentage(C, L + each)) && "assert miss judge sell");
		}
	}
}

int main() {
	testRateStrategy();
	return 0;
}
