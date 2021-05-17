#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterObj.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class Lod : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(Lod, Resource)
public:
    Lod() : ParamIO("lod", 0) {}
    ~Lod() override = default;

    bool ParamIO_m0(char* data) override { return true; }
    void doCreate_(u8*, u32, sead::Heap*) override {}
    bool needsParse() const override { return true; }

protected:
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    agl::utl::ParameterObj mHeader;

public:
    agl::utl::Parameter<bool> mDisableOutScreenCalcStop;
    agl::utl::Parameter<bool> mDisableXLinkSkip;
    agl::utl::Parameter<s32> mDisableCalcSkipFrame;
    agl::utl::Parameter<bool> mDisableConstActor;
    agl::utl::Parameter<f32> mDistanceScale;
    agl::utl::Parameter<bool> mDisableBehaviorSkip;
    agl::utl::Parameter<bool> mDisableCalcRescueDistLimit;
};
KSYS_CHECK_SIZE_NX150(Lod, 0x3c0);

}  // namespace ksys::res
