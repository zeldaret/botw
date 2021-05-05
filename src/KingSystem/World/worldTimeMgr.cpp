#include "KingSystem/World/worldTimeMgr.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/Ecosystem/ecoUtil.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::world {

static_assert(timeToFloat(0, 0) == 0);
static_assert(timeToFloat(5, 15) == 78.75);
static_assert(timeToFloat(12, 0) == 180);
static_assert(timeToFloat(24, 0) == 360);

TimeMgr::TimeMgr() {
    _20 = true;
    _21 = true;
    _22 = 0;
    _24 = false;
    mForceBloodyDay = false;
    _14b = false;
    _cc = {};
    mMoonType = MoonType::Auto;
}

void TimeMgr::init_(sead::Heap* heap) {
    mTime = DefaultTime;
    mTimeForAocFieldSkyEnv = DefaultTime;
    mTimeStep = DefaultTimeStep;
    mTimeUpdateMode = {};
    resetBloodMoonTimer();
    mBloodyEndReserveTimer = 0;
}

void TimeMgr::resetForStageUnload() {
    mNewTime = -1.0;
    mNeedToHandleNewDay = false;
    mWasBloodyDay = false;

    for (auto& entry : _30) {
        entry._0 = {};
        entry._4 = -1;
    }
    _30[9] = {};
    _30[9]._4 = -1;

    gdt::Manager::instance()->setBool(false, mAnimalMasterCtrl.appearance_flag);
    mAnimalMasterCtrl.resetState();
}

void TimeMgr::loadInfo() {
    mTimeStep = DefaultTimeStep;
    mTimeUpdateMode = TimeUpdateMode::Normal;
    mForceBloodyDay = false;
    _14b = false;
    _cc = 0.0;
    mMoonType = MoonType::Auto;

    loadFlags();

    if (mIsPlayedDemo103Flag != gdt::InvalidHandle) {
        gdt::Manager::instance()->getBool(mIsPlayedDemo103Flag, &mPlayedDemo103Or997, true);
        if (!mPlayedDemo103Or997)
            gdt::Manager::instance()->getBool(mDemo997Flag, &mPlayedDemo103Or997, true);
    }

    if (mFindDungeonActivatedFlag != gdt::InvalidHandle)
        gdt::Manager::instance()->getBool(mFindDungeonActivatedFlag, &mFindDungeonActivated, true);

    bool animal_master_appearance = false;
    gdt::Manager::instance()->getBool(mAnimalMasterCtrl.appearance_flag, &animal_master_appearance);
    if (!animal_master_appearance) {
        mAnimalMasterCtrl.resetState();
    }

    mWasBloodyDayAndDayPassed = false;
}

