#pragma once

#include <synchapi.h>

// RW Lock abstract class
struct __declspec(novtable) RWLock
{
public:
    virtual void EnterRead() = 0;
    virtual void LeaveRead() = 0;
    virtual void EnterWrite() = 0;
    virtual void LeaveWrite() = 0;
};

// CriticalSection wrapper class
class CriticalSection
{
public:
    explicit CriticalSection();
    ~CriticalSection();

public:
    void Enter();
    void Leave();

private:
    CRITICAL_SECTION _criticalSection;
};

inline CriticalSection::CriticalSection()
{
    InitializeCriticalSection(&_criticalSection);
}

inline CriticalSection::~CriticalSection()
{
    DeleteCriticalSection(&_criticalSection);
}

inline void CriticalSection::Enter()
{
    EnterCriticalSection(&_criticalSection);
}

inline void CriticalSection::Leave()
{
    LeaveCriticalSection(&_criticalSection);
}

// Critical Section Lock
class CriticalSectionRWLock : public RWLock
{
public:
    virtual void EnterRead() override
    {
        _lock.Enter();
    }

    virtual void LeaveRead() override
    {
        _lock.Leave();
    }

    virtual void EnterWrite() override
    {
        _lock.Enter();
    }

    virtual void LeaveWrite() override
    {
        _lock.Leave();
    }

private:
    CriticalSection _lock;
};

// Windows Slim Reader/Writer (SRW) Locks
class SlimRWLock : public RWLock
{
public:
    SlimRWLock()
    {
        InitializeSRWLock(&_lock);
    }

    virtual void EnterRead() override
    {
        AcquireSRWLockShared(&_lock);
    }

    virtual void LeaveRead() override
    {
        ReleaseSRWLockShared(&_lock);
    }

    virtual void EnterWrite() override
    {
        AcquireSRWLockExclusive(&_lock);
    }

    virtual void LeaveWrite() override
    {
        ReleaseSRWLockExclusive(&_lock);
    }

private:
    SRWLOCK _lock;
};

// Scoped R/W Lock
template <typename Lock = SlimRWLock>
class RLockGuard
{
public:
    RLockGuard(Lock& lock)
        : _lock(lock)
    {
        _lock.EnterRead();
    }

    ~RLockGuard()
    {
        _lock.LeaveRead();
    }

    RLockGuard(const RLockGuard&) = delete;
    RLockGuard& operator=(const RLockGuard&) = delete;

private:
    Lock& _lock;
};

template <typename Lock = SlimRWLock>
class WLockGuard
{
public:
    WLockGuard(Lock& lock)
        : _lock(lock)
    {
        _lock.EnterWrite();
    }

    ~WLockGuard()
    {
        _lock.LeaveWrite();
    }

    WLockGuard(const WLockGuard&) = delete;
    WLockGuard& operator=(const WLockGuard&) = delete;

private:
    Lock& _lock;
};

#define LOCK_R(x) RLockGuard<decltype(x)> rlock(x)
#define LOCK_W(x) WLockGuard<decltype(x)> wlock(x)
