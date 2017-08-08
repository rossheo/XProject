#pragma once

#pragma warning(disable: 4267)
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/integer_traits.hpp>
#pragma warning(default: 4267)

#pragma warning(push)
#pragma warning(disable: 4100)
#include <boost/heap/priority_queue.hpp>
#pragma warning(pop) 

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

#include <boost/variant.hpp>