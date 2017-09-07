#pragma once

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/initializer.h>
#include <iomanip>

// Logging Macro
#define ASSERT(condition) \
    LOG4CPLUS_ASSERT(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(##LOG_FILTER_ASSERT##)), \
     condition); _ASSERT(condition);

#define LOG_TRACE(LOG_FILTER_, FORMAT_STR, ...) \
    LOG4CPLUS_TRACE_STR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(##LOG_FILTER_##)), \
    fmt::format(LOG4CPLUS_TEXT(##FORMAT_STR##), __VA_ARGS__))

#define LOG_DEBUG(LOG_FILTER_, FORMAT_STR, ...) \
    LOG4CPLUS_DEBUG_STR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(##LOG_FILTER_##)), \
    fmt::format(LOG4CPLUS_TEXT(##FORMAT_STR##), __VA_ARGS__))

#define LOG_INFO(LOG_FILTER_, FORMAT_STR, ...) \
    LOG4CPLUS_INFO_STR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(##LOG_FILTER_##)), \
    fmt::format(LOG4CPLUS_TEXT(##FORMAT_STR##), __VA_ARGS__))

#define LOG_WARN(LOG_FILTER_, FORMAT_STR, ...) \
    LOG4CPLUS_WARN_STR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(##LOG_FILTER_##)), \
    fmt::format(LOG4CPLUS_TEXT(##FORMAT_STR##), __VA_ARGS__))

#define LOG_ERROR(LOG_FILTER_, FORMAT_STR, ...) \
    LOG4CPLUS_ERROR_STR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(##LOG_FILTER_##)), \
    fmt::format(LOG4CPLUS_TEXT(##FORMAT_STR##), __VA_ARGS__))

#define LOG_FATAL(LOG_FILTER_, FORMAT_STR, ...) \
    LOG4CPLUS_FATAL_STR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(##LOG_FILTER_##)), \
    fmt::format(LOG4CPLUS_TEXT(##FORMAT_STR##), __VA_ARGS__))

// LOG_FILTER
#define LOG_FILTER_ASSERT "Assert"
#define LOG_FILTER_SYSTEM "System"
#define LOG_FILTER_NETWORK "Network"

#define LOG_FILTER_SERVER "Server"
#define LOG_FILTER_CLIENT "Client"
#define LOG_FILTER_CONNECTION "Connection"

#define LOG_FILTER_ID_POOL "IdPool"
#define LOG_FILTER_UNIT "Unit"

#define LOG_FILTER_PACKET_BUFFER "PacketBuffer"
#define LOG_FILTER_PACKET_HANDLER "PacketHandler"

#define LOG_FILTER_DECLARE_TYPE "DeclareType"