void TimeMgr::loadFlags() {
    mTimeFlag = gdt::Manager::instance()->getF32Handle("WM_Time");
    mNumberOfDaysFlag = gdt::Manager::instance()->getS32Handle("WM_NumberOfDays");
    mTimeDivisionFlag = gdt::Manager::instance()->getS32Handle("WM_TimeDivision");

    gdt::Manager::instance()->getF32(mTimeFlag, &mTime);
    gdt::Manager::instance()->getS32(mNumberOfDaysFlag, &mNumberOfDays);
    gdt::Manager::instance()->getS32(mTimeDivisionFlag, &mTimeDivision);

    mIsDaytimeFlag = gdt::Manager::instance()->getBoolHandle("WM_DaytimeFlag");
    mIsNighttimeFlag = gdt::Manager::instance()->getBoolHandle("WM_NighttimeFlag");
    mIsPlayedDemo103Flag = gdt::Manager::instance()->getBoolHandle("IsPlayed_Demo103_0");
    mDemo997Flag = gdt::Manager::instance()->getBoolHandle("Demo997_0");
    mFindDungeonActivatedFlag = gdt::Manager::instance()->getBoolHandle("FindDungeon_Activated");
    mIsMorningAFlag = gdt::Manager::instance()->getBoolHandle("WM_IsMorningA");
    mIsMorningBFlag = gdt::Manager::instance()->getBoolHandle("WM_IsMorningB");
    mIsNoonAFlag = gdt::Manager::instance()->getBoolHandle("WM_IsNoonA");
    mIsNoonBFlag = gdt::Manager::instance()->getBoolHandle("WM_IsNoonB");
    mIsEveningAFlag = gdt::Manager::instance()->getBoolHandle("WM_IsEveningA");
    mIsEveningBFlag = gdt::Manager::instance()->getBoolHandle("WM_IsEveningB");
    mIsNightAFlag = gdt::Manager::instance()->getBoolHandle("WM_IsNightA");
    mIsNightBFlag = gdt::Manager::instance()->getBoolHandle("WM_IsNightB");
    mWaterRelicRainStopFlag = gdt::Manager::instance()->getBoolHandle("Water_Relic_RainStop");
    mIsGetPlayerStole2Flag = gdt::Manager::instance()->getBoolHandle("IsGet_PlayerStole2");
    mBloodyDayFlag = gdt::Manager::instance()->getBoolHandle("WM_BloodyDay");

    mBloodyMoonTimerFlag = gdt::Manager::instance()->getF32Handle("WM_BloodyMoonTimer");
    gdt::Manager::instance()->getF32(mBloodyMoonTimerFlag, &mBloodMoonTimer);

    mBloodyEndReserveTimerFlag = gdt::Manager::instance()->getS32Handle("WM_bloodyEndReserveTimer");
    if (mBloodyEndReserveTimerFlag != gdt::InvalidHandle)
        gdt::Manager::instance()->getS32(mBloodyEndReserveTimerFlag, &mBloodyEndReserveTimer);

    mAnimalMasterCtrl.appearance_flag =
        gdt::Manager::instance()->getBoolHandle("AnimalMaster_Appearance");
    mAnimalMasterCtrl.existence_flag =
        gdt::Manager::instance()->getBoolHandle("AnimalMaster_Existence");

    mIsInHyruleCastleAreaFlag = gdt::Manager::instance()->getBoolHandle("IsInHyruleCastleArea");
    mLastBossGanonBeastGenerateFlag =
        gdt::Manager::instance()->getBoolHandle("LastBossGanonBeastGenerateFlag");
    mWindRelicBattleStartFlag = gdt::Manager::instance()->getBoolHandle("Wind_Relic_BattleStart");
    mElectricRelicBattleFlag = gdt::Manager::instance()->getBoolHandle("Electric_Relic_Battle");
    mWaterRelicBattleTimeFlag = gdt::Manager::instance()->getBoolHandle("Water_Relic_BattleTime");
    mBloodyMoonProhibitionFlag = gdt::Manager::instance()->getBoolHandle("BloodyMoonProhibition");
}

TimeMgr::~TimeMgr() = default;

bool TimeMgr::isBloodMoonProhibited() const {
    bool prohibited = !Manager::instance()->isMainField();

    if (gdt::Manager::instance()) {
        bool castle = false;
        gdt::Manager::instance()->getBool(mIsInHyruleCastleAreaFlag, &castle);
        if (castle)
            prohibited = true;

        bool last_boss = false;
        gdt::Manager::instance()->getBool(mLastBossGanonBeastGenerateFlag, &last_boss);
        if (last_boss)
            prohibited = true;
    }

    if (isBloodMoonProhibitionFlagSet())
        prohibited = true;

    return prohibited;
}

bool TimeMgr::isBloodMoonProhibitionFlagSet() const {
    bool value = false;
    if (mBloodyMoonProhibitionFlag == gdt::InvalidHandle)
        return false;
    gdt::Manager::instance()->getBool(mBloodyMoonProhibitionFlag, &value);
    return value;
}

bool TimeMgr::isInRelicBattle() const {
    auto* wm = Manager::instance();
    bool in_battle = false;

    if (gdt::Manager::instance()) {
        bool value = false;
        gdt::Manager::instance()->getBool(mWindRelicBattleStartFlag, &value);
        if (value)
            in_battle = true;

        value = false;
        gdt::Manager::instance()->getBool(mElectricRelicBattleFlag, &value);
        if (value)
            in_battle = true;

        value = false;
        gdt::Manager::instance()->getBool(mWaterRelicBattleTimeFlag, &value);
        if (value)
            in_battle = true;
    }

    if (wm->getSkyMgr()->checkConcentrationDarkness())
        in_battle = true;

    return in_battle;
}

