#pragma once

#include <agl/env/aglEnvObjBuffer.h>
#include <agl/env/aglEnvObjMgr.h>
#include <agl/env/aglEnvObjSetMgr.h>
#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterIO.h>
#include <agl/utl/aglParameterObj.h>
#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace gsys {

class ModelSceneConfigList;

class ModelSceneConfig : public sead::hostio::Node, public agl::utl::IParameterObj {
public:
    static constexpr int NumFeatures = 42;

    struct FeatureDescription {
        const char* description;
        const char* parameter_name;
        bool _10;
        bool _11;
        bool should_create_by_default;
        const char* jp_description;
    };

    enum class Feature {
        LightMap = 0,
        LightProbe = 1,
        SnapShot = 2,
        DepthShadow = 3,
        MaskedLight = 4,
        StaticDepthShadow = 5,
        EnvCubeMap = 6,
        Reflection = 7,
        LocalReflection = 8,
        ZPrePass = 9,
        LightPrePass = 10,
        ShadowPrePass = 11,
        Decal = 12,
        NormalDrawer = 13,
        SSAO = 14,
        SSII = 15,
        SSSSS = 16,
        OcclusionQeuery = 17,
        DeferredShading = 18,
        OpaqueAlphaMask = 19,
        OutlineSilhouette = 20,
        DepthSilhouette = 21,
        XluSeal = 22,
        Cloud = 23,
        VolumeMask = 24,
        XluWater = 25,
        Xlu = 26,
        XluIndirect = 27,
        XluFx = 28,
        ReducedBuffer = 29,
        ShadowMask = 30,
        RadialBlur = 31,
        DOF = 32,
        XluZPrePass = 33,
        Bloom = 34,
        GlareFilter = 35,
        FlareFilter = 36,
        OccludedEffect = 37,
        AutoExposure = 38,
        HDR = 39,
        ColorCorrection = 40,
        FilterAA = 41,
    };

    struct DepthShadowParam {
        agl::utl::Parameter<bool> use_uniform_mtx;
        agl::utl::Parameter<int> cascade_num;
        sead::SafeArray<agl::utl::Parameter<float>, 4> near;
        agl::utl::Parameter<float> far;
        agl::utl::Parameter<float> offset_near;
        agl::utl::Parameter<float> offset_far;
    };

    struct EnvObjSetTemplate : agl::utl::IParameterObj {
        EnvObjSetTemplate();

        agl::utl::Parameter<bool> enable;
        agl::utl::Parameter<int> num;
        agl::utl::Parameter<int> ambient_light_num;
        agl::utl::Parameter<int> directional_light_num;
        agl::utl::Parameter<int> hemisphere_light_num;
        agl::utl::Parameter<int> fog_num;
        agl::utl::Parameter<int> light_map_obj_num;
        agl::utl::Parameter<sead::FixedSafeString<32>> template_name;
    };

    ModelSceneConfig();

    int getStaticDepthShadowDepthFormat() const;
    int getStaticDepthShadowDepthShadowMapFormat() const;

    EnvObjSetTemplate& getEnvObjSetTemplate_(int index) const;

    bool preRead_() override;
    void postRead_() override;
    bool preWrite_() const override;

    static constexpr int cConfig_Max = 32;

private:
    friend class ModelSceneConfigList;

    agl::utl::IParameterObj _c0;
    agl::env::EnvObjMgr::InitArg mEnvObjMgrInitArg;
    agl::env::EnvObjBuffer::AllocateArg mEnvObjBufferAllocateArg;

