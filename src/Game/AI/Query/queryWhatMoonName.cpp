#include "Game/AI/Query/queryWhatMoonName.h"
#include <evfl/Query.h>

namespace uking::query {

WhatMoonName::WhatMoonName(const InitArg& arg) : ksys::act::ai::Query(arg) {}

WhatMoonName::~WhatMoonName() = default;

// FIXME: implement
int WhatMoonName::doQuery() {
    return -1;
}

void WhatMoonName::loadParams(const evfl::QueryArg& arg) {}

void WhatMoonName::loadParams() {}

}  // namespace uking::query
