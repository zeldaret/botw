#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::world {

EnvMgr::EnvMgr() {
    mForcedBloodMoonRequested = false;
    mDeactivateForcedBloodMoon = false;
    mForcedBloodMoonReady = false;
    mBloodMoonProhibited = false;
    mForcedBloodMoonStatus = {};
    mForcedBloodMoonTimer = {};

    reset();

    for (int i = 0; i < mEnvAttributes.size(); ++i)
        initEnvAttribute(i);
    for (int i = 0; i < mEnvPalettes.size(); ++i)
        initEnvPalette(i);
    for (int i = 0; i < mWeatherInfluences.size(); ++i)
        initWeatherInfluence(i);
    for (int i = 0; i < mRemains.size(); ++i)
        initRemains(i);
    initIndoorPalette();
    initEnvPaletteStatic();
    initDungeonFog();
    mDungeonSizeType = DungeonSize::M;
    _6b5b0 = 1.0;
}

EnvMgr::EnvPaletteStatic::EnvPaletteStatic() = default;

void EnvMgr::initEnvAttribute(int idx) {
    auto& attr = mEnvAttributes[idx];

    if (Manager::instance()->worldInfoLoaded())
        return;

    auto* obj = &attr.obj;
    attr.DifUse.init(false, "DifUse", "", obj);
    attr.DifXang.init(0.0, "DifXang", "", obj);
    attr.DifYang.init(0.0, "DifYang", "", obj);
    attr.PaletteSel00.init(8 * idx, "PaletteSel00", "", obj);
    attr.PaletteSel01.init(8 * idx + 1, "PaletteSel01", "", obj);
    attr.PaletteSel02.init(8 * idx + 2, "PaletteSel02", "", obj);
    attr.PaletteSel03.init(8 * idx + 3, "PaletteSel03", "", obj);
    attr.PaletteSel04.init(8 * idx + 4, "PaletteSel04", "", obj);
    attr.PaletteSel05.init(8 * idx + 5, "PaletteSel05", "", obj);
    attr.PaletteSel06.init(8 * idx + 6, "PaletteSel06", "", obj);
    attr.PaletteSel07.init(8 * idx + 7, "PaletteSel07", "", obj);
}

