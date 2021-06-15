#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class LifeCondition : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(LifeCondition, Resource)
public:
    LifeCondition() : ParamIO("lifecondition", 0) {}
    ~LifeCondition() override = default;

    bool needsParse() const override { return true; }
    bool ParamIO_m0(char* data) override { return true; }

private:
    void doCreate_(u8*, u32, sead::Heap*) override {}
    void parseArray(const agl::utl::ResParameterObj* data, agl::utl::IParameterObj* obj,
                    sead::Buffer<agl::utl::Parameter<sead::SafeString>>* buffer,
                    const sead::SafeString& key, const sead::SafeString& desc, sead::Heap* heap);

    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    agl::utl::ParameterObj mInvalidWeathersObj;
    agl::utl::ParameterObj mInvalidTimesObj;
    agl::utl::ParameterObj mDisplayDistanceObj;
    agl::utl::ParameterObj mDeleteWeathersObj;
    agl::utl::ParameterObj mDeleteTimesObj;
    agl::utl::ParameterObj mBoundingYObj;
    agl::utl::ParameterObj mYLimitAlgorithmObj;

    sead::Buffer<agl::utl::Parameter<sead::SafeString>> mInvalidWeathersBuffer;
    sead::Buffer<agl::utl::Parameter<sead::SafeString>> mInvalidTimesBuffer;
    agl::utl::Parameter<f32> mDisplayDistance;
    agl::utl::Parameter<sead::SafeString> mBoundingY;
    agl::utl::Parameter<sead::SafeString> mYLimitAlgorithm;
    sead::Buffer<agl::utl::Parameter<sead::SafeString>> mDeleteWeathersBuffer;
    sead::Buffer<agl::utl::Parameter<sead::SafeString>> mDeleteTimesBuffer;
};

}  // namespace ksys::res
