#include "Game/AI/Query/queryCheckRupee.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckRupee::CheckRupee(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckRupee::~CheckRupee() = default;

int CheckRupee::doQuery() {
    auto* mgr = ksys::gdt::Manager::instance();
    s32 value = 0;
    if (!mgr->getParamBypassPerm().get().getS32(&value, "CurrentRupee"))
        return 0;
    return value >= *mValue;
}

void CheckRupee::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Value");
}

void CheckRupee::loadParams() {
    getDynamicParam(&mValue, "Value");
}

}  // namespace uking::query
