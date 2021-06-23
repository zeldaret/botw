#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace al {
class ByamlIter;
}

namespace ksys::qst {

struct CameraTarget {
    virtual ~CameraTarget();
    bool enabled;
    sead::SafeString name;
};
KSYS_CHECK_SIZE_NX150(CameraTarget, 0x20);

struct ActorData {
    ActorData(sead::Heap* heap);
    virtual ~ActorData();

    bool init(al::ByamlIter* iter, sead::BufferedSafeString* out_message);
    const CameraTarget* getTarget(int idx) const;
    void disableAllTargets();
    void enableAllTargets();

    sead::PtrArray<CameraTarget> targets;
    sead::Heap* heap;
};
KSYS_CHECK_SIZE_NX150(ActorData, 0x20);

}  // namespace ksys::qst
