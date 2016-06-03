#include "fx/algorithm/RateStrategy.h"
#include "fx/data/FXInfo.h"

using namespace flowTumn;

RateStrategy::RateStrategy(double rateHigh, double rateLow)
	: rateHigh_(rateHigh / 100.0)
	, rateLow_(rateLow / 100.0)
{}

void RateStrategy::learning(const FXInfo& info) {
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
bool RateStrategy::judgeBuy() const {
	return true;
}

//askを買値とした場合、売るべきか？
IFXStrategy::SellResult RateStrategy::jedgeSell(double ask) const {
	const auto nowBidRate = this->fxInfo_.load().bid;
	const auto h = nowBidRate * this->rateHigh_;
	const auto l = nowBidRate * this->rateLow_;
	const auto nh = nowBidRate + h;
	const auto nl = nowBidRate - l;

	//現在レートから High or Low なら売り。
	if (nh <= ask) {
		return IFXStrategy::SellResult::OverHighRate;
	} else if (nl >= ask) {
		return IFXStrategy::SellResult::OverLowRate;
	}

	return IFXStrategy::SellResult::None;
}