#pragma once

#include <iosfwd>

inline std::basic_ostream<wchar_t, std::char_traits<wchar_t>>&
operator<< (std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& os, const char* pStr)
{
    os << ToWstring(pStr);
    return os;
}

inline std::basic_ostream<wchar_t, std::char_traits<wchar_t>>&
operator<< (std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& os, const std::string& str)
{
    os << ToWstring(str);
    return os;
}

inline std::basic_ostream<wchar_t, std::char_traits<wchar_t>>&
operator<< (std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& os, const std::exception& ex)
{
    os << "exception: " << ex.what();
    return os;
}

inline std::basic_ostream<wchar_t, std::char_traits<wchar_t>>&
operator<< (std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& os,
    const boost::system::error_code& errorCode)
{
    os << "errorCode: " << errorCode.value()
        << ", errorMessage: " << errorCode.message();
    return os;
}

inline std::basic_ostream<wchar_t, std::char_traits<wchar_t>>&
operator<< (std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& os,
    const boost::asio::ip::tcp::endpoint& endPoint)
{
    os << "address: " << endPoint.address().to_string()
        << ", port: " << endPoint.port();
    return os;
}
