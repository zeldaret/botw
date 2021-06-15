#pragma once

#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace al {
class ByamlIter;
}

namespace sead {
class Heap;
}

namespace ksys::res {

class AS;
class Handle;

class DemoASLoader {
public:
    DemoASLoader(const sead::SafeString& event_name, sead::Heap* heap);
    virtual ~DemoASLoader();

    void load(const al::ByamlIter& iter, bool synchronous, Handle* pack_handle);

    const char* getName(int idx) const;
    AS* getAS(int idx) const;

    /// @return whether the load has finished (succeeded or failed).
    bool finishLoad();

private:
    enum class Status {
        Uninitialized = 0,
        Loading = 1,
        Succeeded = 2,
        Failed = 3,
    };

    sead::Heap* mHeap = nullptr;
    sead::Buffer<Handle> mHandles;
    sead::Buffer<sead::FixedSafeString<64>> mNames;
    sead::FixedSafeString<64> mEventName;
    int mNumAS = 0;
    Status mStatus = Status::Uninitialized;
};
KSYS_CHECK_SIZE_NX150(DemoASLoader, 0x90);

}  // namespace ksys::res
