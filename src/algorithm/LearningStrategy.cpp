#include "fx/algorithm/LearningStrategy.h"

#include <algorithm>
#include "fx/data/FXInfo.h"

using namespace flowTumn;

LearningStrategy::LearningStrategy(double rateHigh, double rateLow)
	: RateStrategy(rateHigh, rateLow)
	, learningInfo_(LearningInfo{})
{}

void LearningStrategy::learning(const FXInfo& info) {
	auto r = this->learningInfo_.load();

	//買値の合計値は、始値と高値の平均値とする。
	r.totalAsk += (info.rateOpen + info.rateHigh) / 2;

	//それぞれの高値、低値を更新。
	r.maxAsk = std::max(r.maxAsk, info.rateHigh);
	r.minAsk = std::min(r.maxAsk, info.rateLow);

	//全ての値段に出現回数を振る。
	++this->distribution_[info.rateOpen];
	++this->distribution_[info.rateClose];
	++this->distribution_[info.rateHigh];
	++this->distribution_[info.rateLow];

	//学習した回数。
	++r.learningCount;

	//保存。
	this->learningInfo_.store(r);
}

void LearningStrategy::updateBidAsk(const FXBidAsk& info) {
	RateStrategy::updateBidAsk(info);
}

// ルールに決められたレートを厳守しない。
bool LearningStrategy::isObeyRules() const {
	return false;
}

bool LearningStrategy::judgeBuy(double) const {
	//過去を参考に今買うべきなのかを判断。
	return false;
}

IFXStrategy::SellResult LearningStrategy::jedgeSell(double ask) const {
	auto r = RateStrategy::jedgeSell(ask);

	//HighRateなら、問答無用で売り。
	if (IFXStrategy::SellResult::OverHighRate == r) {
		return r;
	}

	return IFXStrategy::SellResult::None;
}

// 学習した結果を取得。
flowTumn::LearningInfo LearningStrategy::learningInfo(const flowTumn::LearningStrategy& strategy) {
	auto r = strategy.learningInfo_.load();

	return {
		r.totalAsk / r.learningCount,
		r.totalAsk / r.learningCount,
		r.maxAsk,
		r.minAsk,
		r.maxBid,
		r.minBid,
		r.totalAsk,
		r.totalBid,
		r.learningCount
	};
}
