#pragma once

#ifdef NNSDK
#include <atomic>
#endif

namespace sead
{
struct AtomicDirectInitTag
{
};

template <class T>
struct AtomicBase
{
public:
    AtomicBase(T value = {});  // NOLINT(google-explicit-constructor)
    /// Directly initialises the underlying atomic with the specified value.
    /// Note that initialisation is not atomic.
    AtomicBase(AtomicDirectInitTag, T value);
    AtomicBase(const AtomicBase& rhs) { *this = rhs; }

    operator T() const { return load(); }

    AtomicBase& operator=(const AtomicBase& rhs)
    {
        store(rhs.load());
        return *this;
    }

    AtomicBase& operator=(T value)
    {
        store(value);
        return *this;
    }

    /// Load the current value, as if with memory_order_relaxed.
    T load() const;
    /// Store a new value, as if with memory_order_relaxed.
    void store(T value);
    /// Non-atomically store a new value.
    void storeNonAtomic(T value);
    /// Exchange/swap the current value, as if with memory_order_relaxed.
    /// @return the previous value
    T exchange(T value);
    /// Load the current value and if it is equal to `expected`, store `desired`
    /// as if with memory_order_relaxed.
    /// Otherwise, this sets `original` to the current value.
    /// @param expected  The value expected to be found in the atomic object, and to be replaced.
    /// @param desired   The new value to store in the atomic object if `expected` was found.
    /// @param original  The value that was found in the atomic object if the comparison fails. May
    ///                  be null. Note that this is only updated when false is returned.
    /// @return true if and only if the value was modified
    bool compareExchange(T expected, T desired, T* original = nullptr);

protected:
#ifdef NNSDK
    // Nintendo appears to have manually implemented atomics with volatile and platform specific
    // intrinsics (e.g. __builtin_arm_ldrex).
    // For ease of implementation and portability, we will use std::atomic and cast to volatile
    // when necessary. That is formally undefined behavior, but it should be safe because
    // sead is built with -fno-strict-aliasing and because of the following static assertions.
    std::atomic<T> mValue;
    static_assert(sizeof(mValue) == sizeof(T),
                  "std::atomic<T> and T do not have the same size; unsupported case");
    static_assert(alignof(decltype(mValue)) == alignof(volatile T),
                  "std::atomic<T> and T do not have the same alignment; unsupported case");
    static_assert(std::atomic<T>::is_always_lock_free,
                  "std::atomic<T>::is_always_lock_free is not true; unsupported case");

    const volatile T* getValuePtr() const { return reinterpret_cast<const volatile T*>(&mValue); }
    volatile T* getValuePtr() { return reinterpret_cast<volatile T*>(&mValue); }

#endif
};

template <class T>
struct Atomic : AtomicBase<T>
{
    using AtomicBase<T>::AtomicBase;
    using AtomicBase<T>::operator=;

    T fetchAdd(T x);
    T fetchSub(T x);
    T fetchAnd(T x);
    T fetchOr(T x);
    T fetchXor(T x);
    T increment() { return fetchAdd(1); }
    T decrement() { return fetchSub(1); }

    bool isBitOn(unsigned int bit) const;
    /// @return whether the bit was cleared and is now set.
    bool setBitOn(unsigned int bit);
    /// @return whether the bit was set and is now cleared.
    bool setBitOff(unsigned int bit);

    T operator+=(T x) { return fetchAdd(x); }
    T operator-=(T x) { return fetchSub(x); }
    T operator&=(T x) { return fetchAnd(x); }
    T operator|=(T x) { return fetchOr(x); }
    T operator^=(T x) { return fetchXor(x); }
    T operator++() { return fetchAdd(1) + 1; }
    T operator++(int) { return fetchAdd(1); }
    T operator--() { return fetchSub(1) - 1; }
    T operator--(int) { return fetchSub(1); }
};

/// Specialization for pointer types.
template <class T>
struct Atomic<T*> : AtomicBase<T*>
{
    using AtomicBase<T*>::AtomicBase;
    using AtomicBase<T*>::operator=;

