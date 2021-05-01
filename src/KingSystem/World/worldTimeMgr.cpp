#include "KingSystem/World/worldTimeMgr.h"
#include "KingSystem/GameData/gdtManager.h"

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
    mMoonType = MoonType::Unknown;
}

void TimeMgr::init_(sead::Heap* heap) {
    mTime = DefaultTime;
    mTimeForAocFieldSkyEnv = DefaultTime;
    mTimeStep = DefaultTimeStep;
    mTimeUpdateMode = {};
    mBloodMoonTimer = 0.0;
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
    mAnimalMasterCtrl.state = {};
    mAnimalMasterCtrl.appearance_hour = {};
    mAnimalMasterCtrl.valid_hour = {};
    mAnimalMasterCtrl.start_day_of_week = {};
}

TimeMgr::~TimeMgr() = default;

void TimeMgr::calcType1_() {}

void TimeMgr::calcType2_() {}

void TimeMgr::setNewTime(float time) {
    if (time >= 0.0)
        mNewTime = time;
}

}  // namespace ksys::world
