#pragma once

#include <iosfwd>

inline std::basic_ostream<wchar_t, std::char_traits<wchar_t>>&
operator<< (std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& os, const char* pStr)
{
    return os << ToWstring(pStr);
}

inline std::basic_ostream<wchar_t, std::char_traits<wchar_t>>&
operator<< (std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& os, const std::string& str)
{
    return os << ToWstring(str);
}

inline std::basic_ostream<wchar_t, std::char_traits<wchar_t>>&
operator<< (std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& os, const std::exception& ex)
{
    return os << fmt::format(TEXT("exception: {}"), ToWstring(ex.what()));
}

inline std::basic_ostream<wchar_t, std::char_traits<wchar_t>>&
operator<< (std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& os,
    const boost::system::error_code& errorCode)
{
    return os << fmt::format(TEXT("errorCode: {}, errorMessage: {}"),
        errorCode.value(), ToWstring(errorCode.message()));
}

inline std::basic_ostream<wchar_t, std::char_traits<wchar_t>>&
operator<< (std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& os,
    const boost::asio::ip::tcp::endpoint& endPoint)
{
    return os << fmt::format(TEXT("address: {}, port: {}"),
        endPoint.address().to_string(), endPoint.port());
}
