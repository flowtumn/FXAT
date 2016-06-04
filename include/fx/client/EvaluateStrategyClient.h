#ifndef EVALUATESTRATEGYCLIENT_H_INCLUDE__
#define EVALUATESTRATEGYCLIENT_H_INCLUDE__

#include <cstdint>
#include <type_traits>
#include "fx/algorithm/IFXStrategy.h"
#include "fx/repository/IFXRepository.h"

namespace flowTumn {
	struct FXBidAsk;

	/**
	 * 戦略を評価するクライアント。
	 * (自発的にデータを取得ではなく、評価するデータは外から与える)
	 */
	template <typename S, typename R>
	class EvaluateStrategyClient {
		static_assert(std::is_base_of <flowTumn::IFXStrategy, S>::value, "L must be a descendant of IFXStrategy.");
		static_assert(std::is_base_of <flowTumn::IFXRepository, R>::value, "L must be a descendant of IFXRepository.");

		enum struct State {
			Buy,		// 買いたい.
			Sell,		// 売りたい.
		};

	public:
		EvaluateStrategyClient(double rateHigh, double rateLow)
			: strategy_(rateHigh, rateLow)
			, counterBuy_(0)
			, counterSellHigh_(0)
			, counterSellLow_(0)
			, state_(EvaluateStrategyClient::State::Buy)
			, profit_(0.0)
		{}

		IFXRepository& repository() {
			return this->repository_;
		}

		// この高値/売値を用いて、戦略を扱い、売り・買いを実行する。
		void simulation(const flowTumn::FXBidAsk& info, const std::string& description) {
			//更新。
			this->strategy_.updateBidAsk(info);

			switch (this->state_) {
			default:
				return;
			case State::Buy:
				if (this->strategy_.judgeBuy(info.ask)) {
					//買い。
					this->boughtRate_ = info.ask;
					++this->counterBuy_;

					//売りに転じる。
					this->state_ = State::Sell;

					this->repository_.bought(info.ask, 0, description);
				}
				break;
			case State::Sell:
				switch (this->strategy_.jedgeSell(this->boughtRate_)) {
				default:
					return;
				case flowTumn::IFXStrategy::SellResult::Benefit:
				case flowTumn::IFXStrategy::SellResult::OverHighRate:
					//利益が出るので売り。
					++this->counterSellHigh_;

					//利益。
					this->profit_ += info.bid - this->boughtRate_;
					this->state_ = State::Buy;

					this->repository_.sold(info.bid, 0, description);
					break;
				case flowTumn::IFXStrategy::SellResult::Loss:
				case flowTumn::IFXStrategy::SellResult::OverLowRate:
					//損切り。
					++this->counterSellLow_;

					//利益。
					this->profit_ += info.bid - this->boughtRate_;

					this->state_ = State::Buy;

					this->repository_.sold(info.bid, 0, description);
					break;
				}
				break;
			}
		}

		//現在の評価結果を取得。
		int64_t operationBuy() const {
			return this->counterBuy_;
		}

		int64_t operationSellHigh() const {
			return this->counterSellHigh_;
		}

		int64_t operationSellLow() const {
			return this->counterSellLow_;
		}

		//正答率
		double highPercent() const {
			return (this->counterSellHigh_ * 1.0) / (this->counterBuy_ * 1.0) * 100.0;
		}

		//誤答率
		double lowPercent() const {
			return (this->counterSellLow_ * 1.0) / (this->counterBuy_ * 1.0) * 100.0;
		}

		double profit() const {
			return this->profit_;
		}

	private:
		S strategy_;
		R repository_;
		int64_t counterBuy_;
		int64_t counterSellHigh_;
		int64_t counterSellLow_;
		State state_;
		double boughtRate_;
		double profit_;
	};
};

#endif // EVALUATESTRATEGYCLIENT_H_INCLUDE__
