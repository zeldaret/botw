#include "Game/AI/Query/queryIsOnInstEventFlag.h"
#include <evfl/Query.h>

namespace uking::query {

IsOnInstEventFlag::IsOnInstEventFlag(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsOnInstEventFlag::~IsOnInstEventFlag() = default;

// FIXME: implement
int IsOnInstEventFlag::doQuery() {
    return -1;
}

void IsOnInstEventFlag::loadParams(const evfl::QueryArg& arg) {}

void IsOnInstEventFlag::loadParams() {}

}  // namespace uking::query
