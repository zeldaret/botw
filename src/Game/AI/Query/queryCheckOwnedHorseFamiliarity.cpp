#include "Game/AI/Query/queryCheckOwnedHorseFamiliarity.h"
#include <evfl/Query.h>

namespace uking::query {

CheckOwnedHorseFamiliarity::CheckOwnedHorseFamiliarity(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckOwnedHorseFamiliarity::~CheckOwnedHorseFamiliarity() = default;

// FIXME: implement
int CheckOwnedHorseFamiliarity::doQuery() {
    return -1;
}

void CheckOwnedHorseFamiliarity::loadParams(const evfl::QueryArg& arg) {}

void CheckOwnedHorseFamiliarity::loadParams() {}

}  // namespace uking::query
