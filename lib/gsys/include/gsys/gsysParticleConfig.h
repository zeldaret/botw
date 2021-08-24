#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterObj.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

class ParticleConfig : public sead::hostio::Node, public agl::utl::IParameterIO {
public:
    ParticleConfig();
    const char* getLightMapName(unsigned int) const;
    void initialize(sead::Heap*, sead::Heap*);
    void applyResource(const void*);

private:
    agl::utl::IParameterObj mData;               // unused
    short unk = 0;                               // unused
    sead::FixedSafeString<0x40> mUnknownString;  // unused
    agl::utl::ParameterObj mData2;
    agl::utl::Parameter<u32> mGpuParticleHeapSize;
    agl::utl::Parameter<u32> mEffectModelHeapSize;
    agl::utl::Parameter<u32> mPtclEmitCallbackHeapSize;
    agl::utl::Parameter<bool> mEnableParticleLinearDepth;
    agl::utl::Parameter<bool> mEnableBatchProcessStreamOut;
    agl::utl::Parameter<sead::FixedSafeString<0x40>> mLightMapName0;
    agl::utl::Parameter<sead::FixedSafeString<0x40>> mLightMapName1;
    agl::utl::Parameter<sead::FixedSafeString<0x40>> mLightMapName2;
    agl::utl::Parameter<sead::FixedSafeString<0x40>> mLightMapName3;
    agl::utl::Parameter<sead::FixedSafeString<0x40>> mLightMapName4;
    agl::utl::Parameter<sead::FixedSafeString<0x40>> mLightMapName5;
    agl::utl::Parameter<sead::FixedSafeString<0x40>> mLightMapName6;
    agl::utl::Parameter<sead::FixedSafeString<0x40>> mLightMapName7;
};

}  // namespace gsys
