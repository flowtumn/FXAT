#include "fx/algorithm/RateStrategy.h"
#include "fx/data/FXInfo.h"

using namespace flowTumn;

namespace {
	const auto SCALE = 1000000000;
	inline uint64_t scaleOut(double v) {
		return static_cast <uint64_t> (v * SCALE);
	}

	inline double scaleIn(uint64_t v) {
		return static_cast <double> ((v * 1.0) / (SCALE * 1.0));
	}

	inline double toPercent(double v) {
		return v * 100.0;
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

	//買値。
	const auto askRate = scaleOut(ask);

	//現在の目安となる売値。
	const auto bidRate = scaleOut(this->fxInfo_.load().bid);

	//買値より売値は高い。
	if (bidRate >= askRate) {
		auto r = static_cast <double> (bidRate - askRate) / static_cast <double> (bidRate);

		//売った時の差が、計算した利益を超えるなら売り。
		if (this->rateHigh_ <= r) {
			return IFXStrategy::SellResult::OverHighRate;
		}
	} else {
		auto r = static_cast <double> (askRate - bidRate) / static_cast <double> (bidRate);

		//売った時の差が、計算した損益を超えるなら売り。
		if (this->rateLow_ <= r) {
			return IFXStrategy::SellResult::OverLowRate;
		}
	}

	return IFXStrategy::SellResult::None;
}