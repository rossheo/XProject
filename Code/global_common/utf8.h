#pragma once

#include <boost/locale.hpp>
inline std::wstring fromUTF8(const std::string& s)
{
    return boost::locale::conv::utf_to_utf<wchar_t>(s);
}

inline std::string toUTF8(const std::wstring& ws)
{
    return boost::locale::conv::utf_to_utf<char>(ws);
}
