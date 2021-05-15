#pragma once

#include <array>
#include <prim/seadDelegateEventSlot.h>
#include <prim/seadEnum.h>
#include <prim/seadSizedEnum.h>
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

SEAD_ENUM(TimeDivision, Morning_A,Morning_B,Noon_A,Noon_B,Evening_A,Evening_B,Night_A,Night_B)
SEAD_ENUM(TimeType, Morning_A1,Morning_A2,Morning_B,Noon_A,Noon_B,Evening_A,Evening_B,Night_A,Night_B)

enum class MoonType : u8 {
    FullMoon = 0,
    WaningGibbous = 1,
    ThirdQuarter = 2,
    WaningCrescent = 3,
    NewMoon = 4,
    WaxingCrescent = 5,
    FirstQuarter = 6,
    WaxingGibbous = 7,
    Auto = 0xff,
};

constexpr float timeToFloat(int h, int m) {
    return float(h) * 15.0f + float(m) * (15.0f / 60.0f);
}

constexpr float durationToFloat(int h, int m) {
    return timeToFloat(h, m);
}

constexpr float operator""_days(unsigned long long hours) {
    return timeToFloat(static_cast<int>(24 * hours), 0);
}

constexpr float operator""_h(unsigned long long hours) {
    return timeToFloat(static_cast<int>(hours), 0);
}

constexpr float operator""_m(unsigned long long minutes) {
    return timeToFloat(0, static_cast<int>(minutes));
}

// TODO
class TimeMgr : public Job {
    SEAD_RTTI_OVERRIDE(TimeMgr, Job)
public:
    enum class BloodMoonForceMode {
        Disabled = 0,
        /// Force a blood moon to happen tonight and set the time to 23:29.
        Force23h = 1,
        /// Force a blood moon to happen tonight and set the time to 21:30.
        Force21h = 2,
        /// Force a blood moon to happen tonight and set the time to 00:00.
        Immediate = 99,
    };

    struct NewDayEvent {
        virtual ~NewDayEvent() = default;
    };

    TimeMgr();
    ~TimeMgr() override;

    JobType getType() const override { return JobType::Time; }

    void reset();
    void resetForStageUnload();

    void callBloodMoonDemo();
    bool isBloodMoonProhibited() const;
    bool isBloodMoonProhibitionFlagSet() const;
    bool isInRelicBattle() const;

    void resetBloodMoonTimer();
    void setTimeWithoutDayChecks(float time);
    void setTime(float time);
    bool isBloodyDay() const;
    float getTime() const { return mTime; }
    float getTimeForSkyEnv() const;
    void setAocFieldTimeForSkyEnv(float time);
    int getHour() const;
    int getMinute() const;
    MoonType getMoonType() const;
    bool willBloodMoonHappenTonight() const;
    float getTemperatureMultiplier() const;
    bool isTimeFlowingNormally() const;

    int getTimeDivision() const { return mTimeDivision; }
    sead::DelegateEvent<const NewDayEvent&>& getNewDaySignal() { return mNewDaySignal; }
    float getTimeStep() const { return mTimeStep; }
    float getBloodMoonTimer() const { return mBloodMoonTimer; }
    int getNumberOfDays() const { return mNumberOfDays; }
    BloodMoonForceMode getBloodMoonForceMode() const { return mBloodMoonForceMode; }
    bool isPlayedDemo103Or997() const { return mPlayedDemo103Or997; }
    bool isFindDungeonActivated() const { return mFindDungeonActivated; }
    bool isResetGdtOnNextSceneUnloadForBloodMoon() const {
        return mResetGdtOnNextSceneUnloadForBloodMoon;
    }
    bool wasBloodyDay() const { return mWasBloodyDay; }
    bool isBloodMoonForced() const { return mBloodMoonForceMode != BloodMoonForceMode::Disabled; }

    gdt::FlagHandle getWaterRelicRainStopFlag() const { return mWaterRelicRainStopFlag; }

protected:
    void init_(sead::Heap* heap) override;
    void calc_() override;
    void calcType1_() override;
    void calcType2_() override;

private:
    enum class TimeUpdateMode {
        Normal = 0,

        Force0400_b = 1,
        Force0500_b = 2,
        Force0700_b = 3,
        Force1000_b = 4,
        Force1700_b = 5,
        Force1900_b = 6,
        Force2100_b = 7,
        Force0200_b = 8,

        Force0000 = 9,
        Force0100 = 10,
        Force0200 = 11,
        Force0300 = 12,
        Force0400 = 13,
        Force0500 = 14,
        Force0600 = 15,
        Force0700 = 16,
        Force0800 = 17,
        Force0900 = 18,
        Force1000 = 19,
        Force1100 = 20,
        Force1200 = 21,
        Force1300 = 22,
        Force1400 = 23,
        Force1500 = 24,
        Force1600 = 25,
        Force1700 = 26,
        Force1800 = 27,
        Force1900 = 28,
        Force2000 = 29,
        Force2100 = 30,
        Force2200 = 31,
        Force2300 = 32,

