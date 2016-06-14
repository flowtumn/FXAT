#include "fx/data/FXInfo.h"

namespace flowTumn {
	FXBidAsk factoryFXAsk(double ask) {
		return{
			0,
			ask,
			0.0
		};
	}

	FXBidAsk factoryFXBid(double bid) {
		return{
			0,
			0.0,
			bid,
		};
	}

	FXBidAsk factoryFXBidAsk(double ask, double bid) {
		return{
			0,
			ask,
			bid
		};

	}

	FXInfo factoryFXInfo(double open, double close, double high, double low) {
		return{
			0,
			open,
			close,
			high,
			low,
			""
		};
	}
};
