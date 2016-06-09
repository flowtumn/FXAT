#ifndef RATESTRATEGY_H_INCLUDE__
#define RATESTRATEGY_H_INCLUDE__

#include <atomic>
#include "fx/data/FXInfo.h"
#include "IFXStrategy.h"

namespace flowTumn {
	/**
	 * レートによる売り買いを決める戦略。
	 * (基本的な扱いの役割を担うので、これを継承して以降は戦略の幅を広げる。)
	 */
	class RateStrategy : public flowTumn::IFXStrategy {
	public:
		RateStrategy(double rateHigh, double rateLow);
		void learning(const FXInfo& info) override;
		void updateBidAsk(const FXBidAsk& info) override;
		double highRate() const override;
		double lowRate() const override;
		bool isObeyRules() const override;
		bool judgeBuy(double ask) const override;
		IFXStrategy::SellResult jedgeSell(double ask) const override;
		double supportPercentage() const override;

	protected:
		const double rateHigh_;
		const double rateLow_;
		std::atomic <FXBidAsk> fxInfo_;
	};
};

#endif // RATESTRATEGY_H_INCLUDE__
