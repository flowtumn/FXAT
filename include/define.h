#ifndef DEFINE_H_INCLUDE__
#define DEFINE_H_INCLUDE__

#include <cstdlib>
#include <cstdint>
#include <string>

#if defined(UNICODE) || defined(_UNICODE)
  #include <codecvt>
#endif

namespace flowTumn {

#if (1800 < _MSC_VER)
  #define CONSTEXPR   constexpr
#else
  #define CONSTEXPR
#endif

#if defined(UNICODE) || defined(_UNICODE)
  using tstr = std::wstring;
  #define _T(x)	L##x

  inline std::string conv(const std::wstring& s) {
    return std::wstring_convert<std::codecvt_utf8 <wchar_t>, wchar_t>{}.to_bytes(s);
  }

  inline std::wstring conv(const std::string& s) {
    return std::wstring_convert<std::codecvt_utf8 <wchar_t>, wchar_t>{}.from_bytes(s);
  }

#else
  using tstr = std::string;
  #define _T(x)	x

  inline auto conv(const tstr& s) {
    return s;
  }
#endif

  inline uint64_t toUint64(const tstr& s) {
    return std::atoll(conv(s).data());
  }

  inline uint32_t toUint32(const tstr& s) {
    return std::atol(conv(s).data());
  }


};

#endif
