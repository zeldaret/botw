#include "Game/AI/Query/queryCheckFame.h"
#include <evfl/query.h>

namespace uking::query {

CheckFame::CheckFame(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckFame::~CheckFame() = default;

// FIXME: implement
int CheckFame::doQuery() {
    return -1;
}

void CheckFame::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Value");
}

void CheckFame::loadParams() {
    getDynamicParam(&mValue, "Value");
}

}  // namespace uking::query
