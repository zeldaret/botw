#include "Game/AI/Query/queryRandomChoice2.h"
#include <evfl/query.h>

namespace uking::query {

RandomChoice2::RandomChoice2(const InitArg& arg) : ksys::act::ai::Query(arg) {}

RandomChoice2::~RandomChoice2() = default;

// FIXME: implement
int RandomChoice2::doQuery() {
    return -1;
}

void RandomChoice2::loadParams(const evfl::QueryArg& arg) {}

void RandomChoice2::loadParams() {}

}  // namespace uking::query