void EnvMgr::initEnvPalette(int idx) {
    auto& pal = mEnvPalettes[idx];

    if (Manager::instance()->worldInfoLoaded())
        return;

    auto* obj = &pal.obj;
    pal.BgDifColor.init({1.0, 0.894, 0.68, 0.0}, "BgDifColor", "", obj);
    pal.BgDifIntencity.init(8.0, "BgDifIntencity", "", obj);
    pal.FogColor.init({0.535, 0.763, 0.568, 0.4}, "FogColor", "", obj);
    pal.FogStart.init(0.0, "FogStart", "", obj);
    pal.FogEnd.init(600.0, "FogEnd", "", obj);
    pal.YFogColor.init({1.288, 0.992, 0.178, 0.8}, "YFogColor", "", obj);
    pal.YFogStart.init(0.0, "YFogStart", "", obj);
    pal.SkySunColorNoUse.init(1, "SkySunColorNoUse", "", obj);
    pal.SkySunColor.init({1.0, 0.894, 0.68, 10.0}, "SkySunColor", "", obj);
    pal.SkyIsotropicfade.init(0.0, "SkyIsotropicfade", "", obj);
    pal.SfParam_near.init(0.0, "SfParam_near", "", obj);
    pal.SfParam_attenuation.init(15.0, "SfParam_attenuation", "", obj);
    pal.SfParam_horizontal.init(2.4, "SfParam_horizontal", "", obj);
    pal.afParam_attenuationForGrd.init(2.5, "afParam_attenuationForGrd", "", obj);
    pal.afParam_attenuationForSky.init(0.25, "afParam_attenuationForSky", "", obj);
    pal.SkyRParam_rayleigh_amplifier.init(1.0, "SkyRParam_rayleigh_amplifier", "", obj);
    pal.SkyRParam_mie_symmetricalProperty.init(0.8, "SkyRParam_mie_symmetricalProperty", "", obj);
    pal.SkyRParam_mie_amplifier.init(2.0, "SkyRParam_mie_amplifier", "", obj);
    pal.AmplifierForEnvMap.init(5.0, "AmplifierForEnvMap", "", obj);
    pal.cloud.Cloud0_ColorBase.init({0.956, 0.643137, 0.0, 0.835}, "Cloud0_ColorBase", "", obj);
    pal.cloud.Cloud0_IntencityBase.init(0.376, "Cloud0_IntencityBase", "", obj);
    pal.cloud.Cloud0_ColorHilight.init({0.8, 0.92, 0.557, 1.0}, "Cloud0_ColorHilight", "", obj);
    pal.cloud.Cloud0_IntencityHilight.init(11.76, "Cloud0_IntencityHilight", "", obj);
    pal.cloud.Cloud0_ColorShadow.init({0.44, 0.577, 0.61, 1.0}, "Cloud0_ColorShadow", "", obj);
    pal.cloud.Cloud0_IntencityShadow.init(1.0, "Cloud0_IntencityShadow", "", obj);
    pal.cloud.Cloud0_ColorBackLight.init({1.0, 0.95, 0.645, 1.0}, "Cloud0_ColorBackLight", "", obj);
    const u32 i = idx - 8;
    if (i < 8)
        pal.Cloud0_BacklightPower.init(1.2, "Cloud0_BacklightPower", "", obj);
    else
        pal.Cloud0_BacklightPower.init(1.6, "Cloud0_BacklightPower", "", obj);
    pal.cloud.Cloud1_ColorBase.init({1.0, 1.0, 1.0, 1.0}, "Cloud1_ColorBase", "", obj);
    pal.cloud.Cloud1_IntencityBase.init(0.0, "Cloud1_IntencityBase", "", obj);
    pal.cloud.Cloud1_ColorHilight.init({1.0, 1.0, 1.0, 1.0}, "Cloud1_ColorHilight", "", obj);
    pal.cloud.Cloud1_IntencityHilight.init(0.0, "Cloud1_IntencityHilight", "", obj);
    pal.cloud.Cloud1_ColorShadow.init({1.0, 1.0, 1.0, 1.0}, "Cloud1_ColorShadow", "", obj);
    pal.cloud.Cloud1_IntencityShadow.init(0.0, "Cloud1_IntencityShadow", "", obj);
    pal.cloud.Cloud1_ColorBackLight.init({1.0, 1.0, 1.0, 1.0}, "Cloud1_ColorBackLight", "", obj);
    if (i < 8)
        pal.Cloud1_BacklightPower.init(1.2, "Cloud1_BacklightPower", "", obj);
    else
        pal.Cloud1_BacklightPower.init(1.6, "Cloud1_BacklightPower", "", obj);
    pal.cloud.Cloud2_ColorBase.init({1.0, 0.91, 0.72, 1.0}, "Cloud2_ColorBase", "", obj);
    pal.cloud.Cloud2_IntencityBase.init(1.0, "Cloud2_IntencityBase", "", obj);
    pal.cloud.Cloud2_ColorHilight.init({1.0, 0.91, 0.72, 1.0}, "Cloud2_ColorHilight", "", obj);
    pal.cloud.Cloud2_IntencityHilight.init(48.0, "Cloud2_IntencityHilight", "", obj);
    pal.cloud.Cloud2_ColorShadow.init({0.0, 0.541, 0.437, 0.994}, "Cloud2_ColorShadow", "", obj);
    pal.cloud.Cloud2_IntencityShadow.init(2.0, "Cloud2_IntencityShadow", "", obj);
    pal.cloud.Cloud2_ColorBackLight.init({0.0, 0.0, 0.0, 0.0}, "Cloud2_ColorBackLight", "", obj);
    if (i < 8)
        pal.Cloud2_BacklightPower.init(1.2, "Cloud2_BacklightPower", "", obj);
    else
        pal.Cloud2_BacklightPower.init(1.6, "Cloud2_BacklightPower", "", obj);
    pal.Cloud2NoUse.init(1, "Cloud2NoUse", "", obj);
    pal.CloudShadowOnOff.init(true, "CloudShadowOnOff", "", obj);
    pal.BloomOffsetStart.init(19999.0, "BloomOffsetStart", "", obj);
    pal.BloomOffsetEnd.init(20000.0, "BloomOffsetEnd", "", obj);
    pal.BloomOffset.init(2.0, "BloomOffset", "", obj);
    pal.BloomClampedLuminance.init(64.0, "BloomClampedLuminance", "", obj);
    pal.BloomThreshhold.init(2.0, "BloomThreshhold", "", obj);
    pal.BloomIntencity.init(0.1, "BloomIntencity", "", obj);
    pal.VolumeMaskColorNoUse.init(1, "VolumeMaskColorNoUse", "", obj);
    pal.VolumeMaskColor.init({1.0, 1.0, 1.0, 1.0}, "VolumeMaskColor", "", obj);
    pal.VolumeMaskIntencity.init(1.0, "VolumeMaskIntencity", "", obj);
    pal.AmbientIntencity.init(1.0, "AmbientIntencity", "", obj);
    pal.Exposure.init(0.0, "Exposure", "", obj);
}

