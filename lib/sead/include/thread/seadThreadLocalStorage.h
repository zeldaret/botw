#pragma once

#ifdef NNSDK
#include <nn/os.h>
#endif

#include "basis/seadTypes.h"

namespace sead
{
class ThreadLocalStorage
{
public:
    ThreadLocalStorage();
    ~ThreadLocalStorage();

    ThreadLocalStorage(const ThreadLocalStorage&) = delete;
    ThreadLocalStorage& operator=(const ThreadLocalStorage&) = delete;

    void setValue(uintptr_t value);
    uintptr_t getValue() const;

private:
#ifdef NNSDK
    nn::os::TlsSlot mTlsSlot;
#endif
};
}  // namespace sead

#define SEAD_THREAD_THREAD_LOCAL_STORAGE_H_
#ifdef NNSDK
#include "thread/nin/seadThreadLocalStorageNin.hpp"
#else
#error "Unknown platform"
#endif
#undef SEAD_THREAD_THREAD_LOCAL_STORAGE_H_