void TimeMgr::AnimalMasterController::calc() {
    const auto num_days = Manager::instance()->getTimeMgr()->getNumberOfDays();

    act::ActorConstDataAccess player_accessor;
    act::ActorSystem::instance()->getPlayer(&player_accessor);

    const int day_of_week = num_days % 7;

    switch (state) {
    case 0: {
        if (Manager::instance()->getTimeMgr()->getMoonType() != MoonType::WaxingCrescent)
            break;

        bool exists;
        if (gdt::Manager::instance() == nullptr)
            break;
        if (!gdt::Manager::instance()->getBool(existence_flag, &exists, true, true))
            break;
        if (exists)
            break;

        if (!player_accessor.hasProc())
            break;
        if (eco::currentAreaNumIs64(player_accessor.getPreviousPos()))
            break;

        appearance_hour = sead::GlobalRandom::instance()->getU32(23);
        ++state;
        break;
    }

    case 1: {
        if (!player_accessor.hasProc())
            break;

        if (eco::currentAreaNumIs64(player_accessor.getPreviousPos())) {
            state = 0;
            break;
        }

        int hour = Manager::instance()->getTimeMgr()->getHour();
        if (hour != appearance_hour)
            break;

        hour += 24;
        if (hour >= 24)
            hour -= 24;
        valid_hour = hour;

        gdt::Manager::instance()->setBool(true, appearance_flag);
        if (gdt::Manager::instance())
            gdt::Manager::instance()->onAnimalMasterAppearance();

        ++state;
        break;
    }

    case 2: {
        if (Manager::instance()->getTimeMgr()->getHour() == valid_hour)
            break;

        start_day_of_week = day_of_week;
        ++state;
        break;
    }

    case 3: {
        u8 dow = day_of_week;
        if (dow < start_day_of_week)
            dow += 7;

        const auto should_disappear = [this, dow](u8 day) {
            if (u8(dow - start_day_of_week) >= 2)
                return true;

            return start_day_of_week != day &&
                   Manager::instance()->getTimeMgr()->getHour() >= valid_hour;
        };

        if (!should_disappear(day_of_week))
            break;

        gdt::Manager::instance()->setBool(false, appearance_flag);
        ++state;
        break;
    }

    case 4: {
        if (Manager::instance()->getTimeMgr()->getMoonType() == MoonType::WaxingCrescent)
            break;

        state = 0;
        break;
    }
    }
}

void TimeMgr::calcType1_() {}

void TimeMgr::calcType2_() {}

void TimeMgr::resetBloodMoonTimer() {
    mBloodMoonTimer = 0.0;
}

void TimeMgr::setTimeWithoutDayChecks(float time) {
    if (time >= 0.0)
        mNewTime = time;
}

void TimeMgr::setTime(float time) {
    auto* wm = Manager::instance();
    mNewTime = time;
    mWasBloodyDayAndDayPassed = false;

    if (mTime > mNewTime) {
        mNeedToHandleNewDay = true;

        bool was_bloody_day = false;
        if (gdt::Manager::instance()) {
            if (!gdt::Manager::instance()->getBool(mBloodyDayFlag, &was_bloody_day, false, true))
                return;

            if (was_bloody_day)
                mWasBloodyDayAndDayPassed = true;

            if (mWasBloodyDayAndDayPassed && !wm->isMainField()) {
                mWasBloodyDayAndDayPassed = false;
                mResetGdtOnNextSceneUnloadForBloodMoon = true;
            }
        }
    }
}

bool TimeMgr::isBloodyDay() const {
    bool value = false;
    if (!gdt::Manager::instance())
        return false;
    gdt::Manager::instance()->getBool(mBloodyDayFlag, &value);
    return value;
}

float TimeMgr::getTimeForSkyEnv() const {
    if (Manager::instance()->getStageType() == StageType::OpenWorld &&
        Manager::instance()->getFieldType() == FieldType::AocField &&
        Manager::instance()->getScalingMode() == ScalingMode::Disabled) {
        return mTimeForAocFieldSkyEnv;
    }
    return mTime;
}

void TimeMgr::setAocFieldTimeForSkyEnv(float time) {
    mTimeForAocFieldSkyEnv = time;
}

int TimeMgr::getHour() const {
    auto hour = int(mTime / durationToFloat(1, 0));
    if (hour >= 24)
        hour -= 24;
    return hour;
}

MoonType TimeMgr::getMoonType() const {
    auto type = MoonType(u32(mNumberOfDays + (mTime > timeToFloat(12, 0)) + 1) % 8);

    if (mMoonType != MoonType::Auto)
        type = mMoonType;

    if (!willBloodMoonHappenTonight() && !mWasBloodyDay)
        return type;

    return MoonType::FullMoon;
}

bool TimeMgr::willBloodMoonHappenTonight() const {
    return Manager::instance()->getTimeMgr()->getHour() >= 4 && isBloodyDay();
}

float TimeMgr::getTemperatureMultiplier() const {
    const auto time = Manager::instance()->getTimeMgr()->getTime();

    if (time > 4_h && time < 9_h)
        return (time - 4_h) / (4_h - 9_h) + 1.0f;

    if (time >= 9_h && time < 16_h)
        return 0.0f;

    if (time >= 16_h && time < 21_h)
        return (21_h - time) / (16_h - 21_h) + 1.0f;

    return 1.0f;
}

bool TimeMgr::isTimeFlowingNormally() const {
    return mIsTimeFlowingNormally;
}

}  // namespace ksys::world