        OnlyUpdateTimeOfDay = 34,

        Force0400_c = 35,
        Force0700_c = 36,
        Force1000_c = 37,
        Force1300_c = 38,
        Force1700_c = 39,
        Force1900_c = 40,
        Force2100_c = 41,
        Force0000_c = 42,

        Forced = 0xff,
    };

    enum class HandleNewDayMode {
        Normal,
        Forced,
    };

    struct AnimalMasterController {
        void calc();

        void resetState() {
            state = {};
            appearance_hour = {};
            valid_hour = {};
            start_day_of_week = {};
        }

        gdt::FlagHandle appearance_flag = gdt::InvalidHandle;
        gdt::FlagHandle existence_flag = gdt::InvalidHandle;
        int state{};
        int appearance_hour{};
        int valid_hour{};
        u8 start_day_of_week{};
    };
    KSYS_CHECK_SIZE_NX150(AnimalMasterController, 0x18);

    static constexpr float DefaultTime = timeToFloat(5, 15);
    static constexpr float DefaultTimeStep = durationToFloat(0, 1) / 30.0;

    void loadFlags();
    void handleNewDay(HandleNewDayMode mode);

    bool _20;
    bool _21;
    u16 _22;
    bool _24;
    int mTimeDivision{};
    int mTimeType{};
    struct {
        std::array<bool, 4> _0;
        int _4;
    } _30[10];
    sead::DelegateEvent<const NewDayEvent&> mNewDaySignal;
    AnimalMasterController mAnimalMasterCtrl;
    float mTime = DefaultTime;
    float mTimeForAocFieldSkyEnv = DefaultTime;
    float mNewTime = -1.0;
    float mTimeStep = DefaultTimeStep;
    float mBloodMoonTimer = 0.0;
    float _cc;
    float _d0 = 1.0;
    gdt::FlagHandle mTimeFlag = gdt::InvalidHandle;
    gdt::FlagHandle mNumberOfDaysFlag = gdt::InvalidHandle;
    gdt::FlagHandle mTimeDivisionFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsDaytimeFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsNighttimeFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsPlayedDemo103Flag = gdt::InvalidHandle;
    gdt::FlagHandle mDemo997Flag = gdt::InvalidHandle;
    gdt::FlagHandle mFindDungeonActivatedFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsMorningAFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsMorningBFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsNoonAFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsNoonBFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsEveningAFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsEveningBFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsNightAFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsNightBFlag = gdt::InvalidHandle;
    gdt::FlagHandle mWaterRelicRainStopFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsGetPlayerStole2Flag = gdt::InvalidHandle;
    gdt::FlagHandle mBloodyDayFlag = gdt::InvalidHandle;
    gdt::FlagHandle mBloodyMoonTimerFlag = gdt::InvalidHandle;
    gdt::FlagHandle mBloodyEndReserveTimerFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsInHyruleCastleAreaFlag = gdt::InvalidHandle;
    gdt::FlagHandle mLastBossGanonBeastGenerateFlag = gdt::InvalidHandle;
    gdt::FlagHandle mWindRelicBattleStartFlag = gdt::InvalidHandle;
    gdt::FlagHandle mElectricRelicBattleFlag = gdt::InvalidHandle;
    gdt::FlagHandle mWaterRelicBattleTimeFlag = gdt::InvalidHandle;
    int mNumberOfDays{};
    gdt::FlagHandle mBloodyMoonProhibitionFlag = gdt::InvalidHandle;
    int mBloodyEndReserveTimer{};
    bool mNeedToHandleNewDay{};
    sead::SizedEnum<TimeUpdateMode, u8> mTimeUpdateMode = TimeUpdateMode::Normal;
    sead::SizedEnum<BloodMoonForceMode, u8> mBloodMoonForceMode;
    bool _14b;
    MoonType mMoonType;
    bool mPlayedDemo103Or997{};
    bool mFindDungeonActivated{};
    bool mIsTimeFlowingNormally{};
    bool mWasBloodyDayAndDayPassed{};
    bool mResetGdtOnNextSceneUnloadForBloodMoon{};
    bool mWasBloodyDay{};
};
KSYS_CHECK_SIZE_NX150(TimeMgr, 0x158);

inline int TimeMgr::getMinute() const {
    auto remainder = float(int(mTime * 1000.f) % int(durationToFloat(1, 0) * 1000.f)) / 1000.f;
    return int((remainder / durationToFloat(1, 0)) * 60.f);
}

}  // namespace ksys::world
