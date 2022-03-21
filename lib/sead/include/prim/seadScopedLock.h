#pragma once

namespace sead
{
template <typename T>
class ScopedLock
{
public:
    ScopedLock(T* lock) : mLocked(lock) { mLocked->lock(); }
    ScopedLock(const ScopedLock& other) = delete;
    const ScopedLock& operator=(const ScopedLock& other) = delete;
    virtual ~ScopedLock() { mLocked->unlock(); }

protected:
    T* mLocked;
};

template <typename T>
[[nodiscard]] inline ScopedLock<T> makeScopedLock(T& lock)
{
    return ScopedLock<T>(&lock);
}

template <typename T>
class ConditionalScopedLock
{
public:
    ConditionalScopedLock(T* lock, bool do_lock)
    {
        if (!do_lock)
            return;
        mLocked = lock;
        mLocked->lock();
    }
    ConditionalScopedLock(const ConditionalScopedLock& other) = delete;
    const ConditionalScopedLock& operator=(const ConditionalScopedLock& other) = delete;
    virtual ~ConditionalScopedLock()
    {
        if (mLocked)
            mLocked->unlock();
    }

protected:
    T* mLocked = nullptr;
};

template <typename T>
[[nodiscard]] inline ConditionalScopedLock<T> makeScopedLock(T& lock, bool do_lock)
{
    return ConditionalScopedLock<T>(&lock, do_lock);
}
}  // namespace sead
