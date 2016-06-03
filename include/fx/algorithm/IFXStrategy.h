#ifndef IFXSTRATEGY_H_INCLUDE__
#define IFXSTRATEGY_H_INCLUDE__

namespace flowTumn {
	struct FXBidAsk;
	struct FXInfo;

	/**
	 * 買い、売りのStrategy。
	 */
	class IFXStrategy {
	public:
		//どんな理由で売るのか？
		enum struct SellResult : int {
			None = 0x00,			//戦略的に売ってはダメ。
			OverHighRate = 0x01,	//指定した高いレートを超えたので売り。
			OverLowRate = 0x02,		//指定した低いレートを下回ったので売り。(損切)
			Benefit = 0x03,			//指定したレートは無視にして、売れば利益になる。
			Loss = 0x04,			//指定したレートは無視にして、売って損切し、やり直すべき。
		};

		// 過去の情報を用いて学習。
		virtual void learning(const FXInfo& info) = 0;

		// 現在の買い・売りレートを更新。
		virtual void updateBidAsk(const FXBidAsk& info) = 0;

		// 売るべきHigh Rate.(戦略によってはレートを逸脱してもjudgeが期待通りの答えを返すことはないであろう)
		virtual double highRate() const = 0;

		// 売るべきLow Rate.(戦略によってはレートを逸脱してもjudgeが期待通りの答えを返すことはないであろう)
		virtual double lowRate() const = 0;

		// この戦略はレートの規則に従うか？
		virtual bool isObeyRules() const = 0;

		// 買っても良いか？
		virtual bool judgeBuy() const = 0;

		// 売っても良いか？
		virtual SellResult jedgeSell(double ask) const = 0;
	};
};

#endif // IFXSTRATEGY_H_INCLUDE__
