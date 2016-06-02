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

		// ����ׂ�High Rate.(�헪�ɂ���Ă̓��[�g����E���Ă�judge�����Ғʂ�̓�����Ԃ����Ƃ͂Ȃ��ł��낤)
		virtual double highRate() const = 0;

		// ����ׂ�Low Rate.(�헪�ɂ���Ă̓��[�g����E���Ă�judge�����Ғʂ�̓�����Ԃ����Ƃ͂Ȃ��ł��낤)
		virtual double lowRate() const = 0;

		// ���̐헪�̓��[�g�̋K���ɏ]�����H
		virtual bool isObeyRules() const = 0;

		// �����Ă��ǂ����H
		virtual bool judgeBuy() const = 0;

		// �����Ă��ǂ����H
		virtual bool jedgeSell(double price) const = 0;
	};
};

#endif // IFXSTRATEGY_H_INCLUDE__
