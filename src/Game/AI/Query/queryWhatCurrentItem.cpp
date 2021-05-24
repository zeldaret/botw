#include "Game/AI/Query/queryWhatCurrentItem.h"
#include <evfl/Query.h>

namespace uking::query {

WhatCurrentItem::WhatCurrentItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

WhatCurrentItem::~WhatCurrentItem() = default;

// FIXME: implement
int WhatCurrentItem::doQuery() {
    return -1;
}

void WhatCurrentItem::loadParams(const evfl::QueryArg& arg) {}

void WhatCurrentItem::loadParams() {}

}  // namespace uking::query
