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

		// 売るべきHigh Rate.(戦略によってはレートを逸脱してもjudgeが期待通りの答えを返すことはないであろう)
		virtual double highRate() const = 0;

		// 売るべきLow Rate.(戦略によってはレートを逸脱してもjudgeが期待通りの答えを返すことはないであろう)
		virtual double lowRate() const = 0;

		// この戦略はレートの規則に従うか？
		virtual bool isObeyRules() const = 0;

		// 買っても良いか？
		virtual bool judgeBuy() const = 0;

		// 売っても良いか？
		virtual bool jedgeSell(double price) const = 0;
	};
};

#endif // IFXSTRATEGY_H_INCLUDE__
