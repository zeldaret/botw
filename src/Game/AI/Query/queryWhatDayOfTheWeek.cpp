#include "Game/AI/Query/queryWhatDayOfTheWeek.h"
#include <evfl/Query.h>
#include "KingSystem/World/worldManager.h"

namespace uking::query {

WhatDayOfTheWeek::WhatDayOfTheWeek(const InitArg& arg) : ksys::act::ai::Query(arg) {}

WhatDayOfTheWeek::~WhatDayOfTheWeek() = default;

int WhatDayOfTheWeek::doQuery() {
    return u8(ksys::world::Manager::instance()->getTimeMgr()->getNumberOfDays() % 7);
}

void WhatDayOfTheWeek::loadParams(const evfl::QueryArg& arg) {}

void WhatDayOfTheWeek::loadParams() {}

}  // namespace uking::query
