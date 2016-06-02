#ifndef RATESTRATEGY_H_INCLUDE__
#define RATESTRATEGY_H_INCLUDE__

#include "IFXStrategy.h"

namespace flowTumn {
	struct FXInfo;

	/**
	 * ƒŒ[ƒg‚É‚æ‚é”„‚è”ƒ‚¢‚ğŒˆ‚ß‚éB
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
		const double rateHight_;
		const double rateLow_;
	};
};

#endif // RATESTRATEGY_H_INCLUDE__
