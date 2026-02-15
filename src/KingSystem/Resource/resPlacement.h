#pragma once

#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resResource.h"
#include "resource/seadResource.h"

namespace ksys::res {

class Placement : public Resource {
    SEAD_RTTI_OVERRIDE(Placement, Resource)

public:
    Placement() = default;
    ~Placement() override = default;

    static void registerFactory(sead::Heap* heap);

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;

    void* mUnknown1 = nullptr;
    void* mUnknown2 = nullptr;
};

}  // namespace ksys::res