void EnvMgr::initWeatherInfluence(int idx) {
    auto& entry = mWeatherInfluences[idx];

    if (Manager::instance()->worldInfoLoaded())
        return;

    auto* obj = &entry.obj;
    entry.FeatureColor.init({1.0, 1.0, 1.0, 1.0}, "FeatureColor", "", obj);
    entry.FeatureFogColor.init({1.0, 1.0, 1.0, 1.0}, "FeatureFogColor", "", obj);
    entry.CalcRayleigh.init(1.0, "CalcRayleigh", "", "Min=0.0f, Max=2.0f", obj);
    entry.CalcMieSymmetrical.init(1.0, "CalcMieSymmetrical", "", "Min=0.0f, Max=10.0f", obj);
    entry.CalcMie.init(1.0, "CalcMie", "", "Min=0.0f, Max=100.0f", obj);
    entry.CalcVolumeMaskIntencity.init(1.0, "CalcVolumeMaskIntencity", "", "Min=0.0f, Max=20.0f",
                                       obj);
    entry.BloomThreshhold.init(1.0, "BloomThreshhold", "", "Min=0.0f, Max=2.0f", obj);
    entry.BloomIntencity.init(1.0, "BloomIntencity", "", "Min=0.0f, Max=2.0f", obj);
    entry.AddMoisture.init(0.0, "AddMoisture", "", "Min=0.0f, Max=100.0f", obj);
}

void EnvMgr::initRemains(int idx) {
    auto& entry = mRemains[idx];

    if (Manager::instance()->worldInfoLoaded())
        return;

    auto* obj = &entry.obj;
    entry.FeatureColor.init({1.0, 1.0, 1.0, 1.0}, "FeatureColor", "", obj);
    entry.FeatureFogColor.init({1.0, 1.0, 1.0, 1.0}, "FeatureFogColor", "", obj);
    entry.AddFog_near.init(0.0, "AddFog_near", "", obj);
    entry.AddFog_far.init(300.0, "AddFog_far", "", obj);
    entry.AddFog_ratio.init(0.0, "AddFog_ratio", "", obj);
    entry.SfParam_near.init(0.0, "SfParam_near", "", obj);
    entry.SfParam_attenuation.init(0.0, "SfParam_attenuation", "", obj);
    entry.CalcRayleigh.init(1.0, "CalcRayleigh", "", obj);
    entry.CalcMieSymmetrical.init(1.0, "CalcMieSymmetrical", "", obj);
    entry.CalcMie.init(1.0, "CalcMie", "", obj);
    entry.BloomThreshhold.init(1.0, "BloomThreshhold", "", obj);
    entry.BloomIntencity.init(1.0, "BloomIntencity", "", obj);
    entry.CalcVolumeMaskIntencity.init(1.0, "CalcVolumeMaskIntencity", "", obj);
}

