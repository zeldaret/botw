#include "Game/AI/Query/queryCheckPlayerFastFadeDead.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlayerFastFadeDead::CheckPlayerFastFadeDead(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerFastFadeDead::~CheckPlayerFastFadeDead() = default;

// FIXME: implement
int CheckPlayerFastFadeDead::doQuery() {
    return -1;
}

void CheckPlayerFastFadeDead::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerFastFadeDead::loadParams() {}

}  // namespace uking::query
