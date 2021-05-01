#pragma once

#include <array>
#include <prim/seadDelegateEventSlot.h>
#include <prim/seadEnum.h>
#include <prim/seadSizedEnum.h>
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

enum class TimeDivision {
    Morning_A,
    Morning_B,
    Noon_A,
    Noon_B,
    Evening_A,
    Evening_B,
    Night_A,
    Night_B,
};
SEAD_ENUM(TimeDivisionEnum, Morning_A,Morning_B,Noon_A,Noon_B,Evening_A,Evening_B,Night_A,Night_B)

enum class MoonType {
    Unknown = 0xff,
};

constexpr float timeToFloat(int h, int m) {
    return float(h) * 15.0f + float(m) * (15.0f / 60.0f);
}

constexpr float durationToFloat(int h, int m) {
    return timeToFloat(h, m);
}

// TODO
class TimeMgr : public Job {
    SEAD_RTTI_OVERRIDE(TimeMgr, Job)
public:
    struct NewDayEvent {
        virtual ~NewDayEvent() = default;
    };

    TimeMgr();
    ~TimeMgr() override;

    JobType getType() const override { return JobType::Time; }

    void resetForStageUnload();
    void setNewTime(float time);

protected:
    void init_(sead::Heap* heap) override;
    void calc_() override;
    void calcType1_() override;
    void calcType2_() override;

private:
    enum class TimeUpdateMode {

    };

    struct AnimalMasterController {
        enum class State {

        };

        void calc();

        gdt::FlagHandle appearance_flag = gdt::InvalidHandle;
        gdt::FlagHandle existence_flag = gdt::InvalidHandle;
        State state{};
        int appearance_hour{};
        int valid_hour{};
        u8 start_day_of_week{};
    };
    KSYS_CHECK_SIZE_NX150(AnimalMasterController, 0x18);

    static constexpr float DefaultTime = timeToFloat(5, 15);
    static constexpr float DefaultTimeStep = durationToFloat(0, 1) / 30.0;

    bool _20;
    bool _21;
    u16 _22;
    bool _24;
    TimeDivision mTimeDivision{};
    TimeDivision mTimeDivision2{};
    struct {
        std::array<bool, 4> _0;
        int _4;
    } _30[10];
    sead::DelegateEvent<NewDayEvent> mNewDaySignal;
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
    gdt::FlagHandle mIsMoonAFlag = gdt::InvalidHandle;
    gdt::FlagHandle mIsMoonBFlag = gdt::InvalidHandle;
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
    gdt::FlagHandle mWindElectricBattleStartFlag = gdt::InvalidHandle;
    gdt::FlagHandle mElectricRelicBattleFlag = gdt::InvalidHandle;
    gdt::FlagHandle mWindRelicBattleTimeFlag = gdt::InvalidHandle;
    int mNumberOfDays{};
    gdt::FlagHandle mBloodyMoonProhibitionFlag = gdt::InvalidHandle;
    int mBloodyEndReserveTimer{};
    bool mNeedToHandleNewDay{};
    sead::SizedEnum<TimeUpdateMode, u8> mTimeUpdateMode{};
    bool mForceBloodyDay;
    bool _14b;
    sead::SizedEnum<MoonType, u8> mMoonType;
    bool mPlayedDemo103Or997{};
    bool mFindDungeonActivated{};
    bool _14f{};
    bool mWasBloodyDayAndDayPassed{};
    bool mResetGdtOnNextSceneUnloadForBloodMoon{};
    bool mWasBloodyDay{};
};
KSYS_CHECK_SIZE_NX150(TimeMgr, 0x158);

}  // namespace ksys::world
