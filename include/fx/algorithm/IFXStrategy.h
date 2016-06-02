#ifndef IFXSTRATEGY_H_INCLUDE__
#define IFXSTRATEGY_H_INCLUDE__

namespace flowTumn {
	struct FXInfo;

	/**
	 * �����A�����Strategy�B
	 */
	class IFXStrategy {
	public:
		// ���݂̏��ōX�V�B
		virtual void update(const FXInfo& info) = 0;

		// �����Ă��ǂ����H
		virtual bool judgeBuy() = 0;

		// �����Ă��ǂ����H
		virtual bool jedgeSell(double price) = 0;
	};
};

#endif // IFXSTRATEGY_H_INCLUDE__
