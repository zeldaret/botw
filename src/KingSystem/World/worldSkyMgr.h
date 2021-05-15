#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class SkyMgr : public Job {
    SEAD_RTTI_OVERRIDE(SkyMgr, Job)
public:
    struct PrCloud {
        agl::utl::Parameter<float> mScrollSpd;
        agl::utl::Parameter<float> mNoiseAdd1;
        agl::utl::Parameter<float> mNoiseAdd2;
        agl::utl::Parameter<float> mNoiseAdd1_side;
        agl::utl::Parameter<float> mNoiseAdd2_side;
        agl::utl::Parameter<float> mPosDensityChgRange;
        agl::utl::Parameter<float> mPosDensityChgPower;
        agl::utl::Parameter<float> mPosDensityChgSpeed;
        u32 _100;
        u8 _104;
        agl::utl::Parameter<float> mWindVecAdd;
        float _128;
        u32 _12c;
        agl::utl::Parameter<int> mBaseTextureNo;
        agl::utl::Parameter<int> mNoiseTextureNo;
        agl::utl::Parameter<bool> mbCloudTexBlend;
        agl::utl::Parameter<float> mCloudTexBlendRate;
        agl::utl::Parameter<int> mBaseTextureNo_Blend;
        agl::utl::Parameter<int> mNoiseTextureNo_Blend;
        agl::utl::ParameterObj mObj;
    };
    KSYS_CHECK_SIZE_NX150(PrCloud, 0x220);

    struct PrCloudV {
        agl::utl::Parameter<float> mDistotion;
        agl::utl::Parameter<float> mDensity;
        agl::utl::Parameter<float> mAlphaMul;
        agl::utl::Parameter<float> mAlphaThreshold;
        agl::utl::Parameter<float> mBaseTexScale;
        agl::utl::Parameter<float> mEmbossWidth;
        agl::utl::Parameter<float> mEmbossDensity;
        agl::utl::Parameter<float> mShadowPower;
        agl::utl::Parameter<float> mHighlightPower;
        agl::utl::Parameter<float> mHighlightRange;
        agl::utl::Parameter<float> mHighlightAmbient;
        agl::utl::Parameter<float> mSkyHeight;
        agl::utl::Parameter<float> mDensityMax;
        agl::utl::Parameter<float> mDensityMin;
        agl::utl::Parameter<float> mDensitySinSeedAdd;
        float _1e0;
        bool _1e4;
        agl::utl::Parameter<float> mAlphaMulMax;
        agl::utl::Parameter<float> mAlphaMulMin;
        agl::utl::Parameter<float> mAlphaMulSinSeedAdd;
        float _248;
        bool _24c;
        agl::utl::Parameter<float> mDistotionMax;
        agl::utl::Parameter<float> mDistotionMin;
        agl::utl::Parameter<float> mDistotionSinSeedAdd;
        float _2b0;
        bool _2b4;
        agl::utl::Parameter<float> mAlphaThresholdMax;
        agl::utl::Parameter<float> mAlphaThresholdMin;
        agl::utl::Parameter<float> mAlphaThresholdSinSeedAdd;
        float _318;
        bool _31c;
        agl::utl::Parameter<float> mSkyHeightMax;
        agl::utl::Parameter<float> mSkyHeightMin;
        agl::utl::Parameter<float> mSkyHeightSinSeedAdd;
        float _380;
        bool _384;
        agl::utl::Parameter<float> mBaseTexScaleMax;
        agl::utl::Parameter<float> mBaseTexScaleMin;
        agl::utl::Parameter<float> mBaseTexScaleSinSeedAdd;
        float _3e8;
        bool _3ec;
        agl::utl::Parameter<float> mBacklightPowe;
        agl::utl::Parameter<float> mBacklightRange;
        agl::utl::Parameter<float> mBacklightParam0;
        agl::utl::Parameter<float> mBacklightParam1;
        agl::utl::Parameter<float> mDarkSideNoiseParam;
        agl::utl::Parameter<float> mLightSideNoiseParam;
        agl::utl::ParameterObj mObj;
    };
    KSYS_CHECK_SIZE_NX150(PrCloudV, 0x4e0);

    struct SkyPalette {
        agl::utl::Parameter<float> mPosDensityChgPower;
        agl::utl::Parameter<float> mHeight;
        agl::utl::Parameter<float> mDistotion;
        agl::utl::Parameter<float> mDensity;
        agl::utl::Parameter<float> mAlphaMul;
        agl::utl::Parameter<float> mAlphaThreshold;
        agl::utl::Parameter<float> mBaseTexScale;
        agl::utl::Parameter<float> mSkyTexBlendRatio;
        agl::utl::ParameterObj mObj;
    };
    KSYS_CHECK_SIZE_NX150(SkyPalette, 0x130);

    static constexpr int NumSkyPalettes = 8;

    struct CloudPat {
        agl::utl::Parameter<float> mHeight;
        agl::utl::Parameter<float> mDistotion;
        agl::utl::Parameter<float> mDensity;
        agl::utl::Parameter<float> mAlphaMul;
        agl::utl::Parameter<float> mAlphaThreshold;
        agl::utl::Parameter<float> mTexBlendRatio;
        agl::utl::ParameterObj mObj;
    };
    KSYS_CHECK_SIZE_NX150(CloudPat, 0xf0);

    static constexpr int NumCloudPats = 3;

    struct CloudSpd {
        agl::utl::Parameter<float> mCloudPatNoisePow;
        agl::utl::Parameter<float> mCloudPatWindPow;
        agl::utl::ParameterObj mObj;
    };
    KSYS_CHECK_SIZE_NX150(CloudSpd, 0x70);

    SkyMgr();
    ~SkyMgr() override;

    void init_(sead::Heap* heap) override;
    void calcType2_() override;
    JobType getType() const override { return JobType::Sky; }

    void reset();
    void onTimeUpdate();

