#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadSafeArray.h>
#include <gfx/seadColor.h>
#include <prim/seadStorageFor.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

enum class Climate;

// TODO
class EnvMgr : public Job {
    SEAD_RTTI_OVERRIDE(EnvMgr, Job)
public:
    struct EnvPaletteStatic {
        EnvPaletteStatic();

        agl::utl::Parameter<float> rayleigh_baseHeigh;
        agl::utl::Parameter<float> mie_baseHeight;
        agl::utl::Parameter<float> mie_scatteringCoeff;
        agl::utl::Parameter<float> mie_symmetricalPropert;
        agl::utl::Parameter<float> YFogEnd;
        agl::utl::Parameter<float> SfParam_far;
        agl::utl::Parameter<float> SfParam_density;
        agl::utl::Parameter<u32> BloomComposeColorNoUse_8_8;
        agl::utl::Parameter<u32> BloomLayerColorNoUse_16_16;
        agl::utl::Parameter<u32> BloomLayerColorNoUse_32_32;
        agl::utl::Parameter<u32> BloomLayerColorNoUse_64_64;
        agl::utl::Parameter<sead::Color4f> BloomLayerColor_8_8{{}};
        agl::utl::Parameter<sead::Color4f> BloomLayerColor_16_16{{}};
        agl::utl::Parameter<sead::Color4f> BloomLayerColor_32_32{{}};
        agl::utl::Parameter<sead::Color4f> BloomLayerColor_64_64{{}};
        agl::utl::Parameter<u32> _200;
        agl::utl::Parameter<sead::Color4f> BloomComposeColor{{}};
        agl::utl::ParameterObj obj;
    };

    struct EnvPalette {
        struct Cloud {
            agl::utl::Parameter<sead::Color4f> Cloud0_ColorBase{{}};
            agl::utl::Parameter<float> Cloud0_IntencityBase;
            agl::utl::Parameter<sead::Color4f> Cloud0_ColorHilight{{}};
            agl::utl::Parameter<float> Cloud0_IntencityHilight;
            agl::utl::Parameter<sead::Color4f> Cloud0_ColorShadow{{}};
            agl::utl::Parameter<float> Cloud0_IntencityShadow;
            agl::utl::Parameter<sead::Color4f> Cloud0_ColorBackLight{{}};
            agl::utl::Parameter<sead::Color4f> Cloud1_ColorBase{{}};
            agl::utl::Parameter<float> Cloud1_IntencityBase;
            agl::utl::Parameter<sead::Color4f> Cloud1_ColorHilight{{}};
            agl::utl::Parameter<float> Cloud1_IntencityHilight;
            agl::utl::Parameter<sead::Color4f> Cloud1_ColorShadow{{}};
            agl::utl::Parameter<float> Cloud1_IntencityShadow;
            agl::utl::Parameter<sead::Color4f> Cloud1_ColorBackLight{{}};
            agl::utl::Parameter<sead::Color4f> Cloud2_ColorBase{{}};
            agl::utl::Parameter<float> Cloud2_IntencityBase;
            agl::utl::Parameter<sead::Color4f> Cloud2_ColorHilight{{}};
            agl::utl::Parameter<float> Cloud2_IntencityHilight;
            agl::utl::Parameter<sead::Color4f> Cloud2_ColorShadow{{}};
            agl::utl::Parameter<float> Cloud2_IntencityShadow;
            agl::utl::Parameter<sead::Color4f> Cloud2_ColorBackLight{{}};
        };

        agl::utl::Parameter<sead::Color4f> BgDifColor;
        agl::utl::Parameter<float> BgDifIntencity;
        agl::utl::Parameter<sead::Color4f> FogColor;
        agl::utl::Parameter<float> FogStart;
        agl::utl::Parameter<float> FogEnd;
        agl::utl::Parameter<sead::Color4f> YFogColor;
        agl::utl::Parameter<float> YFogStart;
        agl::utl::Parameter<u32> SkySunColorNoUse;
        agl::utl::Parameter<sead::Color4f> SkySunColor;
        agl::utl::Parameter<float> SkyIsotropicfade;
        agl::utl::Parameter<float> SfParam_near;
        agl::utl::Parameter<float> SfParam_attenuation;
        agl::utl::Parameter<float> SfParam_horizontal;
        agl::utl::Parameter<float> afParam_attenuationForGrd;
        agl::utl::Parameter<float> afParam_attenuationForSky;
        agl::utl::Parameter<float> SkyRParam_rayleigh_amplifier;
        agl::utl::Parameter<float> SkyRParam_mie_symmetricalProperty;
        agl::utl::Parameter<float> SkyRParam_mie_amplifier;
        agl::utl::Parameter<float> AmplifierForEnvMap;
        Cloud cloud;
        agl::utl::Parameter<u32> Cloud2NoUse;
        agl::utl::Parameter<bool> CloudShadowOnOff;
        agl::utl::Parameter<float> BloomOffsetStart;
        agl::utl::Parameter<float> BloomOffsetEnd;
        agl::utl::Parameter<float> BloomOffset;
        agl::utl::Parameter<float> BloomClampedLuminance;
        agl::utl::Parameter<float> BloomThreshhold;
        agl::utl::Parameter<float> BloomIntencity;
        agl::utl::Parameter<u32> VolumeMaskColorNoUse;
        agl::utl::Parameter<sead::Color4f> VolumeMaskColor;
        agl::utl::Parameter<float> VolumeMaskIntencity;
        agl::utl::Parameter<float> AmbientIntencity;
        agl::utl::Parameter<float> Exposure;
        agl::utl::Parameter<float> Cloud0_BacklightPower;
        agl::utl::Parameter<float> Cloud1_BacklightPower;
        agl::utl::Parameter<float> Cloud2_BacklightPower;
        agl::utl::ParameterObj obj;
    };
    KSYS_CHECK_SIZE_NX150(EnvPalette, 0x7b8);