    T& operator*() const { return *this->load(); }
    T* operator->() const { return this->load(); }
};

// Implementation.

#ifdef NNSDK
template <class T>
inline AtomicBase<T>::AtomicBase(T value)
{
    storeNonAtomic(value);
}

template <class T>
inline AtomicBase<T>::AtomicBase(AtomicDirectInitTag, T value) : mValue(value)
{
}

template <class T>
inline T AtomicBase<T>::load() const
{
#ifdef MATCHING_HACK_NX_CLANG
    // Using std::atomic<T>::load prevents LLVM from folding ldr+sext into ldrsw.
    return *getValuePtr();
#else
    return mValue.load(std::memory_order_relaxed);
#endif
}

template <class T>
inline void AtomicBase<T>::store(T value)
{
    mValue.store(value, std::memory_order_relaxed);
}

template <class T>
inline void AtomicBase<T>::storeNonAtomic(T value)
{
    *getValuePtr() = value;
}

template <class T>
inline T AtomicBase<T>::exchange(T value)
{
    return mValue.exchange(value, std::memory_order_relaxed);
}

template <class T>
inline bool AtomicBase<T>::compareExchange(T expected, T desired, T* original)
{
#ifdef MATCHING_HACK_NX_CLANG
    // Unlike Clang (https://reviews.llvm.org/D13033), Nintendo's implementation does not use clrex.
    do
    {
        T value = __builtin_arm_ldrex(getValuePtr());
        if (value != expected)
        {
            if (original)
                *original = value;
            return false;
        }
    } while (__builtin_arm_strex(desired, getValuePtr()));
    return true;
#else
    T value = expected;
    if (mValue.compare_exchange_strong(value, desired, std::memory_order_relaxed))
        return true;
    if (original)
        *original = value;
    return false;
#endif
}

#ifdef MATCHING_HACK_NX_CLANG
namespace detail
{
// To match Nintendo's implementation of atomics.
template <typename T, typename F>
inline T atomicReadModifyWrite(volatile T* value_ptr, F op)
{
    T value;
    do
    {
        value = __builtin_arm_ldrex(value_ptr);
    } while (__builtin_arm_strex(op(value), value_ptr));
    return value;
}
}  // namespace detail
#endif

template <class T>
inline T Atomic<T>::fetchAdd(T x)
{
#ifdef MATCHING_HACK_NX_CLANG
    return detail::atomicReadModifyWrite(this->getValuePtr(), [&](T val) { return val + x; });
#else
    return this->mValue.fetch_add(x, std::memory_order_relaxed);
#endif
}

template <class T>
inline T Atomic<T>::fetchSub(T x)
{
#ifdef MATCHING_HACK_NX_CLANG
    return detail::atomicReadModifyWrite(this->getValuePtr(), [&](T val) { return val - x; });
#else
    return this->mValue.fetch_sub(x, std::memory_order_relaxed);
#endif
}

template <class T>
inline T Atomic<T>::fetchAnd(T x)
{
#ifdef MATCHING_HACK_NX_CLANG
    return detail::atomicReadModifyWrite(this->getValuePtr(), [&](T val) { return val & x; });
#else
    return this->mValue.fetch_and(x, std::memory_order_relaxed);
#endif
}

template <class T>
inline T Atomic<T>::fetchOr(T x)
{
#ifdef MATCHING_HACK_NX_CLANG
    return detail::atomicReadModifyWrite(this->getValuePtr(), [&](T val) { return val | x; });
#else
    return this->mValue.fetch_or(x, std::memory_order_relaxed);
#endif
}

template <class T>
inline T Atomic<T>::fetchXor(T x)
{
#ifdef MATCHING_HACK_NX_CLANG
    return detail::atomicReadModifyWrite(this->getValuePtr(), [&](T val) { return val ^ x; });
#else
    return this->mValue.fetch_xor(x, std::memory_order_relaxed);
#endif
}

template <class T>
bool Atomic<T>::isBitOn(unsigned int bit) const
{
    return (this->load() & (1 << bit)) != 0;
}

template <class T>
bool Atomic<T>::setBitOn(unsigned int bit)
{
#ifdef MATCHING_HACK_NX_CLANG
    const auto old = detail::atomicReadModifyWrite(this->getValuePtr(),
                                                   [bit](T val) { return val | (1 << bit); });
#else
    const auto old = this->mValue.fetch_or(1 << bit, std::memory_order_relaxed);
#endif
    return (old & (1 << bit)) == 0;
}

template <class T>
bool Atomic<T>::setBitOff(unsigned int bit)
{
#ifdef MATCHING_HACK_NX_CLANG
    const auto old = detail::atomicReadModifyWrite(this->getValuePtr(),
                                                   [bit](T val) { return val & ~(1 << bit); });
#else
    const auto old = this->mValue.fetch_and(~(1 << bit), std::memory_order_relaxed);
#endif
    return (old & (1 << bit)) != 0;
}
#else  // NNSDK
#error "Unknown platform"
#endif
}  // namespace sead
