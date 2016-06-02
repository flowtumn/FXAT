#ifndef IFXREPOSITORY_H_INCLUDE__
#define IFXREPOSITORY_H_INCLUDE__

namespace flowTumn {
	/**
	 * L^πs€Repository
	 */
	class IFXRepository {
	public:
		// Α½B
		virtual void bought(double rate) = 0;

		// Α½B
		virtual void sold(double rate) = 0;
	};
};

#endif // IFXREPOSITORY_H_INCLUDE__
