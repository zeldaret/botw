#pragma once

#include "KingSystem/Physics/System/physParamSet.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class Physics : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(Physics, Resource)
public:
    Physics() : ParamIO("physics", 0) {}

    phys::ParamSet& getParamSet() { return mParamSet; }

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }

private:
    phys::ParamSet mParamSet;
};

}  // namespace ksys::res
