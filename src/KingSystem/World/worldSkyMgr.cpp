#include "KingSystem/World/worldSkyMgr.h"
#include <cmath>
#include <math/seadMathNumbers.h>
#include <random/seadGlobalRandom.h>

namespace ksys::world {

static void normalize(sead::Vector3f& v) {
    const auto norm = sead::norm2(v);
    if (norm > 0.0)
        v *= 1.0f / norm;
}

SkyMgr::SkyMgr() {
    _20._18 = {0, 0, 0};
    _20._24 = {0, 0, 0};
    _3f08.x = 0.572061;
    _3f08.y = -0.707107;
    _3f08.z = -0.415627;
    _20._0 = {0, 0, 0};
    _20._c = {0, 0, 0};
    _3f20.x = sead::GlobalRandom::instance()->getF32();
    _3f20.y = sead::GlobalRandom::instance()->getF32();

    mPrCloud[0].mScrollSpd.init(-0.35, "ScrollSpd", "", &mPrCloud[0].mObj);
    mPrCloud[0].mNoiseAdd1.init(-0.75, "NoiseAdd1", "", &mPrCloud[0].mObj);
    mPrCloud[0].mNoiseAdd2.init(-0.2, "NoiseAdd2", "", &mPrCloud[0].mObj);
    mPrCloud[0].mNoiseAdd1_side.init(-0.2, "NoiseAdd1_side", "", &mPrCloud[0].mObj);
    mPrCloud[0].mNoiseAdd2_side.init(-0.3, "NoiseAdd2_side", "", &mPrCloud[0].mObj);
    mPrCloud[0].mPosDensityChgRange.init(0.0, "PosDensityChgRange", "", &mPrCloud[0].mObj);
    mPrCloud[0].mPosDensityChgPower.init(0.0, "PosDensityChgPower", "", &mPrCloud[0].mObj);
    mPrCloud[0].mPosDensityChgSpeed.init(0.0, "PosDensityChgSpeed", "", &mPrCloud[0].mObj);
    mPrCloud[0].mWindVecAdd.init(0.262, "WindVecAdd", "", &mPrCloud[0].mObj);
    mPrCloud[0].mBaseTextureNo.init(2, "BaseTextureNo", "", &mPrCloud[0].mObj);
    mPrCloud[0].mNoiseTextureNo.init(3, "NoiseTextureNo", "", &mPrCloud[0].mObj);
    mPrCloud[0].mbCloudTexBlend.init(false, "bCloudTexBlend", "", &mPrCloud[0].mObj);
    mPrCloud[0].mCloudTexBlendRate.init(0.0, "CloudTexBlendRate", "", &mPrCloud[0].mObj);
    mPrCloud[0].mBaseTextureNo_Blend.init(4, "BaseTextureNo_Blend", "", &mPrCloud[0].mObj);
    mPrCloud[0].mNoiseTextureNo_Blend.init(4, "NoiseTextureNo_Blend", "", &mPrCloud[0].mObj);

    mPrCloud[1].mScrollSpd.init(-0.5, "ScrollSpd", "", &mPrCloud[1].mObj);
    mPrCloud[1].mNoiseAdd1.init(-0.25, "NoiseAdd1", "", &mPrCloud[1].mObj);
    mPrCloud[1].mNoiseAdd2.init(-0.5, "NoiseAdd2", "", &mPrCloud[1].mObj);
    mPrCloud[1].mNoiseAdd1_side.init(-0.2, "NoiseAdd1_side", "", &mPrCloud[1].mObj);
    mPrCloud[1].mNoiseAdd2_side.init(-0.3, "NoiseAdd2_side", "", &mPrCloud[1].mObj);
    mPrCloud[1].mPosDensityChgRange.init(0.0, "PosDensityChgRange", "", &mPrCloud[1].mObj);
    mPrCloud[1].mPosDensityChgPower.init(0.0, "PosDensityChgPower", "", &mPrCloud[1].mObj);
    mPrCloud[1].mPosDensityChgSpeed.init(0.0, "PosDensityChgSpeed", "", &mPrCloud[1].mObj);
    mPrCloud[1].mWindVecAdd.init(0.0, "WindVecAdd", "", &mPrCloud[1].mObj);
    mPrCloud[1].mBaseTextureNo.init(2, "BaseTextureNo", "", &mPrCloud[1].mObj);
    mPrCloud[1].mNoiseTextureNo.init(3, "NoiseTextureNo", "", &mPrCloud[1].mObj);
    mPrCloud[1].mbCloudTexBlend.init(false, "bCloudTexBlend", "", &mPrCloud[1].mObj);
    mPrCloud[1].mCloudTexBlendRate.init(0.0, "CloudTexBlendRate", "", &mPrCloud[1].mObj);
    mPrCloud[1].mBaseTextureNo_Blend.init(4, "BaseTextureNo_Blend", "", &mPrCloud[1].mObj);
    mPrCloud[1].mNoiseTextureNo_Blend.init(4, "NoiseTextureNo_Blend", "", &mPrCloud[1].mObj);

    mPrCloud[2].mScrollSpd.init(-0.5, "ScrollSpd", "", &mPrCloud[2].mObj);
    mPrCloud[2].mNoiseAdd1.init(-0.25, "NoiseAdd1", "", &mPrCloud[2].mObj);
    mPrCloud[2].mNoiseAdd2.init(-0.5, "NoiseAdd2", "", &mPrCloud[2].mObj);
    mPrCloud[2].mNoiseAdd1_side.init(-0.2, "NoiseAdd1_side", "", &mPrCloud[2].mObj);
    mPrCloud[2].mNoiseAdd2_side.init(-0.3, "NoiseAdd2_side", "", &mPrCloud[2].mObj);
    mPrCloud[2].mPosDensityChgRange.init(0.0, "PosDensityChgRange", "", &mPrCloud[2].mObj);
    mPrCloud[2].mPosDensityChgPower.init(0.0, "PosDensityChgPower", "", &mPrCloud[2].mObj);
    mPrCloud[2].mPosDensityChgSpeed.init(0.0, "PosDensityChgSpeed", "", &mPrCloud[2].mObj);
    mPrCloud[2].mWindVecAdd.init(0.0, "WindVecAdd", "", &mPrCloud[2].mObj);
    mPrCloud[2].mBaseTextureNo.init(2, "BaseTextureNo", "", &mPrCloud[2].mObj);
    mPrCloud[2].mNoiseTextureNo.init(3, "NoiseTextureNo", "", &mPrCloud[2].mObj);
    mPrCloud[2].mbCloudTexBlend.init(false, "bCloudTexBlend", "", &mPrCloud[2].mObj);
    mPrCloud[2].mCloudTexBlendRate.init(0.0, "CloudTexBlendRate", "", &mPrCloud[2].mObj);
    mPrCloud[2].mBaseTextureNo_Blend.init(4, "BaseTextureNo_Blend", "", &mPrCloud[2].mObj);
    mPrCloud[2].mNoiseTextureNo_Blend.init(3, "NoiseTextureNo_Blend", "", &mPrCloud[2].mObj);

    *mPrCloud[0].mNoiseTextureNo_Blend = 3;
    *mPrCloud[2].mNoiseTextureNo_Blend = 3;
    mPrCloud[0]._128 = 1.0;
    mPrCloud[1]._128 = 1.0;
    mPrCloud[2]._128 = 1.0;
    mPrCloud[0]._104 = 0;
    mPrCloud[1]._104 = 0;
    mPrCloud[2]._104 = 0;
    mPrCloud[0]._100 = 0;
    mPrCloud[1]._100 = 0;
    mPrCloud[2]._100 = 0;

    auto& prv0_0 = mPrCloudV[0][0];
    prv0_0.mDistotion.init(0.6, "Distotion", "", &prv0_0.mObj);
    prv0_0.mDistotionMax.init(0.6, "DistotionMax", "", &prv0_0.mObj);
    prv0_0.mDistotionMin.init(0.6, "DistotionMin", "", &prv0_0.mObj);
    prv0_0.mDistotionSinSeedAdd.init(0.0, "DistotionSinSeedAdd", "", &prv0_0.mObj);
    prv0_0.mDensity.init(0.3, "Density", "", &prv0_0.mObj);
    prv0_0.mDensityMax.init(0.3, "DensityMax", "", &prv0_0.mObj);
    prv0_0.mDensityMin.init(0.3, "DensityMin", "", &prv0_0.mObj);
    prv0_0.mDensitySinSeedAdd.init(0.0, "DensitySinSeedAdd", "", &prv0_0.mObj);
    prv0_0.mAlphaMul.init(0.4, "AlphaMul", "", &prv0_0.mObj);
    prv0_0.mAlphaMulMax.init(0.4, "AlphaMulMax", "", &prv0_0.mObj);
    prv0_0.mAlphaMulMin.init(0.4, "AlphaMulMin", "", &prv0_0.mObj);
    prv0_0.mAlphaMulSinSeedAdd.init(0.0, "AlphaMulSinSeedAdd", "", &prv0_0.mObj);
    prv0_0.mAlphaThreshold.init(0.7, "AlphaThreshold", "", &prv0_0.mObj);
    prv0_0.mAlphaThresholdMax.init(0.7, "AlphaThresholdMax", "", &prv0_0.mObj);
    prv0_0.mAlphaThresholdMin.init(0.7, "AlphaThresholdMin", "", &prv0_0.mObj);
    prv0_0.mAlphaThresholdSinSeedAdd.init(0.0, "AlphaThresholdSinSeedAdd", "", &prv0_0.mObj);
    prv0_0.mBaseTexScale.init(1.0, "BaseTexScale", "", &prv0_0.mObj);
    prv0_0.mBaseTexScaleMax.init(1.0, "BaseTexScaleMax", "", &prv0_0.mObj);
    prv0_0.mBaseTexScaleMin.init(1.0, "BaseTexScaleMin", "", &prv0_0.mObj);
    prv0_0.mBaseTexScaleSinSeedAdd.init(0.0, "BaseTexScaleSinSeedAdd", "", &prv0_0.mObj);
    prv0_0.mEmbossWidth.init(1.0, "EmbossWidth", "", &prv0_0.mObj);
    prv0_0.mEmbossDensity.init(1.0, "EmbossDensity", "", &prv0_0.mObj);
    prv0_0.mShadowPower.init(0.249, "ShadowPower", "", &prv0_0.mObj);
    prv0_0.mHighlightPower.init(1.0, "HighlightPower", "", &prv0_0.mObj);
    prv0_0.mHighlightRange.init(0.8, "HighlightRange", "", &prv0_0.mObj);
    prv0_0.mHighlightAmbient.init(0.1, "HighlightAmbient", "", &prv0_0.mObj);
    prv0_0.mSkyHeight.init(15000.0, "SkyHeight", "", &prv0_0.mObj);
    prv0_0.mSkyHeightMax.init(15000.0, "SkyHeightMax", "", &prv0_0.mObj);
    prv0_0.mSkyHeightMin.init(15000.0, "SkyHeightMin", "", &prv0_0.mObj);
    prv0_0.mSkyHeightSinSeedAdd.init(0.0, "SkyHeightSinSeedAdd", "", &prv0_0.mObj);
    prv0_0.mBacklightPowe.init(1.5, "BacklightPowe", "", &prv0_0.mObj);
    prv0_0.mBacklightRange.init(0.65, "BacklightRange", "", &prv0_0.mObj);
    prv0_0.mBacklightParam0.init(0.2, "BacklightParam0", "", &prv0_0.mObj);
    prv0_0.mBacklightParam1.init(0.45, "BacklightParam1", "", &prv0_0.mObj);
    prv0_0.mDarkSideNoiseParam.init(1.0, "DarkSideNoiseParam", "", &prv0_0.mObj);
    prv0_0.mLightSideNoiseParam.init(0.25, "LightSideNoiseParam", "", &prv0_0.mObj);

    auto& prv0_1 = mPrCloudV[0][1];
    prv0_1.mDistotion.init(0.6, "Distotion", "", &prv0_1.mObj);
    prv0_1.mDistotionMax.init(0.6, "DistotionMax", "", &prv0_1.mObj);
    prv0_1.mDistotionMin.init(0.6, "DistotionMin", "", &prv0_1.mObj);
    prv0_1.mDistotionSinSeedAdd.init(0.0, "DistotionSinSeedAdd", "", &prv0_1.mObj);
    prv0_1.mDensity.init(0.65, "Density", "", &prv0_1.mObj);
    prv0_1.mDensityMax.init(0.65, "DensityMax", "", &prv0_1.mObj);
    prv0_1.mDensityMin.init(0.65, "DensityMin", "", &prv0_1.mObj);
    prv0_1.mDensitySinSeedAdd.init(0.0, "DensitySinSeedAdd", "", &prv0_1.mObj);
    prv0_1.mAlphaMul.init(0.65, "AlphaMul", "", &prv0_1.mObj);
    prv0_1.mAlphaMulMax.init(0.65, "AlphaMulMax", "", &prv0_1.mObj);
    prv0_1.mAlphaMulMin.init(0.65, "AlphaMulMin", "", &prv0_1.mObj);
    prv0_1.mAlphaMulSinSeedAdd.init(0.0, "AlphaMulSinSeedAdd", "", &prv0_1.mObj);
    prv0_1.mAlphaThreshold.init(0.95, "AlphaThreshold", "", &prv0_1.mObj);
    prv0_1.mAlphaThresholdMax.init(0.95, "AlphaThresholdMax", "", &prv0_1.mObj);
    prv0_1.mAlphaThresholdMin.init(0.95, "AlphaThresholdMin", "", &prv0_1.mObj);
    prv0_1.mAlphaThresholdSinSeedAdd.init(0.0, "AlphaThresholdSinSeedAdd", "", &prv0_1.mObj);
    prv0_1.mBaseTexScale.init(1.0, "BaseTexScale", "", &prv0_1.mObj);
    prv0_1.mBaseTexScaleMax.init(1.0, "BaseTexScaleMax", "", &prv0_1.mObj);
    prv0_1.mBaseTexScaleMin.init(1.0, "BaseTexScaleMin", "", &prv0_1.mObj);
    prv0_1.mBaseTexScaleSinSeedAdd.init(0.0, "BaseTexScaleSinSeedAdd", "", &prv0_1.mObj);
    prv0_1.mEmbossWidth.init(0.06, "EmbossWidth", "", &prv0_1.mObj);
    prv0_1.mEmbossDensity.init(0.039, "EmbossDensity", "", &prv0_1.mObj);
    prv0_1.mShadowPower.init(0.223, "ShadowPower", "", &prv0_1.mObj);
    prv0_1.mHighlightPower.init(1.0, "HighlightPower", "", &prv0_1.mObj);
    prv0_1.mHighlightRange.init(0.8, "HighlightRange", "", &prv0_1.mObj);
    prv0_1.mHighlightAmbient.init(0.1, "HighlightAmbient", "", &prv0_1.mObj);
    prv0_1.mSkyHeight.init(13000.0, "SkyHeight", "", &prv0_1.mObj);
    prv0_1.mSkyHeightMax.init(13000.0, "SkyHeightMax", "", &prv0_1.mObj);
    prv0_1.mSkyHeightMin.init(13000.0, "SkyHeightMin", "", &prv0_1.mObj);
    prv0_1.mSkyHeightSinSeedAdd.init(0.0, "SkyHeightSinSeedAdd", "", &prv0_1.mObj);
    prv0_1.mBacklightPowe.init(1.5, "BacklightPowe", "", &prv0_1.mObj);
    prv0_1.mBacklightRange.init(0.65, "BacklightRange", "", &prv0_1.mObj);
    prv0_1.mBacklightParam0.init(0.2, "BacklightParam0", "", &prv0_1.mObj);
    prv0_1.mBacklightParam1.init(0.45, "BacklightParam1", "", &prv0_1.mObj);
    prv0_1.mDarkSideNoiseParam.init(0.5, "DarkSideNoiseParam", "", &prv0_1.mObj);
    prv0_1.mLightSideNoiseParam.init(1.0, "LightSideNoiseParam", "", &prv0_1.mObj);

    auto& prv1_0 = mPrCloudV[1][0];
    prv1_0.mDistotion.init(0.6, "Distotion", "", &prv1_0.mObj);
    prv1_0.mDistotionMax.init(0.6, "DistotionMax", "", &prv1_0.mObj);
    prv1_0.mDistotionMin.init(0.6, "DistotionMin", "", &prv1_0.mObj);
    prv1_0.mDistotionSinSeedAdd.init(0.0, "DistotionSinSeedAdd", "", &prv1_0.mObj);
    prv1_0.mDensity.init(0.2, "Density", "", &prv1_0.mObj);
    prv1_0.mDensityMax.init(0.05, "DensityMax", "", &prv1_0.mObj);
    prv1_0.mDensityMin.init(0.05, "DensityMin", "", &prv1_0.mObj);
    prv1_0.mDensitySinSeedAdd.init(0.01, "DensitySinSeedAdd", "", &prv1_0.mObj);
    prv1_0.mAlphaMul.init(0.4, "AlphaMul", "", &prv1_0.mObj);
    prv1_0.mAlphaMulMax.init(0.4, "AlphaMulMax", "", &prv1_0.mObj);
    prv1_0.mAlphaMulMin.init(0.4, "AlphaMulMin", "", &prv1_0.mObj);
    prv1_0.mAlphaMulSinSeedAdd.init(0.0, "AlphaMulSinSeedAdd", "", &prv1_0.mObj);
    prv1_0.mAlphaThreshold.init(0.7, "AlphaThreshold", "", &prv1_0.mObj);
    prv1_0.mAlphaThresholdMax.init(0.7, "AlphaThresholdMax", "", &prv1_0.mObj);
    prv1_0.mAlphaThresholdMin.init(0.7, "AlphaThresholdMin", "", &prv1_0.mObj);
    prv1_0.mAlphaThresholdSinSeedAdd.init(0.0, "AlphaThresholdSinSeedAdd", "", &prv1_0.mObj);
    prv1_0.mBaseTexScale.init(1.0, "BaseTexScale", "", &prv1_0.mObj);
    prv1_0.mBaseTexScaleMax.init(1.0, "BaseTexScaleMax", "", &prv1_0.mObj);
    prv1_0.mBaseTexScaleMin.init(1.0, "BaseTexScaleMin", "", &prv1_0.mObj);
    prv1_0.mBaseTexScaleSinSeedAdd.init(0.0, "BaseTexScaleSinSeedAdd", "", &prv1_0.mObj);
    prv1_0.mEmbossWidth.init(1.0, "EmbossWidth", "", &prv1_0.mObj);
    prv1_0.mEmbossDensity.init(1.0, "EmbossDensity", "", &prv1_0.mObj);
    prv1_0.mShadowPower.init(0.249, "ShadowPower", "", &prv1_0.mObj);
    prv1_0.mHighlightPower.init(1.0, "HighlightPower", "", &prv1_0.mObj);
    prv1_0.mHighlightRange.init(0.8, "HighlightRange", "", &prv1_0.mObj);
    prv1_0.mHighlightAmbient.init(0.1, "HighlightAmbient", "", &prv1_0.mObj);
    prv1_0.mSkyHeight.init(15000.0, "SkyHeight", "", &prv1_0.mObj);
    prv1_0.mSkyHeightMax.init(15000.0, "SkyHeightMax", "", &prv1_0.mObj);
    prv1_0.mSkyHeightMin.init(15000.0, "SkyHeightMin", "", &prv1_0.mObj);
    prv1_0.mSkyHeightSinSeedAdd.init(0.0, "SkyHeightSinSeedAdd", "", &prv1_0.mObj);
    prv1_0.mBacklightPowe.init(1.5, "BacklightPowe", "", &prv1_0.mObj);
    prv1_0.mBacklightRange.init(0.65, "BacklightRange", "", &prv1_0.mObj);
    prv1_0.mBacklightParam0.init(0.2, "BacklightParam0", "", &prv1_0.mObj);
    prv1_0.mBacklightParam1.init(0.45, "BacklightParam1", "", &prv1_0.mObj);
    prv1_0.mDarkSideNoiseParam.init(1.0, "DarkSideNoiseParam", "", &prv1_0.mObj);
    prv1_0.mLightSideNoiseParam.init(0.25, "LightSideNoiseParam", "", &prv1_0.mObj);

    auto& prv1_1 = mPrCloudV[1][1];
    prv1_1.mDistotion.init(1.0, "Distotion", "", &prv1_1.mObj);
    prv1_1.mDistotionMax.init(1.0, "DistotionMax", "", &prv1_1.mObj);
    prv1_1.mDistotionMin.init(1.0, "DistotionMin", "", &prv1_1.mObj);
    prv1_1.mDistotionSinSeedAdd.init(0.0, "DistotionSinSeedAdd", "", &prv1_1.mObj);
    prv1_1.mDensity.init(0.5, "Density", "", &prv1_1.mObj);
    prv1_1.mDensityMax.init(0.5, "DensityMax", "", &prv1_1.mObj);
    prv1_1.mDensityMin.init(0.5, "DensityMin", "", &prv1_1.mObj);
    prv1_1.mDensitySinSeedAdd.init(0.0, "DensitySinSeedAdd", "", &prv1_1.mObj);
    prv1_1.mAlphaMul.init(1.0, "AlphaMul", "", &prv1_1.mObj);
    prv1_1.mAlphaMulMax.init(1.0, "AlphaMulMax", "", &prv1_1.mObj);
    prv1_1.mAlphaMulMin.init(1.0, "AlphaMulMin", "", &prv1_1.mObj);
    prv1_1.mAlphaMulSinSeedAdd.init(0.0, "AlphaMulSinSeedAdd", "", &prv1_1.mObj);
    prv1_1.mAlphaThreshold.init(1.0, "AlphaThreshold", "", &prv1_1.mObj);
    prv1_1.mAlphaThresholdMax.init(1.0, "AlphaThresholdMax", "", &prv1_1.mObj);
    prv1_1.mAlphaThresholdMin.init(1.0, "AlphaThresholdMin", "", &prv1_1.mObj);
    prv1_1.mAlphaThresholdSinSeedAdd.init(0.0, "AlphaThresholdSinSeedAdd", "", &prv1_1.mObj);
    prv1_1.mBaseTexScale.init(1.0, "BaseTexScale", "", &prv1_1.mObj);
    prv1_1.mBaseTexScaleMax.init(1.0, "BaseTexScaleMax", "", &prv1_1.mObj);
    prv1_1.mBaseTexScaleMin.init(1.0, "BaseTexScaleMin", "", &prv1_1.mObj);
    prv1_1.mBaseTexScaleSinSeedAdd.init(0.0, "BaseTexScaleSinSeedAdd", "", &prv1_1.mObj);
    prv1_1.mEmbossWidth.init(1.0, "EmbossWidth", "", &prv1_1.mObj);
    prv1_1.mEmbossDensity.init(1.0, "EmbossDensity", "", &prv1_1.mObj);
    prv1_1.mShadowPower.init(0.249, "ShadowPower", "", &prv1_1.mObj);
    prv1_1.mHighlightPower.init(1.0, "HighlightPower", "", &prv1_1.mObj);
    prv1_1.mHighlightRange.init(0.8, "HighlightRange", "", &prv1_1.mObj);
    prv1_1.mHighlightAmbient.init(0.1, "HighlightAmbient", "", &prv1_1.mObj);
    prv1_1.mSkyHeight.init(15000.0, "SkyHeight", "", &prv1_1.mObj);
    prv1_1.mSkyHeightMax.init(15000.0, "SkyHeightMax", "", &prv1_1.mObj);
    prv1_1.mSkyHeightMin.init(15000.0, "SkyHeightMin", "", &prv1_1.mObj);
    prv1_1.mSkyHeightSinSeedAdd.init(0.0, "SkyHeightSinSeedAdd", "", &prv1_1.mObj);
    prv1_1.mBacklightPowe.init(1.5, "BacklightPowe", "", &prv1_1.mObj);
    prv1_1.mBacklightRange.init(0.65, "BacklightRange", "", &prv1_1.mObj);
    prv1_1.mBacklightParam0.init(0.2, "BacklightParam0", "", &prv1_1.mObj);
    prv1_1.mBacklightParam1.init(0.45, "BacklightParam1", "", &prv1_1.mObj);
    prv1_1.mDarkSideNoiseParam.init(0.5, "DarkSideNoiseParam", "", &prv1_1.mObj);
    prv1_1.mLightSideNoiseParam.init(1.0, "LightSideNoiseParam", "", &prv1_1.mObj);

    auto& prv2_0 = mPrCloudV[2][0];
    prv2_0.mDistotion.init(0.6, "Distotion", "", &prv2_0.mObj);
    prv2_0.mDistotionMax.init(0.6, "DistotionMax", "", &prv2_0.mObj);
    prv2_0.mDistotionMin.init(0.6, "DistotionMin", "", &prv2_0.mObj);
    prv2_0.mDistotionSinSeedAdd.init(0.0, "DistotionSinSeedAdd", "", &prv2_0.mObj);
    prv2_0.mDensity.init(0.3, "Density", "", &prv2_0.mObj);
    prv2_0.mDensityMax.init(0.3, "DensityMax", "", &prv2_0.mObj);
    prv2_0.mDensityMin.init(0.3, "DensityMin", "", &prv2_0.mObj);
    prv2_0.mDensitySinSeedAdd.init(0.0, "DensitySinSeedAdd", "", &prv2_0.mObj);
    prv2_0.mAlphaMul.init(1.0, "AlphaMul", "", &prv2_0.mObj);
    prv2_0.mAlphaMulMax.init(1.0, "AlphaMulMax", "", &prv2_0.mObj);
    prv2_0.mAlphaMulMin.init(1.0, "AlphaMulMin", "", &prv2_0.mObj);
    prv2_0.mAlphaMulSinSeedAdd.init(0.0, "AlphaMulSinSeedAdd", "", &prv2_0.mObj);
    prv2_0.mAlphaThreshold.init(0.7, "AlphaThreshold", "", &prv2_0.mObj);
    prv2_0.mAlphaThresholdMax.init(0.7, "AlphaThresholdMax", "", &prv2_0.mObj);
    prv2_0.mAlphaThresholdMin.init(0.7, "AlphaThresholdMin", "", &prv2_0.mObj);
    prv2_0.mAlphaThresholdSinSeedAdd.init(0.0, "AlphaThresholdSinSeedAdd", "", &prv2_0.mObj);
    prv2_0.mBaseTexScale.init(1.0, "BaseTexScale", "", &prv2_0.mObj);
    prv2_0.mBaseTexScaleMax.init(1.0, "BaseTexScaleMax", "", &prv2_0.mObj);
    prv2_0.mBaseTexScaleMin.init(1.0, "BaseTexScaleMin", "", &prv2_0.mObj);
    prv2_0.mBaseTexScaleSinSeedAdd.init(0.0, "BaseTexScaleSinSeedAdd", "", &prv2_0.mObj);
    prv2_0.mEmbossWidth.init(0.08904, "EmbossWidth", "", &prv2_0.mObj);
    prv2_0.mEmbossDensity.init(0.5, "EmbossDensity", "", &prv2_0.mObj);
    prv2_0.mShadowPower.init(0.75, "ShadowPower", "", &prv2_0.mObj);
    prv2_0.mHighlightPower.init(20.0, "HighlightPower", "", &prv2_0.mObj);
    prv2_0.mHighlightRange.init(1.7, "HighlightRange", "", &prv2_0.mObj);
    prv2_0.mHighlightAmbient.init(0.5, "HighlightAmbient", "", &prv2_0.mObj);
    prv2_0.mSkyHeight.init(14500.0, "SkyHeight", "", &prv2_0.mObj);
    prv2_0.mSkyHeightMax.init(14500.0, "SkyHeightMax", "", &prv2_0.mObj);
    prv2_0.mSkyHeightMin.init(14500.0, "SkyHeightMin", "", &prv2_0.mObj);
    prv2_0.mSkyHeightSinSeedAdd.init(0.0, "SkyHeightSinSeedAdd", "", &prv2_0.mObj);
    prv2_0.mBacklightPowe.init(1.5, "BacklightPowe", "", &prv2_0.mObj);
    prv2_0.mBacklightRange.init(0.65, "BacklightRange", "", &prv2_0.mObj);
    prv2_0.mBacklightParam0.init(0.2, "BacklightParam0", "", &prv2_0.mObj);
    prv2_0.mBacklightParam1.init(0.45, "BacklightParam1", "", &prv2_0.mObj);
    prv2_0.mDarkSideNoiseParam.init(1.0, "DarkSideNoiseParam", "", &prv2_0.mObj);
    prv2_0.mLightSideNoiseParam.init(0.25, "LightSideNoiseParam", "", &prv2_0.mObj);

    auto& prv2_1 = mPrCloudV[2][1];
    prv2_1.mDistotion.init(0.6, "Distotion", "", &prv2_1.mObj);
    prv2_1.mDistotionMax.init(0.6, "DistotionMax", "", &prv2_1.mObj);
    prv2_1.mDistotionMin.init(0.6, "DistotionMin", "", &prv2_1.mObj);
    prv2_1.mDistotionSinSeedAdd.init(0.0, "DistotionSinSeedAdd", "", &prv2_1.mObj);
    prv2_1.mDensity.init(0.65, "Density", "", &prv2_1.mObj);
    prv2_1.mDensityMax.init(0.65, "DensityMax", "", &prv2_1.mObj);
    prv2_1.mDensityMin.init(0.65, "DensityMin", "", &prv2_1.mObj);
    prv2_1.mDensitySinSeedAdd.init(0.0, "DensitySinSeedAdd", "", &prv2_1.mObj);
    prv2_1.mAlphaMul.init(1.0, "AlphaMul", "", &prv2_1.mObj);
    prv2_1.mAlphaMulMax.init(1.0, "AlphaMulMax", "", &prv2_1.mObj);
    prv2_1.mAlphaMulMin.init(1.0, "AlphaMulMin", "", &prv2_1.mObj);
    prv2_1.mAlphaMulSinSeedAdd.init(0.0, "AlphaMulSinSeedAdd", "", &prv2_1.mObj);
    prv2_1.mAlphaThreshold.init(0.8, "AlphaThreshold", "", &prv2_1.mObj);
    prv2_1.mAlphaThresholdMax.init(0.8, "AlphaThresholdMax", "", &prv2_1.mObj);
    prv2_1.mAlphaThresholdMin.init(0.8, "AlphaThresholdMin", "", &prv2_1.mObj);
    prv2_1.mAlphaThresholdSinSeedAdd.init(0.0, "AlphaThresholdSinSeedAdd", "", &prv2_1.mObj);
    prv2_1.mBaseTexScale.init(1.0, "BaseTexScale", "", &prv2_1.mObj);
    prv2_1.mBaseTexScaleMax.init(1.0, "BaseTexScaleMax", "", &prv2_1.mObj);
    prv2_1.mBaseTexScaleMin.init(1.0, "BaseTexScaleMin", "", &prv2_1.mObj);
    prv2_1.mBaseTexScaleSinSeedAdd.init(0.0, "BaseTexScaleSinSeedAdd", "", &prv2_1.mObj);
    prv2_1.mEmbossWidth.init(0.08904, "EmbossWidth", "", &prv2_1.mObj);
    prv2_1.mEmbossDensity.init(0.5, "EmbossDensity", "", &prv2_1.mObj);
    prv2_1.mShadowPower.init(0.75, "ShadowPower", "", &prv2_1.mObj);
    prv2_1.mHighlightPower.init(20.0, "HighlightPower", "", &prv2_1.mObj);
    prv2_1.mHighlightRange.init(1.7, "HighlightRange", "", &prv2_1.mObj);
    prv2_1.mHighlightAmbient.init(0.5, "HighlightAmbient", "", &prv2_1.mObj);
    prv2_1.mSkyHeight.init(10000.0, "SkyHeight", "", &prv2_1.mObj);
    prv2_1.mSkyHeightMax.init(10000.0, "SkyHeightMax", "", &prv2_1.mObj);
    prv2_1.mSkyHeightMin.init(10000.0, "SkyHeightMin", "", &prv2_1.mObj);
    prv2_1.mSkyHeightSinSeedAdd.init(0.0, "SkyHeightSinSeedAdd", "", &prv2_1.mObj);
    prv2_1.mBacklightPowe.init(1.5, "BacklightPowe", "", &prv2_1.mObj);
    prv2_1.mBacklightRange.init(0.65, "BacklightRange", "", &prv2_1.mObj);
    prv2_1.mBacklightParam0.init(0.2, "BacklightParam0", "", &prv2_1.mObj);
    prv2_1.mBacklightParam1.init(0.45, "BacklightParam1", "", &prv2_1.mObj);
    prv2_1.mDarkSideNoiseParam.init(0.5, "DarkSideNoiseParam", "", &prv2_1.mObj);
    prv2_1.mLightSideNoiseParam.init(1.0, "LightSideNoiseParam", "", &prv2_1.mObj);

    mSunSlope.init(1.1, "SunSlope", "", &mSunParamObj);
    mSunMoonDispDist.init(-24000.0, "SunMoonDispDist", "", &mSunParamObj);
    mSunScale.init(2400.0, "SunScale", "", &mSunParamObj);
    mMoonScale.init(2400.0, "MoonScale", "", &mSunParamObj);
    mSunDirYStop.init(-55000.0, "SunDirYStop", "", &mSunParamObj);

    _3f3c = 0.0;
    _3f40 = 0.0;
    _3f14.x = -0.0;
    _3f14.y = -std::sinf(0.82903141);
    _3f14.z = -std::cosf(0.82903141);
    normalize(_3f14);
    _3f44 = 0.0;
    _3f48 = 0.0;
    _3f4c = 0.2;

    const auto a = sead::GlobalRandom::instance()->getF32() * float(2 * sead::numbers::pi);
    const auto b = sead::GlobalRandom::instance()->getF32() * float(2 * sead::numbers::pi);
    const auto c = sead::GlobalRandom::instance()->getF32() * float(2 * sead::numbers::pi);
    const auto d = sead::GlobalRandom::instance()->getF32() * float(2 * sead::numbers::pi);
    const auto e = sead::GlobalRandom::instance()->getF32() * float(2 * sead::numbers::pi);
    const auto f = sead::GlobalRandom::instance()->getF32() * float(2 * sead::numbers::pi);

    for (u32 i = 0; i != 6; ++i) {
        static constexpr int idx0_array[] = {0, 0, 1, 1, 2};
        static constexpr int idx1_array[] = {0, 1, 0, 1, 0};
        int idx0 = i <= 4 ? idx0_array[i] : 2;
        int idx1 = i <= 4 ? idx1_array[i] : 1;
        auto& pr = mPrCloudV[idx0][idx1];
        pr._1e4 = false;
        pr._24c = false;
        pr._2b4 = false;
        pr._31c = false;
        pr._384 = false;
        pr._3ec = false;
        pr._1e0 = a;
        pr._248 = b;
        pr._2b0 = c;
        pr._318 = d;
        pr._380 = e;
        pr._3e8 = f;
    }

    for (int i = 0; i != NumSkyPalettes; ++i) {
        auto& pal0 = mSkyPalette0[i];
        pal0.mPosDensityChgPower.init(0.0, "Sky0PosDensityChgPower", "", &pal0.mObj);
        pal0.mHeight.init(15000.0, "Sky0Height", "", &pal0.mObj);
        pal0.mDistotion.init(0.6, "Sky0Distotion", "", &pal0.mObj);
        pal0.mDensity.init(0.65, "Sky0Density", "", &pal0.mObj);
        pal0.mAlphaMul.init(0.65, "Sky0AlphaMul", "", &pal0.mObj);
        pal0.mAlphaThreshold.init(0.95, "Sky0AlphaThreshold", "", &pal0.mObj);
        pal0.mBaseTexScale.init(1.0, "Sky0BaseTexScale", "", &pal0.mObj);
        pal0.mSkyTexBlendRatio.init(0.0, "Sky0TexBlendRatio", "", &pal0.mObj);

        auto& pal2 = mSkyPalette2[i];
        pal2.mPosDensityChgPower.init(0.0, "Sky2PosDensityChgPower", "", &pal2.mObj);
        pal2.mHeight.init(15000.0, "Sky2Height", "", &pal2.mObj);
        pal2.mDistotion.init(0.6, "Sky2Distotion", "", &pal2.mObj);
        pal2.mDensity.init(0.65, "Sky2Density", "", &pal2.mObj);
        pal2.mAlphaMul.init(0.65, "Sky2AlphaMul", "", &pal2.mObj);
        pal2.mAlphaThreshold.init(0.95, "Sky2AlphaThreshold", "", &pal2.mObj);
        pal2.mBaseTexScale.init(1.0, "Sky2BaseTexScale", "", &pal2.mObj);
        pal2.mSkyTexBlendRatio.init(0.0, "Sky2TexBlendRatio", "", &pal2.mObj);
    }

    for (int i = 0; i != NumCloudPats; ++i) {
        mCloudPat0[i].mHeight.init(10000.0, "0Height", "", &mCloudPat0[i].mObj);
        mCloudPat0[i].mDistotion.init(0.6, "0Distotion", "", &mCloudPat0[i].mObj);
        mCloudPat0[i].mDensity.init(0.55, "0Density", "", &mCloudPat0[i].mObj);
        mCloudPat0[i].mAlphaMul.init(0.9, "0AlphaMul", "", &mCloudPat0[i].mObj);
        mCloudPat0[i].mAlphaThreshold.init(0.95, "0AlphaThreshold", "", &mCloudPat0[i].mObj);
        mCloudPat0[i].mTexBlendRatio.init(0.75, "0TexBlendRatio", "", &mCloudPat0[i].mObj);

        mCloudPat2[i].mHeight.init(5000.0, "0Height", "", &mCloudPat2[i].mObj);
        mCloudPat2[i].mDistotion.init(0.6, "0Distotion", "", &mCloudPat2[i].mObj);
        mCloudPat2[i].mDensity.init(0.5, "0Density", "", &mCloudPat2[i].mObj);
        mCloudPat2[i].mAlphaMul.init(0.9, "0AlphaMul", "", &mCloudPat2[i].mObj);
        mCloudPat2[i].mAlphaThreshold.init(0.925, "0AlphaThreshold", "", &mCloudPat2[i].mObj);
        mCloudPat2[i].mTexBlendRatio.init(0.75, "0TexBlendRatio", "", &mCloudPat2[i].mObj);

        mCloudSpd[i].mCloudPatNoisePow.init(0.4, "CLOUDPAT_noisePow", "", &mCloudSpd[i].mObj);
        mCloudSpd[i].mCloudPatWindPow.init(0.004, "CLOUDPAT_windPow", "", &mCloudSpd[i].mObj);
    }

    reset();
}

SkyMgr::~SkyMgr() = default;

void SkyMgr::init_(sead::Heap* heap) {}

}  // namespace ksys::world
