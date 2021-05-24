#include "Game/AI/Query/queryCheckPlayerHellType.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlayerHellType::CheckPlayerHellType(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerHellType::~CheckPlayerHellType() = default;

// FIXME: implement
int CheckPlayerHellType::doQuery() {
    return -1;
}

void CheckPlayerHellType::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "PlayerHellType");
}

void CheckPlayerHellType::loadParams() {
    getDynamicParam(&mPlayerHellType, "PlayerHellType");
}

}  // namespace uking::query