    sead::SafeArray<agl::utl::Parameter<bool>, NumFeatures> mEnabledFeatures;
    sead::SafeArray<agl::utl::Parameter<bool>, NumFeatures> mShouldCreateFeatures;
    agl::env::EnvObjSetMgr::InitArg mEnvObjSetMgrInitArg;
    const sead::FixedSafeString<32>* mConfigName{};
    ModelSceneConfigList* mpConfigList{};
    bool _1798 = false;
    bool _1799 = false;
    sead::FixedSafeString<64> _17A0;
    int mIndex1 = -1;
    int mIndex2 = -1;
    int mStaticSdwDepthFormat;
    int mStaticSdwShadowMapFormat;
    agl::utl::Parameter<float> mOpaPolygonOffset;
    agl::utl::Parameter<float> mOpaPolygonScale;
    agl::utl::Parameter<float> mXluPolygonOffset;
    agl::utl::Parameter<float> mXluPolygonScale;
    agl::utl::Parameter<float> mRevPolygonOffset;
    agl::utl::Parameter<float> mRevPolygonScale;
    agl::utl::Parameter<bool> mLinearLightingEnable;
    agl::utl::Parameter<bool> mHizExpandEnable;
    agl::utl::Parameter<bool> mNldEnable;
    agl::utl::Parameter<bool> mNld32Bit;
    agl::utl::Parameter<bool> mNldHalf32Bit;
    agl::utl::Parameter<bool> mDepthReduce;
    agl::utl::Parameter<bool> mZPrePassSelectable;
    agl::utl::Parameter<bool> mDepthClear;
    agl::utl::Parameter<bool> mGBufferAlbedoSrgb;
    agl::utl::Parameter<bool> mIndirectBufferLDR;
    agl::utl::Parameter<bool> mReducedBuffer16Bit;
    agl::utl::Parameter<bool> mReducedBufferEdgeAdjustBake;
#ifdef UKING_NX_V150
    agl::utl::Parameter<bool> mReducedBufferBlurAdjustBake;
#endif
    agl::utl::Parameter<bool> mReducedBufferEdgeAdjust;
    agl::utl::Parameter<float> mReducedBufferEdgeAdjustCoeff;
    agl::utl::Parameter<bool> mGBufferAlbedoReduceNearest;
    agl::utl::Parameter<bool> mGBufferNormal8Bit;
    agl::utl::Parameter<bool> mGBufferNormalDisableReduce;
    agl::utl::Parameter<bool> mGBufferNormalReduceNearest;
    agl::utl::Parameter<bool> mGBufferNormalZSignW;
    agl::utl::Parameter<bool> mGBufferDepth;
    agl::utl::Parameter<int> mGBufferMaterialIdFormat;
    agl::utl::Parameter<int> mBaseResoWidth;
    agl::utl::Parameter<int> mBaseResoHeight;
    agl::utl::Parameter<bool> mGpuStressAnalyzerEnable;
    agl::utl::Parameter<bool> mEnableDrcFilterAa;
    agl::utl::Parameter<bool> mInitFilterAaSmaaResTextures;
    agl::utl::Parameter<bool> mGpuStressAnalyzerReduceBufferenable;
    sead::SafeArray<agl::utl::Parameter<int>, 3> mLmMax;
    agl::utl::Parameter<int> mLightMapSizeSphere;
    agl::utl::Parameter<int> mLightMapCube;
    agl::utl::Parameter<int> mLightMapAmbientLight;
    agl::utl::Parameter<int> mLightMapHemiSphereLight;
    agl::utl::Parameter<int> mLightMapDirectionalLight;
    sead::SafeArray<agl::utl::Parameter<int>, 2> mCubeMapMaxTex;
    agl::utl::Parameter<bool> mLightPrepassTextureHalf;
    agl::utl::Parameter<bool> mUseDecalAo;
    agl::utl::Parameter<int> mDecalAoObjectMax;
    agl::utl::Parameter<int> mDecalAoTextureMax;
    agl::utl::Parameter<int> mDecalAoTextureWidth;
    agl::utl::Parameter<int> mDecalAoTextureHeight;
    agl::utl::Parameter<int> mDecalAoTextureCannelNum;
    agl::utl::Parameter<bool> mUseDecalBuffer;
    agl::utl::Parameter<bool> mUseDecalTrail;
    agl::utl::Parameter<int> mStaticSdwWidth;
    mutable agl::utl::Parameter<sead::FixedSafeString<32>> mStaticSdwDepthFormatName;
    mutable agl::utl::Parameter<sead::FixedSafeString<32>> mStaticSdwShadowMapFormatName;
    agl::utl::Parameter<bool> mMaskedLightShadowOnly;
    agl::utl::Parameter<int> mDepthShadowClipPlaneEnable;
    agl::utl::Parameter<int> mDepthShadowExClipPlaneNum;
    sead::SafeArray<agl::utl::Parameter<sead::Vector4f>, 4> mDepthShadowClipPlanes;
    agl::utl::Parameter<float> mDepthShadowPcfOffset;
    agl::utl::Parameter<int> mDepthShadowTexWidth;
    agl::utl::Parameter<int> mDepthShadowTexHeight;
    agl::utl::Parameter<bool> mDepthShadowEnableBbClip;
    agl::utl::Parameter<bool> mDepthShadowCheckOnly;
    agl::utl::Parameter<bool> mDepthShadowMatrixViewCoordinate;
    agl::utl::Parameter<bool> mDepthShadowEnableHiZ;
    agl::utl::Parameter<bool> mDepthShadowForceArray;
    agl::utl::Parameter<bool> mBloomCorrectDepth;
    agl::utl::Parameter<float> mDepthShadowNearFarMargin;
    agl::utl::Parameter<float> mDepthShadowPolygonOffset;
    agl::utl::Parameter<float> mDepthShadowPolygonScale;
    sead::SafeArray<agl::utl::Parameter<float>, 4> mDepthShadowRefValueThresholds;
    agl::utl::Parameter<bool> mDepthShadowReleaseGbuffer;
    sead::SafeArray<DepthShadowParam, 2> mDepthShadowParams;
    agl::utl::Parameter<int> mProjectionShadowNum;
    agl::utl::Parameter<bool> mProjShadowMatrixViewCoordinate;
    agl::utl::Parameter<float> mSsaoWidthScale;
    agl::utl::Parameter<bool> mSsaoIsDepthFull;
    agl::utl::Parameter<int> mModelSceneEnvDataSetNum;
    agl::utl::Parameter<bool> mCubemapArray;
    agl::utl::Parameter<float> mCubemapDynamicRange;
    agl::utl::Parameter<float> mCubemapHdrComposePower;
    agl::utl::Parameter<u32> mCubemapMaxModelUnitNum;
    agl::utl::Parameter<u32> mCubemapMaxShapeNum;
    agl::utl::Parameter<bool> mCubemapDisableEncode;
    agl::utl::Parameter<int> mModelNum;
    agl::utl::Parameter<int> mModelUnitNum;
    agl::utl::Parameter<int> mShapeNum;
    agl::utl::Parameter<int> mOcclusionQueryNum;
    agl::utl::Parameter<int> mEnvObjPointLightNum;
    agl::utl::Parameter<int> mEnvObjPointLightRigNum;
    agl::utl::Parameter<int> mEnvObjSpotLightNum;
    agl::utl::Parameter<int> mEnvObjSpotLightRigNum;
    agl::utl::Parameter<int> mEnvObjMaskedSpotLightNum;
    agl::utl::Parameter<int> mEnvObjMaskedSpotLightRigNum;
    agl::utl::Parameter<int> mEnvObjMaskedProjLightNum;
    agl::utl::Parameter<int> mOfxNumLensFlare;
    agl::utl::Parameter<int> mOfxNumLensFlarePreset;
    agl::utl::Parameter<int> mOfxNumLensFlareDynamic;
    agl::utl::Parameter<int> mOfxNumLensFlareDynamicPreset;
    agl::utl::Parameter<int> mOfxNumLensFlareRig;
    agl::utl::Parameter<int> mOfxNumLensFlareRigObj;
    agl::utl::Parameter<int> mOfxNumLensFlareRigPreset;
    agl::utl::Parameter<int> mOfxNumLargeLensFlareRig;
    agl::utl::Parameter<int> mOfxNumLargeLensFlareRigObj;
    agl::utl::Parameter<int> mOfxNumLargeLensFlareRigPreset;
    sead::SafeArray<agl::utl::Parameter<sead::FixedSafeString<64>>, 8> mDeferredShadingModels;
    agl::utl::Parameter<sead::FixedSafeString<64>> mSceneMaterialModel;
    sead::SafeArray<agl::utl::Parameter<sead::FixedSafeString<32>>, 8> mUserVisualizeClrNames;
    sead::SafeArray<agl::utl::Parameter<sead::FixedSafeString<32>>, 8> mUserVisualizeTexNames;
};

