#ifndef RATESTRATEGY_H_INCLUDE__
#define RATESTRATEGY_H_INCLUDE__

#include <atomic>
#include "fx/data/FXInfo.h"
#include "IFXStrategy.h"

namespace flowTumn {
	/**
	 * レートによる売り買いを決める。
	 */
	class RateStrategy : public flowTumn::IFXStrategy {
	public:
		RateStrategy(double rateHigh, double rateLow);
		void update(const FXInfo& info) override;
		double highRate() const override;
		double lowRate() const override;
		bool isObeyRules() const override;
		bool judgeBuy() const override;
		bool jedgeSell(double price) const override;

	private:
		const double rateHigh_;
		const double rateLow_;
		std::atomic <FXInfo> fxInfo_;
	};
};

#endif // RATESTRATEGY_H_INCLUDE__
