#include "Game/AI/Query/queryWhatDungeonType.h"
#include <evfl/Query.h>
#include "KingSystem/World/worldManager.h"

namespace uking::query {

WhatDungeonType::WhatDungeonType(const InitArg& arg) : ksys::act::ai::Query(arg) {}

WhatDungeonType::~WhatDungeonType() = default;

int WhatDungeonType::doQuery() {
    return u8(ksys::world::Manager::instance()->getDungeonType());
}

void WhatDungeonType::loadParams(const evfl::QueryArg& arg) {}

void WhatDungeonType::loadParams() {}

}  // namespace uking::query
