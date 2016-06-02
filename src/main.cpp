#include <array>
#include <iostream>
#include <tuple>
#include <functional>
#include <fstream>
#include <regex>
#include <sstream>

#include "define.h"

#if defined(UNICODE) || defined(_UNICODE)
  #define _tmain	wmain
  #define err		std::wcerr
#else
  #define _tmain	main
  #define err		std::cerr
#endif

int _tmain(int argc, flowTumn::tstr::value_type** argv) {

	[] {
		std::cout << "Hello." << std::endl;
	}();

}
