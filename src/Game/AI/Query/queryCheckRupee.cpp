#include "Game/AI/Query/queryCheckRupee.h"
#include <evfl/Query.h>

namespace uking::query {

CheckRupee::CheckRupee(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckRupee::~CheckRupee() = default;

// FIXME: implement
int CheckRupee::doQuery() {
    return -1;
}

void CheckRupee::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Value");
}

void CheckRupee::loadParams() {
    getDynamicParam(&mValue, "Value");
}

}  // namespace uking::query
