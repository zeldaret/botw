#include "Game/AI/Query/queryRandomChoice4.h"
#include <evfl/query.h>

namespace uking::query {

RandomChoice4::RandomChoice4(const InitArg& arg) : ksys::act::ai::Query(arg) {}

RandomChoice4::~RandomChoice4() = default;

// FIXME: implement
int RandomChoice4::doQuery() {
    return -1;
}

void RandomChoice4::loadParams(const evfl::QueryArg& arg) {}

void RandomChoice4::loadParams() {}

}  // namespace uking::query
