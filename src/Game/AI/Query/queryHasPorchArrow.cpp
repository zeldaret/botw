#include "Game/AI/Query/queryHasPorchArrow.h"
#include <evfl/Query.h>

namespace uking::query {

HasPorchArrow::HasPorchArrow(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasPorchArrow::~HasPorchArrow() = default;

// FIXME: implement
int HasPorchArrow::doQuery() {
    return -1;
}

void HasPorchArrow::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CheckNum");
}

void HasPorchArrow::loadParams() {
    getDynamicParam(&mCheckNum, "CheckNum");
}

}  // namespace uking::query
