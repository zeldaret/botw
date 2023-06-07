#pragma once

#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resResource.h"
#include "resource/seadResource.h"

namespace ksys::res {

class Placement : public Resource {
    SEAD_RTTI_OVERRIDE(Placement, Resource)
public:
    Placement();
    ~Placement() override;

    void registerFactory(sead::Heap* heap);

    s64 mVar1;
    s64 mVar2;
};

}  // namespace ksys::res
