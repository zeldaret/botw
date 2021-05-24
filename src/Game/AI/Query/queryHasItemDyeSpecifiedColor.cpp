#include "Game/AI/Query/queryHasItemDyeSpecifiedColor.h"
#include <evfl/Query.h>

namespace uking::query {

HasItemDyeSpecifiedColor::HasItemDyeSpecifiedColor(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

HasItemDyeSpecifiedColor::~HasItemDyeSpecifiedColor() = default;

// FIXME: implement
int HasItemDyeSpecifiedColor::doQuery() {
    return -1;
}

void HasItemDyeSpecifiedColor::loadParams(const evfl::QueryArg& arg) {}

void HasItemDyeSpecifiedColor::loadParams() {}

}  // namespace uking::query
