#include "fx/data/FXInfo.h"

namespace flowTumn {
	FXInfo factoryFXInfoCurrentRate(double rateCurrent) {
		return{ rateCurrent, 0.0, 0.0, 0.0, 0.0 };
	}
}