#include "Game/AI/Query/queryHasItemDye.h"
#include <evfl/Query.h>
#include "Game/UI/uiPauseMenuDataMgr.h"

namespace uking::query {

HasItemDye::HasItemDye(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasItemDye::~HasItemDye() = default;

int HasItemDye::doQuery() {
    auto* pm = ui::PauseMenuDataMgr::instance();
    if (pm == nullptr)
        return 0;
    return pm->hasItemDye();
}

void HasItemDye::loadParams(const evfl::QueryArg& arg) {}

void HasItemDye::loadParams() {}

}  // namespace uking::query
