#ifndef IFXREPOSITORY_H_INCLUDE__
#define IFXREPOSITORY_H_INCLUDE__

namespace flowTumn {
	/**
	 * �����L�^���s��Repository
	 */
	class IFXRepository {
	public:
		// �������B
		virtual void bought(double rate) = 0;

		// �������B
		virtual void sold(double rate) = 0;
	};
};

#endif // IFXREPOSITORY_H_INCLUDE__
