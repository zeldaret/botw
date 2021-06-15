#include "Game/AI/Query/queryCheckFame.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckFame::CheckFame(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckFame::~CheckFame() = default;

int CheckFame::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm)
        return 0;

    int fame = 0;
    if (!gdm->getParamBypassPerm().get().getS32(&fame, "FamouseValue"))  // sic
        return 0;

    return fame >= *mValue;
}

void CheckFame::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Value");
}

void CheckFame::loadParams() {
    getDynamicParam(&mValue, "Value");
}

}  // namespace uking::query
