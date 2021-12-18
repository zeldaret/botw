#pragma once

#include <Havok/Common/Base/Types/hkBaseDefs.h>

namespace hkAtomic {

/// Weak compare-and-swap.
template <typename T>
HK_FORCE_INLINE bool compareAndSwap(volatile T* address, const T& oldValue, const T& newValue) {
    T expected = oldValue;
    return __atomic_compare_exchange_n(address, &expected, newValue, false, __ATOMIC_SEQ_CST,
                                       __ATOMIC_SEQ_CST);
}

template <typename T, typename Fn>
HK_FORCE_INLINE T readModifyWrite(volatile T* address, const Fn& getNewValue) {
    T oldVal, newVal;
    do {
        oldVal = *address;
        newVal = getNewValue(oldVal);
    } while (!hkAtomic::compareAndSwap(address, oldVal, newVal));
    return newVal;
}

}  // namespace hkAtomic
