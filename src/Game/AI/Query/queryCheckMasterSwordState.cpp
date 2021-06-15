#include "Game/AI/Query/queryCheckMasterSwordState.h"
#include <evfl/Query.h>

namespace uking::query {

CheckMasterSwordState::CheckMasterSwordState(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckMasterSwordState::~CheckMasterSwordState() = default;

// FIXME: implement
int CheckMasterSwordState::doQuery() {
    return -1;
}

void CheckMasterSwordState::loadParams(const evfl::QueryArg& arg) {}

void CheckMasterSwordState::loadParams() {}

}  // namespace uking::query