void EnvMgr::initIndoorPalette() {
    if (Manager::instance()->worldInfoLoaded())
        return;

    auto* obj = &mIndoorPalette.obj;
    mIndoorPalette.FeatureColor.init({0.5, 0.342, 0.274, 0.175}, "FeatureColor", "", obj);
    mIndoorPalette.CalcVolumeMaskIntencity.init(2.0, "CalcVolumeMaskIntencity", "", obj);
    mIndoorPalette.BloomClampedLuminance.init(64.0, "BloomClampedLuminance", "", obj);
    mIndoorPalette.BloomThreshhold.init(2.0, "BloomThreshhold", "", obj);
    mIndoorPalette.BloomIntencity.init(3.0, "BloomIntencity", "", obj);
    mIndoorPalette.IndoorFogRatio.init(0.175, "IndoorFogRatio", "", obj);
    mIndoorPalette.IndoorFogStart.init(5.0, "IndoorFogStart", "", obj);
    mIndoorPalette.IndoorFogEnd.init(15.0, "IndoorFogEnd", "", obj);
    mIndoorPalette.attenuationForGrd.init(0.75, "attenuationForGrd", "", obj);
}

void EnvMgr::initEnvPaletteStatic() {
    if (Manager::instance()->worldInfoLoaded())
        return;

    auto* obj = &mEnvPaletteStatic.obj;
    mEnvPaletteStatic.rayleigh_baseHeigh.init(20.0, "rayleigh_baseHeigh", "", obj);
    mEnvPaletteStatic.mie_baseHeight.init(2.0, "mie_baseHeight", "", obj);
    mEnvPaletteStatic.mie_scatteringCoeff.init(0.0018, "mie_scatteringCoeff", "", obj);
    mEnvPaletteStatic.mie_symmetricalPropert.init(0.8, "mie_symmetricalPropert", "", obj);
    mEnvPaletteStatic.YFogEnd.init(160.0, "YFogEnd", "", obj);
    mEnvPaletteStatic.SfParam_far.init(24000.0, "SfParam_far", "", obj);
    mEnvPaletteStatic.SfParam_density.init(0.85, "SfParam_density", "", obj);
    mEnvPaletteStatic.BloomComposeColorNoUse_8_8.init(0, "BloomComposeColorNoUse_8_8", "", obj);
    mEnvPaletteStatic.BloomLayerColor_8_8.init({1.0, 1.0, 1.0, 0.5}, "BloomLayerColor_8_8", "",
                                               obj);
    mEnvPaletteStatic.BloomLayerColorNoUse_16_16.init(0, "BloomLayerColorNoUse_16_16", "", obj);
    mEnvPaletteStatic.BloomLayerColor_16_16.init({1.0, 1.0, 1.0, 1.0}, "BloomLayerColor_16_16", "",
                                                 obj);
    mEnvPaletteStatic.BloomLayerColorNoUse_32_32.init(1, "BloomLayerColorNoUse_32_32", "", obj);
    mEnvPaletteStatic.BloomLayerColor_32_32.init({1.0, 1.0, 1.0, 1.0}, "BloomLayerColor_32_32", "",
                                                 obj);
    mEnvPaletteStatic.BloomLayerColorNoUse_64_64.init(1, "BloomLayerColorNoUse_64_64", "", obj);
    mEnvPaletteStatic.BloomLayerColor_64_64.init({1.0, 1.0, 1.0, 0.0}, "BloomLayerColor_64_64", "",
                                                 obj);
    mEnvPaletteStatic.BloomComposeColor.init({1.0, 1.0, 1.0, 1.0}, "BloomComposeColor", "", obj);
}