    struct CdanAddFog {
        agl::utl::Parameter<float> DungeonFogFogEnd;
        agl::utl::Parameter<float> DungeonFogVolA;
        agl::utl::ParameterObj obj;
    };
    KSYS_CHECK_SIZE_NX150(CdanAddFog, 0x70);

    struct EnvAttribute {
        agl::utl::Parameter<bool> DifUse;
        agl::utl::Parameter<float> DifXang;
        agl::utl::Parameter<float> DifYang;
        agl::utl::Parameter<int> PaletteSel00;
        agl::utl::Parameter<int> PaletteSel01;
        agl::utl::Parameter<int> PaletteSel02;
        agl::utl::Parameter<int> PaletteSel03;
        agl::utl::Parameter<int> PaletteSel04;
        agl::utl::Parameter<int> PaletteSel05;
        agl::utl::Parameter<int> PaletteSel06;
        agl::utl::Parameter<int> PaletteSel07;
        agl::utl::ParameterObj obj;
    };
    KSYS_CHECK_SIZE_NX150(EnvAttribute, 0x190);

    struct WeatherInfluence {
        agl::utl::Parameter<sead::Color4f> FeatureColor;
        agl::utl::Parameter<sead::Color4f> FeatureFogColor;
        agl::utl::Parameter<float> CalcRayleigh;
        agl::utl::Parameter<float> CalcMieSymmetrical;
        agl::utl::Parameter<float> CalcMie;
        agl::utl::Parameter<float> CalcVolumeMaskIntencity;
        agl::utl::Parameter<float> BloomThreshhold;
        agl::utl::Parameter<float> BloomIntencity;
        agl::utl::Parameter<float> AddMoisture;
        agl::utl::ParameterObj obj;
    };
    KSYS_CHECK_SIZE_NX150(WeatherInfluence, 0x160);

    struct Remains {
        agl::utl::Parameter<sead::Color4f> FeatureColor;
        agl::utl::Parameter<sead::Color4f> FeatureFogColor;
        agl::utl::Parameter<float> AddFog_near;
        agl::utl::Parameter<float> AddFog_far;
        agl::utl::Parameter<float> AddFog_ratio;
        agl::utl::Parameter<float> SfParam_near;
        agl::utl::Parameter<float> SfParam_attenuation;
        agl::utl::Parameter<float> CalcRayleigh;
        agl::utl::Parameter<float> CalcMieSymmetrical;
        agl::utl::Parameter<float> CalcMie;
        agl::utl::Parameter<float> BloomThreshhold;
        agl::utl::Parameter<float> BloomIntencity;
        agl::utl::Parameter<float> CalcVolumeMaskIntencity;
        agl::utl::ParameterObj obj;
    };
    KSYS_CHECK_SIZE_NX150(Remains, 0x1e0);

    struct IndoorPalette {
        agl::utl::Parameter<sead::Color4f> FeatureColor;
        agl::utl::Parameter<float> CalcVolumeMaskIntencity;
        agl::utl::Parameter<float> BloomClampedLuminance;
        agl::utl::Parameter<float> BloomThreshhold;
        agl::utl::Parameter<float> BloomIntencity;
        agl::utl::Parameter<float> IndoorFogRatio;
        agl::utl::Parameter<float> IndoorFogStart;
        agl::utl::Parameter<float> IndoorFogEnd;
        agl::utl::Parameter<float> attenuationForGrd;
        agl::utl::ParameterObj obj;
    };

    EnvMgr();
    ~EnvMgr() override;

    JobType getType() const override { return JobType::Env; }

    void reset();
    void resetForStageUnload();

    bool isBloodMoonNight() const;
    bool isInBloodMoonTimeRange() const;
    float getConcentrationBM() const;
    void activateForcedBloodMoon();
    void setBloodMoonProhibition(bool prohibited);
    bool isLoadingScreenOpened() const;

