#include "Game/AI/Query/queryWhatMoonName.h"
#include <evfl/Query.h>
#include "KingSystem/World/worldManager.h"

namespace uking::query {

WhatMoonName::WhatMoonName(const InitArg& arg) : ksys::act::ai::Query(arg) {}

WhatMoonName::~WhatMoonName() = default;

int WhatMoonName::doQuery() {
    auto* tm = ksys::world::Manager::instance()->getTimeMgr();
    return static_cast<int>(tm->getMoonType());
}

void WhatMoonName::loadParams(const evfl::QueryArg& arg) {}

void WhatMoonName::loadParams() {}

}  // namespace uking::query
