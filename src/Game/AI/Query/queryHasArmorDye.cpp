#include "Game/AI/Query/queryHasArmorDye.h"
#include <evfl/Query.h>
#include "Game/UI/uiPauseMenuDataMgr.h"

namespace uking::query {

HasArmorDye::HasArmorDye(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasArmorDye::~HasArmorDye() = default;

int HasArmorDye::doQuery() {
    auto* pm = ui::PauseMenuDataMgr::instance();
    if (pm == nullptr)
        return 0;

    return pm->countArmorDye() > 0;
}

void HasArmorDye::loadParams(const evfl::QueryArg& arg) {}

void HasArmorDye::loadParams() {}

}  // namespace uking::query
