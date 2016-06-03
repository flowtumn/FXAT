#ifndef FXINFO_H_INCLUDE__
#define FXINFO_H_INCLUDE__

namespace flowTumn {
	struct FXInfo {
		double rateCurrent;	// 現値
		double rateOpen;	// 始値
		double rateClose;	// 終値
		double rateHigh;	// 高値
		double rateLow;		// 低音
	};

	//現値だけでFXInfoを生成。
	FXInfo factoryFXInfoCurrentRate(double rateCurrent);
};

#endif // FXINFO_H_INCLUDE__
