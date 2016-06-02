#ifndef RATESTRATEGY_H_INCLUDE__
#define RATESTRATEGY_H_INCLUDE__

#include "IFXStrategy.h"

namespace flowTumn {
	struct FXInfo;

	/**
	 * ���[�g�ɂ�锄�蔃�������߂�B
	 */
	class RateStrategy : public flowTumn::IFXStrategy {
		void update(const FXInfo& info) override;
		bool judgeBuy() override;
		bool jedgeSell(double price) override;
	};
};

#endif // RATESTRATEGY_H_INCLUDE__
