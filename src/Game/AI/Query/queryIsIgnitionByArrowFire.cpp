#include "Game/AI/Query/queryIsIgnitionByArrowFire.h"
#include <evfl/Query.h>

namespace uking::query {

IsIgnitionByArrowFire::IsIgnitionByArrowFire(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsIgnitionByArrowFire::~IsIgnitionByArrowFire() = default;

// FIXME: implement
int IsIgnitionByArrowFire::doQuery() {
    return -1;
}

void IsIgnitionByArrowFire::loadParams(const evfl::QueryArg& arg) {}

void IsIgnitionByArrowFire::loadParams() {}

}  // namespace uking::query
