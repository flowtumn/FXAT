#ifndef FX_INFO_H_INCLUDE__
#define FX_INFO_H_INCLUDE__

#include <cstdint>
#include <string>

namespace flowTumn {
	struct FXBidAsk {
		uint32_t tm;
		double ask;	//買いレート
		double bid; //売りレート
	};

	struct FXInfo {
		uint32_t tm;
		double rateOpen;
		double rateClose;
		double rateHigh;
		double rateLow;
		std::string description;
	};

	/**
	 * 買値だけで FXBidAsk を生成。
	 */
	FXBidAsk factoryFXAsk(double ask);

	/**
	 * 売値だけで FXBidAsk を生成。
	 */
	FXBidAsk factoryFXBid(double bid);

	/**
	 * FXBidAskを生成。
	 */
	FXBidAsk factoryFXBidAsk(double ask, double bid);

	/**
	 *
	 */
	FXInfo factoryFXInfo(double open, double close, double high, double low);
};

#endif //  FX_INFO_H_INCLUDE__