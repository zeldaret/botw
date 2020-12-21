#include "Game/AI/Query/queryRandomChoice3.h"
#include <evfl/query.h>

namespace uking::query {

RandomChoice3::RandomChoice3(const InitArg& arg) : ksys::act::ai::Query(arg) {}

RandomChoice3::~RandomChoice3() = default;

// FIXME: implement
int RandomChoice3::doQuery() {
    return -1;
}

void RandomChoice3::loadParams(const evfl::QueryArg& arg) {}

void RandomChoice3::loadParams() {}

}  // namespace uking::query
