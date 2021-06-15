#include "KingSystem/World/worldTimeMgr.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/Ecosystem/ecoUtil.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/System/VFR.h"
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
    mBloodMoonForceMode = {};
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

void TimeMgr::reset() {
    mTimeStep = DefaultTimeStep;
    mTimeUpdateMode = TimeUpdateMode::Normal;
    mBloodMoonForceMode = {};
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

void TimeMgr::callBloodMoonDemo() {
    auto* evt_mgr = evt::Manager::instance();
    if (!evt_mgr)
        return;

    evt_mgr->callEvent(evt::Metadata("Demo011_0"));
}

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

    if (wm->getEnvMgr()->isInYigaClanHideoutArea())
        in_battle = true;

    return in_battle;
}

static bool playerHasLeftPlateau() {
    bool left_plateau = false;
    gdt::Manager::instance()->getParamBypassPerm().get().getBool(&left_plateau, "FirstTouchdown");
    return left_plateau;
}

void TimeMgr::handleNewDay(HandleNewDayMode mode) {
    auto* wm = Manager::instance();
    auto* gdm = gdt::Manager::instance();

    ++mNumberOfDays;

    if (mode == HandleNewDayMode::Normal && wm->getEnvMgr()->isBloodMoonNight()) {
        if (isBloodMoonProhibited() || isInRelicBattle()) {
            mBloodMoonTimer = 8_days;
        } else {
            callBloodMoonDemo();
            mBloodMoonTimer = 0.0;
            if (PlayReportMgr::instance())
                PlayReportMgr::instance()->reportDebug("BloodyMoon", "Schedule");
        }
        mBloodMoonForceMode = {};
    }

    if (gdm) {
        gdt::Manager::instance()->getBool(mBloodyDayFlag, &mWasBloodyDay);

        if (playerHasLeftPlateau() && mBloodMoonTimer > 7_days) {
            mBloodMoonTimer = 0.0;
            gdm->setBool(true, mBloodyDayFlag);
        } else {
            mBloodyEndReserveTimer = 150;
        }
    }

    NewDayEvent event;
    if (mNewDaySignal.getNumSlots() > 0)
        mNewDaySignal.emit(event);
}

