#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN
#include <windows.h>
#undef max
#undef min

#include "data_type.h"
#include "macro_define.h"
#include "stl_define.h"
#include "boost_define.h"
#include "log4plus_define.h"
#include "format.h"
#include "utf8.h"
#include "rw_lock.h"

#define LOKI_WINDOWS_H
#include "singleton.h"