#include "Game/AI/Query/queryHasArmorDye.h"
#include <evfl/Query.h>

namespace uking::query {

HasArmorDye::HasArmorDye(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasArmorDye::~HasArmorDye() = default;

// FIXME: implement
int HasArmorDye::doQuery() {
    return -1;
}

void HasArmorDye::loadParams(const evfl::QueryArg& arg) {}

void HasArmorDye::loadParams() {}

}  // namespace uking::query