void TimeMgr::calc_() {
    bool is_daytime_flag_set = true;

    auto* gdm = gdt::Manager::instance();
    if (!gdm)
        return;

    mIsTimeFlowingNormally = false;
    float& time = mTime;
    gdm->getF32(mTimeFlag, &time);
    gdm->getS32(mNumberOfDaysFlag, &mNumberOfDays);
    gdm->getS32(mTimeDivisionFlag, &mTimeDivision);
    gdm->getBool(mIsDaytimeFlag, &is_daytime_flag_set);
    gdm->getF32(mBloodyMoonTimerFlag, &mBloodMoonTimer);
    if (mBloodyEndReserveTimerFlag != gdt::InvalidHandle)
        gdm->getS32(mBloodyEndReserveTimerFlag, &mBloodyEndReserveTimer);

    if (!mPlayedDemo103Or997) {
        mTime = DefaultTime;
        gdm->getBool(mIsPlayedDemo103Flag, &mPlayedDemo103Or997, true);
        if (!mPlayedDemo103Or997)
            gdm->getBool(mDemo997Flag, &mPlayedDemo103Or997, true);
    }

    if (!mFindDungeonActivated) {
        gdm->getBool(mFindDungeonActivatedFlag, &mFindDungeonActivated, true);
    }

    auto* wm = Manager::instance();
    if (!wm->worldInfoLoaded())
        return;

    if (mNewTime >= 0.0 &&
        (mTimeUpdateMode == TimeUpdateMode::Forced || mTimeUpdateMode == TimeUpdateMode::Normal)) {
        mTime = mNewTime;
        mNewTime = -1.0;
        wm->getSkyMgr()->onTimeUpdate();
    }

    if (mNeedToHandleNewDay) {
        handleNewDay(HandleNewDayMode::Forced);
        mNeedToHandleNewDay = false;
    }

    switch (mBloodMoonForceMode) {
    case BloodMoonForceMode::Disabled:
        break;
    case BloodMoonForceMode::Force23h:
        mBloodMoonForceMode = {};
        mTime = timeToFloat(23, 29) + 0.1;
        mBloodMoonTimer = 0.0;
        gdm->setBool(true, mBloodyDayFlag);
        break;
    case BloodMoonForceMode::Force21h:
        mBloodMoonForceMode = {};
        mTime = timeToFloat(21, 30);
        mBloodMoonTimer = 0.0;
        gdm->setBool(true, mBloodyDayFlag);
        break;
    case BloodMoonForceMode::Immediate:
        mTimeUpdateMode = TimeUpdateMode::Forced;
        mTime = 0.0;
        _cc = 1.0;
        gdm->setBool(true, mBloodyDayFlag);
        mWasBloodyDay = true;
        if (!evt::Manager::instance()->hasActiveEvent()) {
            mBloodMoonForceMode = {};
            mTimeUpdateMode = TimeUpdateMode::Normal;
            _cc = 0.0;
        }
        break;
    }

    if (mWasBloodyDay && mTime > 12_h)
        mWasBloodyDay = false;

    _d0 = 1.0;

    switch (mTimeUpdateMode) {
    case TimeUpdateMode::Normal: {
        if (!mPlayedDemo103Or997 || evt::Manager::instance()->hasActiveEvent())
            break;

        const auto delta = mTimeStep * VFR::instance()->getDeltaTime();
        mIsTimeFlowingNormally = true;
        mTime += delta;
        if (mTime >= 24_h) {
            mTime -= 24_h;
            handleNewDay(HandleNewDayMode::Normal);
        }
        if (!mFindDungeonActivated && mTime >= 11_h)
            mTime = 11_h;

        _d0 = sead::Mathf::max(mTimeStep / DefaultTimeStep, 1.0);
        mBloodMoonTimer += delta;
        break;
    }

    case TimeUpdateMode::Force0400_b:
        mTime = 4_h;
        break;
    case TimeUpdateMode::Force0500_b:
        mTime = 5_h;
        break;
    case TimeUpdateMode::Force0700_b:
        mTime = 7_h;
        break;
    case TimeUpdateMode::Force1000_b:
        mTime = 10_h;
        break;
    case TimeUpdateMode::Force1700_b:
        mTime = 17_h;
        break;
    case TimeUpdateMode::Force1900_b:
        mTime = 19_h;
        break;
    case TimeUpdateMode::Force2100_b:
        mTime = 21_h;
        break;
    case TimeUpdateMode::Force0200_b:
        mTime = 2_h;
        break;

    case TimeUpdateMode::Force0000:
        mTime = 0_h;
        break;
    case TimeUpdateMode::Force0100:
        mTime = 1_h;
        break;
    case TimeUpdateMode::Force0200:
        mTime = 2_h;
        break;
    case TimeUpdateMode::Force0300:
        mTime = 3_h;
        break;
    case TimeUpdateMode::Force0400:
        mTime = 4_h;
        break;
    case TimeUpdateMode::Force0500:
        mTime = 5_h;
        break;
    case TimeUpdateMode::Force0600:
        mTime = 6_h;
        break;
    case TimeUpdateMode::Force0700:
        mTime = 7_h;
        break;
    case TimeUpdateMode::Force0800:
        mTime = 8_h;
        break;
    case TimeUpdateMode::Force0900:
        mTime = 9_h;
        break;
    case TimeUpdateMode::Force1000:
        mTime = 10_h;
        break;
    case TimeUpdateMode::Force1100:
        mTime = 11_h;
        break;
    case TimeUpdateMode::Force1200:
        mTime = 12_h;
        break;
    case TimeUpdateMode::Force1300:
        mTime = 13_h;
        break;
    case TimeUpdateMode::Force1400:
        mTime = 14_h;
        break;
    case TimeUpdateMode::Force1500:
        mTime = 15_h;
        break;
    case TimeUpdateMode::Force1600:
        mTime = 16_h;
        break;
    case TimeUpdateMode::Force1700:
        mTime = 17_h;
        break;
    case TimeUpdateMode::Force1800:
        mTime = 18_h;
        break;
    case TimeUpdateMode::Force1900:
        mTime = 19_h;
        break;
    case TimeUpdateMode::Force2000:
        mTime = 20_h;
        break;
    case TimeUpdateMode::Force2100:
        mTime = 21_h;
        break;
    case TimeUpdateMode::Force2200:
        mTime = 22_h;
        break;
    case TimeUpdateMode::Force2300:
        mTime = 23_h;
        break;

    case TimeUpdateMode::OnlyUpdateTimeOfDay:
        mTime += mTimeStep * VFR::instance()->getDeltaTime();
        if (mTime >= 24_h)
            mTime -= 24_h;
        break;

    case TimeUpdateMode::Force0400_c:
        mTime = 4_h;
        break;
    case TimeUpdateMode::Force0700_c:
        mTime = 7_h;
        break;
    case TimeUpdateMode::Force1000_c:
        mTime = 10_h;
        break;
    case TimeUpdateMode::Force1300_c:
        mTime = 13_h;
        break;
    case TimeUpdateMode::Force1700_c:
        mTime = 17_h;
        break;
    case TimeUpdateMode::Force1900_c:
        mTime = 19_h;
        break;
    case TimeUpdateMode::Force2100_c:
        mTime = 21_h;
        break;
    case TimeUpdateMode::Force0000_c:
        mTime = 0_h;
        break;

    case TimeUpdateMode::Forced:
        break;
    }

    const auto update_daytime_flags = [&] {
        if (mTime > 6_h && mTime < 18_h) {
            if (!is_daytime_flag_set) {
                gdm->setBool(true, mIsDaytimeFlag);
                gdm->setBool(false, mIsNighttimeFlag);
            }
        } else {
            if (is_daytime_flag_set) {
                gdm->setBool(false, mIsDaytimeFlag);
                gdm->setBool(true, mIsNighttimeFlag);
            }
        }
    };
    update_daytime_flags();

    bool update_division = false;
    bool division_flag_set = false;

    if (mTime >= 4_h && mTime < 7_h) {
        mTimeDivision = TimeDivision::Morning_A;
        u8 ok = 0;
        if (gdm->getBool(mIsMorningAFlag, &division_flag_set))
            ok = !division_flag_set;
        if (mTime < 5_h) {
            mTimeType = TimeType::Morning_A1;
            if (ok)
                update_division = true;
        } else {
            mTimeType = TimeType::Morning_A2;
            if (ok)
                [&] { update_division = true; }();
        }
    } else if (mTime >= 7_h && mTime < 10_h) {
        mTimeDivision = TimeDivision::Morning_B;
        mTimeType = TimeType::Morning_B;
        if (gdm->getBool(mIsMorningBFlag, &division_flag_set) && !division_flag_set)
            update_division = true;
    } else if (mTime >= 10_h && mTime < 13_h) {
        mTimeDivision = TimeDivision::Noon_A;
        mTimeType = TimeType::Noon_A;
        if (gdm->getBool(mIsNoonAFlag, &division_flag_set) && !division_flag_set)
            update_division = true;
    } else if (mTime >= 13_h && mTime < 17_h) {
        mTimeDivision = TimeDivision::Noon_B;
        mTimeType = TimeType::Noon_B;
        if (gdm->getBool(mIsNoonBFlag, &division_flag_set) && !division_flag_set)
            update_division = true;
    } else if (mTime >= 17_h && mTime < 19_h) {
        mTimeDivision = TimeDivision::Evening_A;
        mTimeType = TimeType::Evening_A;
        if (gdm->getBool(mIsEveningAFlag, &division_flag_set) && !division_flag_set)
            update_division = true;
    } else if (mTime >= 19_h && mTime < 21_h) {
        mTimeDivision = TimeDivision::Evening_B;
        mTimeType = TimeType::Evening_B;
        if (gdm->getBool(mIsEveningBFlag, &division_flag_set) && !division_flag_set)
            update_division = true;
    } else if (mTime >= 21_h && mTime < 24_h) {
        mTimeDivision = TimeDivision::Night_A;
        mTimeType = TimeType::Night_A;
        if (gdm->getBool(mIsNightAFlag, &division_flag_set) && !division_flag_set)
            update_division = true;
    } else {
        mTimeDivision = TimeDivision::Night_B;
        mTimeType = TimeType::Night_B;
        if (gdm->getBool(mIsNightBFlag, &division_flag_set) && !division_flag_set)
            update_division = true;
    }

    if (update_division) {
        const bool is_morning_a = mTimeDivision == TimeDivision::Morning_A;
        const bool is_morning_b = mTimeDivision == TimeDivision::Morning_B;
        const bool is_noon_a = mTimeDivision == TimeDivision::Noon_A;
        const bool is_noon_b = mTimeDivision == TimeDivision::Noon_B;
        const bool is_evening_a = mTimeDivision == TimeDivision::Evening_A;
        const bool is_evening_b = mTimeDivision == TimeDivision::Evening_B;
        const bool is_night_a = mTimeDivision == TimeDivision::Night_A;
        const bool is_night_b = mTimeDivision == TimeDivision::Night_B;
        gdm->setBool(is_morning_a, mIsMorningAFlag);
        gdm->setBool(is_morning_b, mIsMorningBFlag);
        gdm->setBool(is_noon_a, mIsNoonAFlag);
        gdm->setBool(is_noon_b, mIsNoonBFlag);
        gdm->setBool(is_evening_a, mIsEveningAFlag);
        gdm->setBool(is_evening_b, mIsEveningBFlag);
        gdm->setBool(is_night_a, mIsNightAFlag);
        gdm->setBool(is_night_b, mIsNightBFlag);
        gdm->setS32(mTimeDivision, mTimeDivisionFlag);
    }

    if (mBloodyEndReserveTimer != 0) {
        --mBloodyEndReserveTimer;
        if (mBloodyEndReserveTimer <= 0)
            gdm->setBool(false, mBloodyDayFlag);
    }

    gdm->setF32(mTime, mTimeFlag);
    gdm->setS32(mNumberOfDays, mNumberOfDaysFlag);
    gdm->setF32(mBloodMoonTimer, mBloodyMoonTimerFlag);
    gdm->setS32(mBloodyEndReserveTimer, mBloodyEndReserveTimerFlag);
    mAnimalMasterCtrl.calc();
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
