#ifndef SEAD_THREAD_THREAD_LOCAL_STORAGE_H_
#include "thread/seadThreadLocalStorage.h"
#endif

#include "basis/seadRawPrint.h"

namespace sead
{
inline ThreadLocalStorage::ThreadLocalStorage()
{
    [[maybe_unused]] auto result = nn::os::AllocateTlsSlot(&mTlsSlot, nullptr);
    SEAD_ASSERT(result.IsSuccess());
}

inline ThreadLocalStorage::~ThreadLocalStorage()
{
    nn::os::FreeTlsSlot(mTlsSlot);
}

inline void ThreadLocalStorage::setValue(uintptr_t value)
{
    static_assert(sizeof(uintptr_t) == sizeof(u64), "uintptr_t and u64 should have the same size");
    nn::os::SetTlsValue(mTlsSlot, value);
}

inline uintptr_t ThreadLocalStorage::getValue() const
{
    return nn::os::GetTlsValue(mTlsSlot);
}
}  // namespace sead