    bool returnFalse() const;
    bool isInSandstorm() const;
    bool isInYigaClanHideoutArea() const;
    float getConcentrationDarkness() const;
    bool isPaletteSetTransitionDone() const;

    void worldMgrCalc2();
    int getPaletteSet() const;
    bool isWaterRelicRainOn(Climate climate) const;
    void setPaletteSelSpeed(int speed);
    void setPaletteSet(int palette);
    void setCharAmbientScale(sead::Color4f color);
    void setCharMainLightScale(sead::Color4f color);
    void setWarpMistIntensity(float intensity);
    void setFogDirect(bool fog_near_use, bool fog_instant_sw, bool fog_far_use, float fog_ratio,
                      float fog_near, float fog_far);
    float getBloodMoonProgress() const;

    void allowPaletteOverride();

protected:
    void init_(sead::Heap* heap) override;
    void calc_() override;

private:
    friend class Manager;

    static constexpr int NumEnvPalettes = 207;
    static constexpr int NumCdanAddFog = 4;
    static constexpr int NumEnvAttributes = 59;
    static constexpr int NumWeatherInfluences = 4;
    static constexpr int NumRemains = 7;

    void initEnvAttribute(int idx);
    void initEnvPalette(int idx);
    void initWeatherInfluence(int idx);
    void initRemains(int idx);
    void initIndoorPalette();
    void initEnvPaletteStatic();
    void initDungeonFog();

    void updateTimeDivision();
    void updateBloodMoon();
    void updateBloodMoonFlags();
    void updateForcedBloodMoon();

    EnvPaletteStatic mEnvPaletteStatic;
    u32 mPrevSkyEnvTimeDivision = 0;
    u32 mSkyEnvTimeDivision = 0;
    float mEnvTimeTransition = 0.0;
    u32 mBloodMoonEndState = 0;
    u32 mBloodMoonStartState = 0;
    float mBloodMoonProgress = 0.0;
    int mPreviousPaletteSet = 0;
    int mActivePaletteSet = 0;
    float mPaletteSetTransition = 0.0;
    sead::SafeArray<EnvPalette, NumEnvPalettes> mEnvPalettes;
    sead::SafeArray<CdanAddFog, NumCdanAddFog> mCdanAddFog;
    EnvPaletteStatic mEnvPaletteStaticUnused;
    sead::SafeArray<EnvAttribute, NumEnvAttributes> mEnvAttributes;
    sead::SafeArray<WeatherInfluence, NumWeatherInfluences> mWeatherInfluences;
    sead::SafeArray<Remains, NumRemains> mRemains;
    IndoorPalette mIndoorPalette;
    sead::Color4f _6b4e8;
    sead::Color4f _6b4f8;
    sead::Color4f _6b508;
    sead::Color4f _6b518;
    sead::Color4f mCharAmbientScale;
    sead::Color4f mCharMainLightScale;
    float _6b548;
    float _6b54c;
    float _6b550;
    float mEventYfogRatio;
    float _6b558;
    float mEventDiffuseAttenuateDiameter;
    float _6b560;
    float _6b564;
    float _6b568;
    float _6b56c;
    float _6b570;
    float _6b574;
    float _6b578;
    float _6b57c;
    float mWarpMistIntensity;
    float mExposure;
    float mForcedBloodMoonTimer;
    float _6b58c;
    float _6b590;
    float _6b594;
    float _6b598;
    float mConcentrationBM;
    float mBloodMoonTimeRangeProgress;
    float mFogRatio;
    float mFogNear;
    float mFogFar;
    float _6b5b0;
    float _6b5b4;
    int mPaletteSetOverride;
    int mPaletteSetOverrideTimer;
    int mPaletteSetForClimate;
    int mPaletteSetForClimateTimer;
    u32 _6b5c8;
    u32 _6b5cc;
    u32 _6b5d0;
    u32 _6b5d4;
    int mWarpMistTimer;
    u32 _6b5dc;
    u32 _6b5e0;
    u32 _6b5e4;
    u32 _6b5e8;
    int mPaletteSelSpeed;
    int mPaletteSelSpeedTimer;
    int mForcedBloodMoonStatus;
    int mCharAmbientScaleTimer;
    int mCharMainLightScaleTimer;
    int mFogSetDirectTimer;
    u8 mDungeonSizeType;
    bool mForcedBloodMoonRequested;
    bool mForcedBloodMoonReady;
    bool mFogInstantSW;
    bool mFogNearUse;
    bool mFogFagUse;
    bool _6b60a;
    bool _6b60b;
    bool mBloodMoonProhibited;
    bool mDeactivateForcedBloodMoon;
    bool _6b60e;
    bool _6b60f;
    bool _6b610;
    bool mBlockPaletteSetOverride;
    u32 _6b614;
};
KSYS_CHECK_SIZE_NX150(EnvMgr, 0x6b618);

}  // namespace ksys::world
