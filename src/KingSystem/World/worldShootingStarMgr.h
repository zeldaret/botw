#pragma once

#include <math/seadVector.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

class ShootingStarMgr : public Job {
public:
    ShootingStarMgr();
    virtual ~ShootingStarMgr();

    JobType getType() const override { return JobType::ShootingStar; }

    virtual void init_(sead::Heap* heap) override;
    virtual void calc_() override;
    virtual void reset();

    static void setScheduled(bool enable);
    void initSchedule();
    static bool isScheduledTime();

    bool tryGetStarPosition(sead::Vector3f* out) const;
    static void setStarPosition(f32 x, f32 y, f32 z);
    static void spawnShootingStar();
    void spawnStar();

    static bool checkCamera();
    bool isStarPositionValid();
    static void setShootingStarHours(int start, int end, int hr_unk);
    static void resetStarPosition();
    static void resetStarProperty();

    s32 mFallHour = 0;
    s32 mFallMinute = 0;
    bool mInitialised = false;
    bool mNeedSpawnStar = false;
    bool mIsMainField = false;
    bool _2b = false;
};
KSYS_CHECK_SIZE_NX150(ShootingStarMgr, 0x30);

}  // namespace ksys::world
