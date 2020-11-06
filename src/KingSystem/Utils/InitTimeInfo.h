#pragma once

#include <time/seadTickTime.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class InitTimeInfo {
public:
    InitTimeInfo() = default;
    explicit InitTimeInfo(sead::TickTime start_time) : mInitStartTime(start_time) {}

    sead::TickTime getInitStartTime() const { return mInitStartTime; }
    sead::TickSpan getInitDuration() const { return mInitDuration; }

    void finish() { mInitDuration = sead::TickTime().diff(mInitStartTime); }

private:
    sead::TickTime mInitStartTime;
    sead::TickSpan mInitDuration;
};
KSYS_CHECK_SIZE_NX150(InitTimeInfo, 0x10);

struct InitConstants {
    InitConstants() {
        _0 = 0;
        _4 = 0x8004EF;
    }

    u32 _0;
    u32 _4;
};

class InitTimeInfoEx {
public:
    explicit InitTimeInfoEx(sead::TickTime start_time = {}) : mInfo(start_time) {
        mConstants._0 = 0;
        mConstants._4 = 0x8004EF;
    }

    InitTimeInfo& getInfo() { return mInfo; }
    const InitTimeInfo& getInfo() const { return mInfo; }

private:
    InitConstants mConstants;
    InitTimeInfo mInfo;
};
KSYS_CHECK_SIZE_NX150(InitTimeInfoEx, 0x18);

}  // namespace ksys::util