class ModelSceneConfigList : public sead::hostio::Node, public agl::utl::IParameterIO {
public:
    struct EnvObjSetTemplateList : agl::utl::IParameterList {
        EnvObjSetTemplateList();
        bool preRead_() override;

        bool unk = false;
    };

    ModelSceneConfigList();

    // sic
    void applyResouce(const void* resource);

    const ModelSceneConfig& setup(const sead::SafeString& config_name);
    void reload(const sead::SafeString& config_name);

    void copyPassConfig(const sead::SafeString& config_name_1,
                        const sead::SafeString& config_name_2);

    void copyPassConfig(int config_idx_1, int config_idx_2);

protected:
    bool preRead_() override;
    void postRead_() override;
    bool preWrite_() const override;

private:
    friend class ModelSceneConfig;

    ModelSceneConfig& addNewConfig_(const sead::SafeString& config_name);
    void deleteConfig_(ModelSceneConfig* config);

    agl::utl::IParameterObj mNameArrayObj;
    EnvObjSetTemplateList mEnvObjSetTemplateList;
    sead::SafeArray<ModelSceneConfig, ModelSceneConfig::cConfig_Max> mConfigs;
    sead::SafeArray<agl::utl::Parameter<sead::FixedSafeString<32>>, ModelSceneConfig::cConfig_Max>
        mConfigNames;
    sead::SafeArray<ModelSceneConfig::EnvObjSetTemplate, 8> mEnvObjSetTemplates;
    int mCurrentConfigIndex = -1;
    bool _821e4 = true;
    const void* mResource = nullptr;
};

}  // namespace gsys
