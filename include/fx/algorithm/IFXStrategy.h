#ifndef IFXSTRATEGY_H_INCLUDE__
#define IFXSTRATEGY_H_INCLUDE__

namespace flowTumn {
	struct FXInfo;

	/**
	 * 買い、売りのStrategy。
	 */
	class IFXStrategy {
	public:
		// 現在の情報で更新。
		virtual void update(const FXInfo& info) = 0;

		// 買っても良いか？
		virtual bool judgeBuy() = 0;

		// 売っても良いか？
		virtual bool jedgeSell(double price) = 0;
	};
};

#endif // IFXSTRATEGY_H_INCLUDE__
