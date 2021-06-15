#include "Game/AI/Query/queryIsArriveAnchorForRain.h"
#include <evfl/Query.h>

namespace uking::query {

IsArriveAnchorForRain::IsArriveAnchorForRain(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsArriveAnchorForRain::~IsArriveAnchorForRain() = default;

// FIXME: implement
int IsArriveAnchorForRain::doQuery() {
    return -1;
}

void IsArriveAnchorForRain::loadParams(const evfl::QueryArg& arg) {}

void IsArriveAnchorForRain::loadParams() {}

}  // namespace uking::query
