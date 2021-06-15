#include "Game/AI/Query/queryCheckGetDemoTypeFromArg.h"
#include <evfl/Query.h>
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::query {

namespace {
enum CheckGetDemoTypeFromArgResult {
    Result_Default = 0,
    Result_Deluxe = 1,
    Result_HighGrade = 2,
};
}

CheckGetDemoTypeFromArg::CheckGetDemoTypeFromArg(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckGetDemoTypeFromArg::~CheckGetDemoTypeFromArg() = default;

int CheckGetDemoTypeFromArg::doQuery() {
    if (*mUseLastTryGetItemName && ui::PauseMenuDataMgr::instance()) {
        auto* item = ui::PauseMenuDataMgr::instance()->getLastAddedItem();
        if (item->get25()) {
            if (ksys::act::hasTag(item->getName(), ksys::act::tags::ApplyHighGradeGetDemo))
                return Result_HighGrade;
            if (ksys::act::hasTag(item->getName(), ksys::act::tags::ApplyDeluxeGetDemo))
                return Result_Deluxe;
            return Result_Default;
        }
    }

    if (mCheckTargetActorName.isEmpty()) {
        if (auto* actor = mActor) {
            if (ksys::act::hasTag(actor, ksys::act::tags::ApplyHighGradeGetDemo))
                return Result_HighGrade;
            if (ksys::act::hasTag(actor, ksys::act::tags::ApplyDeluxeGetDemo))
                return Result_Deluxe;
        }
    } else {
        if (ksys::act::hasTag(mCheckTargetActorName, ksys::act::tags::ApplyHighGradeGetDemo))
            return Result_HighGrade;
        if (ksys::act::hasTag(mCheckTargetActorName, ksys::act::tags::ApplyDeluxeGetDemo))
            return Result_Deluxe;
    }

    return Result_Default;
}

void CheckGetDemoTypeFromArg::loadParams(const evfl::QueryArg& arg) {
    loadBool(arg.param_accessor, "UseLastTryGetItemName");
    loadString(arg.param_accessor, "CheckTargetActorName");
}

void CheckGetDemoTypeFromArg::loadParams() {
    getDynamicParam(&mUseLastTryGetItemName, "UseLastTryGetItemName");
    getDynamicParam(&mCheckTargetActorName, "CheckTargetActorName");
}

}  // namespace uking::query
