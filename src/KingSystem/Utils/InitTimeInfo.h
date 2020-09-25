#pragma once

#include <time/seadTickTime.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class InitTimeInfo {
public:
    InitTimeInfo() = default;

    sead::TickTime getInitStartTime() const { return mInitStartTime; }
    sead::TickSpan getInitDuration() const { return mInitDuration; }

    void finish() { mInitDuration = sead::TickTime().diff(mInitStartTime); }

private:
    sead::TickTime mInitStartTime;
    sead::TickSpan mInitDuration;
};
KSYS_CHECK_SIZE_NX150(InitTimeInfo, 0x10);

}  // namespace ksys::util
