#include "Game/AI/Query/queryWhatDayOfTheWeek.h"
#include <evfl/Query.h>

namespace uking::query {

WhatDayOfTheWeek::WhatDayOfTheWeek(const InitArg& arg) : ksys::act::ai::Query(arg) {}

WhatDayOfTheWeek::~WhatDayOfTheWeek() = default;

// FIXME: implement
int WhatDayOfTheWeek::doQuery() {
    return -1;
}

void WhatDayOfTheWeek::loadParams(const evfl::QueryArg& arg) {}

void WhatDayOfTheWeek::loadParams() {}

}  // namespace uking::query
