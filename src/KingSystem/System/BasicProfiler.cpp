#include "KingSystem/System/BasicProfiler.h"
#include <container/seadObjList.h>
#include <devenv/seadEnvUtil.h>
#include <prim/seadSafeString.h>
#include <prim/seadStorageFor.h>
#include <thread/seadAtomic.h>
#include <time/seadTickTime.h>
#include "KingSystem/Utils/Debug.h"

namespace ksys {

struct ProfilerRecord {
    ProfilerRecord() { enter_time.construct(); }

    sead::StorageFor<sead::TickTime, true> enter_time{};
    const char* description{};
};

struct ProfilerInitInfo {
    ProfilerInitInfo() { time.setNow(); }
    sead::TickTime time;
};

ProfilerInitInfo sProfilerInitInfo;
sead::Atomic<bool> sProfilerUnusedBool = true;
sead::FixedObjList<ProfilerRecord, 10> sProfilerRecords;

void BasicProfiler::push(const char* description) {
    auto* record = sProfilerRecords.emplaceBack();
    record->enter_time->setNow();
    record->description = description;
}

void BasicProfiler::pop(const char* description) {
    if (sProfilerRecords.isEmpty())
        return;

    auto* record = sProfilerRecords.back();
    if (!record)
        return;

    if (sead::SafeString(description) != record->description)
        return;

    if (sProfilerRecords.size() == 1 && sead::EnvUtil::getRomType() != "Show_2017_1st" &&
        sead::EnvUtil::getRomType() != "RID_Demo") {
        util::PrintDebug(sead::FormatFixedSafeString<64>(
            "%s:%.3f秒", record->description,
            record->enter_time->diffToNow().toMilliSeconds() / 1000.0f));
    }

    sProfilerRecords.erase(record);
}

}  // namespace ksys
