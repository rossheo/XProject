#pragma once
#include "loki/Singleton.h"

#define SINGLETON(class_name, create_policy) \
::Loki::SingletonHolder<class_name, create_policy, ::Loki::DefaultLifetime, ::Loki::ClassLevelLockable>::Instance()

#define SINGLETON_STATIC(class_name) SINGLETON(class_name, ::Loki::CreateStatic)
#define SINGLETON_DYNAMIC(class_name) SINGLETON(class_name, ::Loki::CreateUsingNew)
