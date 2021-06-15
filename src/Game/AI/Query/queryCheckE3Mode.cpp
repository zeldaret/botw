#include "Game/AI/Query/queryCheckE3Mode.h"
#include <evfl/Query.h>

namespace uking::query {

CheckE3Mode::CheckE3Mode(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckE3Mode::~CheckE3Mode() = default;

// FIXME: implement
int CheckE3Mode::doQuery() {
    return -1;
}

void CheckE3Mode::loadParams(const evfl::QueryArg& arg) {}

void CheckE3Mode::loadParams() {}

}  // namespace uking::query
