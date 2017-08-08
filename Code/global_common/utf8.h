#pragma once

#include <boost/locale.hpp>
inline std::wstring FromUTF8(const std::string& s)
{
    return boost::locale::conv::utf_to_utf<wchar_t>(s);
}

inline std::string ToUTF8(const std::wstring& ws)
{
    return boost::locale::conv::utf_to_utf<char>(ws);
}

inline std::wstring ToWstring(const std::string& str)
{
    auto length = MultiByteToWideChar(CP_ACP, 0, str.c_str(),
        static_cast<int>(str.size()),
        0, 0);

    std::wstring wstr(length, 0);
    MultiByteToWideChar(CP_ACP, 0,
        str.c_str(), static_cast<int>(str.size()),
        const_cast<wchar_t*>(wstr.data()), static_cast<int>(wstr.size()));

    return wstr;
}
