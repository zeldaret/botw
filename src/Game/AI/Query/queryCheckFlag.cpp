#include "Game/AI/Query/queryCheckFlag.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckFlag::CheckFlag(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckFlag::~CheckFlag() = default;

int CheckFlag::doQuery() {
    bool value = false;
    ksys::gdt::Manager::instance()->getParamBypassPerm().get().getBool(&value, mFlagName);
    return value;
}

void CheckFlag::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "FlagName");
}

void CheckFlag::loadParams() {
    getDynamicParam(&mFlagName, "FlagName");
}

}  // namespace uking::query
