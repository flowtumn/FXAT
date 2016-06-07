#include "fx/algorithm/RateStrategy.h"
#include "fx/data/FXInfo.h"

#include <sstream>

using namespace flowTumn;

namespace {
	inline uint64_t scale(double v) {
		round(v);
		auto r = v + 0.00000000000000005;
		return static_cast <uint64_t > ((v + 0.00000000000000005) * 10000000000000000);
	}
}

RateStrategy::RateStrategy(double rateHigh, double rateLow)
	: rateHigh_(rateHigh)
	, rateLow_(rateLow)
{}

void RateStrategy::learning(const FXInfo&) {
}

void RateStrategy::updateBidAsk(const FXBidAsk& info) {
	this->fxInfo_.store(info);
}

double RateStrategy::highRate() const {
	return this->rateHigh_;
}

double RateStrategy::lowRate() const {
	return this->rateLow_;
}

//この戦略はRateで売り買いするRuleの規則に従う。
bool RateStrategy::isObeyRules() const {
	return true;
}

//Rateで売る事が重視するので、買うタイミングはいつでも良い。
bool RateStrategy::judgeBuy(double) const {
	return true;
}

//askを買値とした場合、売るべきか？
IFXStrategy::SellResult RateStrategy::jedgeSell(double ask) const {

	//現在の目安となる売値。
	const auto bidRate = this->fxInfo_.load().bid;

	//買値より売値は高い。
	if (bidRate >= ask) {
		const auto r = static_cast <double> (bidRate - ask) / bidRate;

		//売った時の差が、計算した利益を超えるなら売り。
		if (scale(this->rateHigh_) <= scale(r)) {
			return IFXStrategy::SellResult::OverHighRate;
		}
	} else {
		const auto r = static_cast <double> (ask - bidRate) / bidRate;

		//売った時の差が、計算した損益を超えるなら売り。
		if (scale(this->rateLow_) <= scale(r)) {
			return IFXStrategy::SellResult::OverLowRate;
		}
	}

	return IFXStrategy::SellResult::None;

}
