#include "Game/AI/Query/queryCheckSiteBossDamageAnm.h"
#include <evfl/Query.h>

namespace uking::query {

CheckSiteBossDamageAnm::CheckSiteBossDamageAnm(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckSiteBossDamageAnm::~CheckSiteBossDamageAnm() = default;

// FIXME: implement
int CheckSiteBossDamageAnm::doQuery() {
    return -1;
}

void CheckSiteBossDamageAnm::loadParams(const evfl::QueryArg& arg) {}

void CheckSiteBossDamageAnm::loadParams() {}

}  // namespace uking::query
