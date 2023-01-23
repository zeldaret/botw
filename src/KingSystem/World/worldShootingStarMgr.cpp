#include "KingSystem/World/worldShootingStarMgr.h"
#include <container/seadObjArray.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actBaseProcHeapMgr.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::world {

static bool sScheduled = true;

static struct {
    int end = 3;
    int start = 21;
    int unk = 4;
} sHours;

static sead::Vector3f sStarProperty{};

ShootingStarMgr::ShootingStarMgr() = default;

ShootingStarMgr::~ShootingStarMgr() = default;

void ShootingStarMgr::init_(sead::Heap* heap) {
    if (Manager::instance()->isDemo())
        sScheduled = false;
    else
        initSchedule();
}

void ShootingStarMgr::initSchedule() {
    const s32& start_hour = sHours.start;
    const s32 end_hour = sHours.end - 1;

    s32 fall_hour;

    if (start_hour <= end_hour) {
        // Time range is continuous.
        fall_hour = sead::GlobalRandom::instance()->getS32Range(start_hour, end_hour);
    } else {
        // Time range is discontinuous.
        // Fill an array with valid hours, shuffle it, and take the first.
        sead::FixedObjArray<s32, 24> valid_hours;

        for (int i = start_hour; i < 24; ++i) {
            valid_hours.emplaceBack(i);
        }
        for (int i = 0; i < end_hour; ++i) {
            valid_hours.emplaceBack(i);
        }

        valid_hours.shuffle();
        fall_hour = *valid_hours[0];
    }

    mFallHour = fall_hour;
    mFallMinute = sead::GlobalRandom::instance()->getU32(59);
    mInitialised = true;
}

void ShootingStarMgr::calc_() {
    if (Manager::instance() != nullptr) {
        if (!mIsMainField)
            return;
        if (sScheduled) {
            if (Manager::instance()->isDemo()) {
                sScheduled = false;
                return;
            }
            TimeMgr* tm = Manager::instance()->getTimeMgr();
            if (tm != nullptr) {
                int hour = tm->getHour();
                if (mInitialised) {
                    if (hour == mFallHour && mFallMinute < tm->getMinute())
                        mNeedSpawnStar = true;
                } else if (Manager::instance() != nullptr) {
                    if (isScheduledTime())
                        initSchedule();
                }
            }
        }
    }
    if (mNeedSpawnStar && checkCamera()) {
        spawnShootingStar();
        mInitialised = false;
        mNeedSpawnStar = false;
    }
}

bool ShootingStarMgr::isScheduledTime() {
    bool result = false;
    if (Manager::instance() != nullptr) {
        auto* tm = Manager::instance()->getTimeMgr();
        if (tm != nullptr) {
            int hour = tm->getHour();
            if (sHours.start > sHours.unk) {
                result = sHours.unk < hour && hour < sHours.start;
            } else {
                result = sHours.unk < hour || hour < sHours.start;
            }
        }
    }
    return result;
}

void ShootingStarMgr::resetStarPosition() {
    if (gdt::Manager::instance() != nullptr)
        gdt::Manager::instance()->setVec3f(sead::Vector3f::zero, "ShootingStarPosition");
}

void ShootingStarMgr::spawnStar() {
    if (gdt::Manager::instance() == nullptr)
        return;

    if (!isStarPositionValid())
        return;

    act::InstParamPack pack;
    sead::Vector3f pos;
    tryGetStarPosition(&pos);

    pack.getBuffer().add(pos, "@P");
    act::ActorCreator::instance()->requestCreateActor("FldObj_ShootingStar",
                                                      act::BaseProcHeapMgr::instance()->getHeap(),
                                                      nullptr, &pack, nullptr, 1);
}

bool ShootingStarMgr::isStarPositionValid() {
    if (gdt::Manager::instance() == nullptr)
        return false;

    sead::Vector3f pos;
    if (!gdt::Manager::instance()->getParam().get().getVec3f(&pos, "ShootingStarPosition"))
        return false;
    return !(pos.x == 0 && pos.y == 0 && pos.z == 0);
}

bool ShootingStarMgr::tryGetStarPosition(sead::Vector3f* out) const {
    bool result = false;
    if (gdt::Manager::instance())
        result = gdt::Manager::instance()->getParam().get().getVec3f(out, "ShootingStarPosition");
    return result;
}

void ShootingStarMgr::setStarPosition(f32 x, f32 y, f32 z) {
    sead::Vector3f pos(x, y, z);

    if (gdt::Manager::instance()) {
        gdt::Manager::instance()->setVec3f(pos, "ShootingStarPosition");
    }
}

void ShootingStarMgr::setScheduled(bool enable) {
    sScheduled = enable;
}

void ShootingStarMgr::setShootingStarHours(int start, int end, int hr_unk) {
    sHours.start = start;
    sHours.end = end;
    sHours.unk = hr_unk;
}

}  // namespace ksys::world
