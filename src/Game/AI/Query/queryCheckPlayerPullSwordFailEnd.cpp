#include "Game/AI/Query/queryCheckPlayerPullSwordFailEnd.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlayerPullSwordFailEnd::CheckPlayerPullSwordFailEnd(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckPlayerPullSwordFailEnd::~CheckPlayerPullSwordFailEnd() = default;

// FIXME: implement
int CheckPlayerPullSwordFailEnd::doQuery() {
    return -1;
}

void CheckPlayerPullSwordFailEnd::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerPullSwordFailEnd::loadParams() {}

}  // namespace uking::query