private:
    friend class Manager;

    struct StructA {
        sead::Vector3f _0;
        sead::Vector3f _c;
        sead::Vector3f _18;
        sead::Vector3f _24;
        sead::Vector3f _30;
        sead::Vector3f _3c;
    };
    StructA _20;
    u16 _68;
    sead::SafeArray<PrCloud, 3> mPrCloud;
    sead::SafeArray<sead::SafeArray<PrCloudV, 2>, 3> mPrCloudV;
    sead::SafeArray<SkyPalette, NumSkyPalettes> mSkyPalette0;
    sead::SafeArray<SkyPalette, NumSkyPalettes> mSkyPalette2;
    sead::SafeArray<CloudPat, NumCloudPats> mCloudPat0;
    sead::SafeArray<CloudPat, NumCloudPats> mCloudPat2;
    sead::SafeArray<CloudSpd, NumCloudPats> mCloudSpd;
    u8 _3e00[8];
    agl::utl::Parameter<float> mSunSlope;
    agl::utl::Parameter<float> mSunMoonDispDist;
    agl::utl::Parameter<float> mSunScale;
    agl::utl::Parameter<float> mMoonScale;
    agl::utl::Parameter<float> mSunDirYStop;
    agl::utl::ParameterObj mSunParamObj;
    sead::Vector3f _3ed8;
    sead::Vector3f _3ee4;
    sead::Vector3f _3ef0;
    sead::Vector3f _3efc;
    sead::Vector3f _3f08;
    sead::Vector3f _3f14;
    sead::Vector2f _3f20;
    sead::Vector2f _3f28;
    int _3f30;
    int _3f34;
    float _3f38;
    float _3f3c;
    float _3f40;
    float _3f44;
    float _3f48;
    float _3f4c;
    float _3f50;
    float _3f54;
    float _3f58;
    float _3f5c;
    int _3f60;
    int _3f64;
    float _3f68;
    float _3f6c;
    float _3f70;
    float _3f74;
    float _3f78;
    float _3f7c;
    float _3f80;
    float _3f84;
    float _3f88;
    float _3f8c;
    float _3f90;
    float _3f94;
    float _3f98;
    int _3f9c;
    int _3fa0;
    int _3fa4;
    int _3fa8;
    bool _3fac;
    bool _3fad;
    bool _3fae;
    bool _3faf;
    bool _3fb0;
    bool _3fb1;
};
KSYS_CHECK_SIZE_NX150(SkyMgr, 0x3fb8);

}  // namespace ksys::world
