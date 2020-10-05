#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class LifeCondition : public ParamIO, public Resource {
    void parseArray(const agl::utl::ResParameterObj* data, agl::utl::IParameterObj* obj,
                    sead::Buffer<agl::utl::Parameter<sead::SafeString>>* buffer,
                    const sead::SafeString& key, const sead::SafeString& desc, sead::Heap* heap);

    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    agl::utl::IParameterObj mInvalidWeathersObj;
    agl::utl::IParameterObj mInvalidTimesObj;
    agl::utl::IParameterObj mDisplayDistanceObj;
    agl::utl::IParameterObj mDeleteWeathersObj;
    agl::utl::IParameterObj mDeleteTimesObj;
    agl::utl::IParameterObj mBoundingYObj;
    agl::utl::IParameterObj mYLimitAlgorithmObj;

    sead::Buffer<agl::utl::Parameter<sead::SafeString>> mInvalidWeathersBuffer;
    sead::Buffer<agl::utl::Parameter<sead::SafeString>> mInvalidTimesBuffer;
    agl::utl::Parameter<f32> mDisplayDistance;
    agl::utl::Parameter<sead::SafeString> mBoundingY;
    agl::utl::Parameter<sead::SafeString> mYLimitAlgorithm;
    sead::Buffer<agl::utl::Parameter<sead::SafeString>> mDeleteWeathersBuffer;
    sead::Buffer<agl::utl::Parameter<sead::SafeString>> mDeleteTimesBuffer;
};

}  // namespace ksys::res
