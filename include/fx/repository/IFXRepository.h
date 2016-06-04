﻿#ifndef IFXREPOSITORY_H_INCLUDE__
#define IFXREPOSITORY_H_INCLUDE__

#include <cstdint>
#include <string>

namespace flowTumn {
	/**
	 * 売買記録を行うRepository
	 */
	class IFXRepository {
	public:
		// 買った。
		virtual void bought(double rate, uint32_t tm, const std::string& description) = 0;

		// 売った。
		virtual void sold(double rate, uint32_t tm, const std::string& description) = 0;
	};
};

#endif // IFXREPOSITORY_H_INCLUDE__
