#include "Game/AI/Query/queryHasArmorAlreadyDyed.h"
#include <evfl/Query.h>
#include "Game/UI/uiPauseMenuDataMgr.h"

namespace uking::query {

HasArmorAlreadyDyed::HasArmorAlreadyDyed(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasArmorAlreadyDyed::~HasArmorAlreadyDyed() = default;

int HasArmorAlreadyDyed::doQuery() {
    auto* pm = ui::PauseMenuDataMgr::instance();
    if (pm == nullptr)
        return 0;

    return pm->countAlreadyDyedArmor() > 0;
}

void HasArmorAlreadyDyed::loadParams(const evfl::QueryArg& arg) {}

void HasArmorAlreadyDyed::loadParams() {}

}  // namespace uking::query
