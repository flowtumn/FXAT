#include "fx/algorithm/RateStrategy.h"
#include "fx/data/FXInfo.h"

using namespace flowTumn;

RateStrategy::RateStrategy(double rateHigh, double rateLow)
	: rateHigh_(rateHigh / 100.0)
	, rateLow_(rateLow / 100.0)
{}

void RateStrategy::update(const FXInfo& info){
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

//priceを買値とした場合、売るべきか？
bool RateStrategy::jedgeSell(double price) const {
	const auto nowRate = this->fxInfo_.load().rateCurrent;
	const auto h = nowRate * this->rateHigh_;
	const auto l = nowRate * this->rateLow_;
	const auto nh = nowRate + h;
	const auto nl = nowRate - l;

	//現在レートから High or Low なら売り。
	if (nh <= price) {
		return true;
	} else if (nl >= price) {
		return true;
	}

	return false;
}