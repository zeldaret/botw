#include "Game/AI/Query/queryCheckMiniGameTimeOver.h"
#include <evfl/Query.h>

namespace uking::query {

CheckMiniGameTimeOver::CheckMiniGameTimeOver(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckMiniGameTimeOver::~CheckMiniGameTimeOver() = default;

// FIXME: implement
int CheckMiniGameTimeOver::doQuery() {
    return -1;
}

void CheckMiniGameTimeOver::loadParams(const evfl::QueryArg& arg) {}

void CheckMiniGameTimeOver::loadParams() {}

}  // namespace uking::query
