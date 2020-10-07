#pragma once

#include <prim/seadSafeString.h>

namespace ksys::res {

// TODO: very incomplete
class CompactedHeap {
public:
    static CompactedHeap* tryCreate(const sead::SafeString& name, void* buffer, size_t buffer_size,
                                    u32 x);
    static CompactedHeap* create(const sead::SafeString& name, void* buffer, size_t buffer_size,
                                 u32 x);

    void destroy();

private:
    virtual ~CompactedHeap();
};

}  // namespace ksys::res
