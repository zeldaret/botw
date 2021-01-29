#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::evt {

class InfoDataUnknownType {
public:
    virtual ~InfoDataUnknownType();
};

class InfoData {
    SEAD_SINGLETON_DISPOSER(InfoData)
    InfoData();
    virtual ~InfoData();

public:
    bool getEntry(al::ByamlIter* iter, const sead::SafeString& event_flow_name,
                  const sead::SafeString& entry_point);
    bool getSceneChangeEventTraverseLimit(const sead::SafeString& event_flow_name);
    void init(sead::Heap* heap);

private:
    void doInit(sead::Heap* heap, OverlayArena* arena);
    al::ByamlIter* mRootIter = nullptr;
    ksys::res::Handle mHandle;
    InfoDataUnknownType* _80 = nullptr;
};

}  // namespace ksys::evt
