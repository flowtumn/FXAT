#ifndef LEARNINGSTRATEGY_H_INCLUDE__
#define LEARNINGSTRATEGY_H_INCLUDE__

#include <unordered_map>
#include "RateStrategy.h"

namespace flowTumn {
	struct LearningInfo {
		double averageAsk;	//買値の平均値
		double averageBid;	//売値の平均値
		double maxAsk;		//買値の最高値
		double minAsk;		//買値の最安値
		double maxBid;		//売値の最高値
		double minBid;		//売値の最安値
		double totalAsk;
		double totalBid;
		int64_t learningCount;
	};

	/**
	 * 過去の情報などを元に、買うことを重視した戦略。」
	 */
	class LearningStrategy : public flowTumn::RateStrategy {
	public:
		LearningStrategy(double rateHigh, double rateLow);
		void learning(const FXInfo& info) override;
		void updateBidAsk(const FXBidAsk& info) override;
		bool isObeyRules() const override;
		bool judgeBuy() const override;
		IFXStrategy::SellResult jedgeSell(double ask) const override;

		/**
		 * 学習した結果の情報を取得。
		 */
		static LearningInfo learningInfo(const flowTumn::LearningStrategy& strategy);

	private:
		std::unordered_map <double, int64_t> distribution_;
		std::atomic <LearningInfo> learningInfo_;
	};
};

#endif // LEARNINGSTRATEGY_H_INCLUDE__
