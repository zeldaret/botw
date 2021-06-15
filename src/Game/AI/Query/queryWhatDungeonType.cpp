#include "Game/AI/Query/queryWhatDungeonType.h"
#include <evfl/Query.h>

namespace uking::query {

WhatDungeonType::WhatDungeonType(const InitArg& arg) : ksys::act::ai::Query(arg) {}

WhatDungeonType::~WhatDungeonType() = default;

// FIXME: implement
int WhatDungeonType::doQuery() {
    return -1;
}

void WhatDungeonType::loadParams(const evfl::QueryArg& arg) {}

void WhatDungeonType::loadParams() {}

}  // namespace uking::query
