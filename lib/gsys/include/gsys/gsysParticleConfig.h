#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterIO.h>
#include <agl/utl/aglParameterObj.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

class ParticleConfig : public sead::hostio::Node, public agl::utl::IParameterIO {
public:
    ParticleConfig();
    const char* getLightMapName(unsigned int index) const;
    void initialize(sead::Heap* heap, sead::Heap* hio_heap);
    void applyResouce(const void* data);

private:
    [[maybe_unused]] agl::utl::IParameterObj _1d8;      // unused
    [[maybe_unused]] short _208 = 0;                    // unused
    [[maybe_unused]] sead::FixedSafeString<0x40> _210;  // unused
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
