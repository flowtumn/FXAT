#include "fx/algorithm/RateStrategy.h"
#include "fx/data/FXInfo.h"

using namespace flowTumn;

RateStrategy::RateStrategy(double rateHigh, double rateLow)
	: rateHigh_(rateHigh / 100.0)
	, rateLow_(rateLow / 100.0)
{}

void RateStrategy::learning(const FXInfo&) {
}

void RateStrategy::updateBidAsk(const FXBidAsk& info) {
	this->fxInfo_.store(info);
}

double RateStrategy::highRate() const {
	return this->rateHigh_ * 100.0;
}

double RateStrategy::lowRate() const {
	return this->rateLow_ * 100.0;
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
	const auto nowBidRate = this->fxInfo_.load().bid;

	//買値より売値は高い。
	if (nowBidRate >= ask) {
		auto h = ask * (this->rateHigh_ + 1.0);

		//売った時の差が、計算した利益を超えるなら売り。
		if (nowBidRate >= h) {
			return IFXStrategy::SellResult::OverHighRate;
		}
	} else {
		auto l = ask - (ask * this->rateLow_);

		//売った時の差が、計算した損益を超えるなら売り。
		if (nowBidRate <= l) {
			return IFXStrategy::SellResult::OverLowRate;
		}
	}

	return IFXStrategy::SellResult::None;
}