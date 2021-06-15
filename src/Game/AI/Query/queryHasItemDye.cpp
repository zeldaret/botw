#include "Game/AI/Query/queryHasItemDye.h"
#include <evfl/Query.h>

namespace uking::query {

HasItemDye::HasItemDye(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasItemDye::~HasItemDye() = default;

// FIXME: implement
int HasItemDye::doQuery() {
    return -1;
}

void HasItemDye::loadParams(const evfl::QueryArg& arg) {}

void HasItemDye::loadParams() {}

}  // namespace uking::query
