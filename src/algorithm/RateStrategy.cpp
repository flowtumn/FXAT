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
	//現在の目安となる売値。
	const auto nowBidRate = this->fxInfo_.load().bid;

	if (nowBidRate < ask) {
		// 買値より下がってる。
		auto diff = ask - nowBidRate;
		auto l = ask * this->rateLow_;

		//最低レートを下回った、損切りすべき。
		if (l <= diff) {
			return IFXStrategy::SellResult::OverLowRate;
		}
	} else {
		// 買値より高い。
		auto diff = nowBidRate - ask;
		auto h = ask * this->rateHigh_;

		//最大レートを上まった、問答無用で売る。
		if (h <= diff) {
			return IFXStrategy::SellResult::OverHighRate;
		}
	}

	return IFXStrategy::SellResult::None;
}