KSYS_ALWAYS_INLINE void EnvMgr::initDungeonFog() {
    if (Manager::instance()->worldInfoLoaded())
        return;

    for (int i = 0; i < mCdanAddFog.size(); ++i) {
        auto& entry = mCdanAddFog[i];
        auto* obj = &entry.obj;
        entry.DungeonFogFogEnd.init(300.0, "DungeonFogFogEnd", "", obj);
        entry.DungeonFogVolA.init(10.0, "DungeonFogVolA", "", obj);
    }
}

EnvMgr::~EnvMgr() = default;

void EnvMgr::init_(sead::Heap* heap) {
    mBloodMoonEndState = {};
    mBloodMoonStartState = {};
    mBloodMoonProgress = 1.0;
}

void EnvMgr::calc_() {}

void EnvMgr::updateTimeDivision() {
    auto* wm = Manager::instance();
    const auto time = wm->getTimeMgr()->getTimeForSkyEnv();

    float transition = 1.0;
    u32 division = 0;

    if (wm->getStageType() == StageType::Indoor) {
        division = 0;

    } else if (time >= 3_h && time < 4_h) {
        division = 0;
        if (time < timeToFloat(3, 40))
            transition = (time - 3_h) / timeToFloat(0, 40);

    } else if (time >= 4_h && time < 6_h) {
        division = 1;
        if (time < 5_h)
            transition = (time - 4_h) / 1_h;

    } else if (time >= 6_h && time < 9_h) {
        division = 2;
        if (time < 7_h)
            transition = (time - 6_h) / 1_h;

    } else if (time >= 9_h && time < 16_h) {
        division = 3;
        if (time < 10_h)
            transition = (time - 9_h) / 1_h;

    } else if (time >= 16_h && time < 18_h) {
        division = 4;
        if (time < 17_h)
            transition = (time - 16_h) / 1_h;

    } else if (time >= 18_h && time < 20_h) {
        division = 5;
        if (time < 19_h)
            transition = (time - 18_h) / 1_h;

    } else if (time >= 20_h && time < 21_h) {
        division = 6;
        if (time < timeToFloat(20, 40))
            transition = (time - 20_h) / timeToFloat(0, 40);

    } else if (time >= 21_h && time < 22_h) {
        division = 7;
        transition = (time - 21_h) / 1_h;

    } else {
        division = 7;
    }

    if (mSkyEnvTimeDivision != division) {
        mPrevSkyEnvTimeDivision = division == 0 ? 7 : division - 1;
        mSkyEnvTimeDivision = division;
    }
    mEnvTimeTransition = transition;
}

bool EnvMgr::isBloodMoonNight() const {
    auto* wm = Manager::instance();
    const auto time = wm->getTimeMgr()->getTimeForSkyEnv();

    bool bm = false;
    bm |= wm->getTimeMgr()->isBloodyDay();
    bm |= wm->getTimeMgr()->wasBloodyDay() && time < 1_h;
    bm |= wm->getTimeMgr()->getBloodMoonForceMode() != TimeMgr::BloodMoonForceMode::Disabled;
    return bm;
}

bool EnvMgr::isInBloodMoonTimeRange() const {
    return mBloodMoonTimeRangeProgress > 0.001f;
}

float EnvMgr::getConcentrationBM() const {
    return mConcentrationBM;
}

void EnvMgr::activateForcedBloodMoon() {
    if (Manager::instance()->isMainField())
        mForcedBloodMoonRequested = true;
    mBloodMoonProhibited = false;
}

void EnvMgr::setBloodMoonProhibition(bool prohibited) {
    if (!mDeactivateForcedBloodMoon)
        mBloodMoonProhibited = prohibited;
}

bool EnvMgr::isWaterRelicRainOn(Climate climate) const {
    if (climate != Climate::ZoraTemperateClimate)
        return false;

    bool on = false;
    const auto flag = Manager::instance()->getTimeMgr()->getWaterRelicRainStopFlag();
    if (flag == gdt::InvalidHandle)
        return false;
    gdt::Manager::instance()->getBool(flag, &on, true);
    return !on;
}

}  // namespace ksys::world
