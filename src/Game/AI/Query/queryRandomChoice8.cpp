#include "Game/AI/Query/queryRandomChoice8.h"
#include <evfl/query.h>

namespace uking::query {

RandomChoice8::RandomChoice8(const InitArg& arg) : ksys::act::ai::Query(arg) {}

RandomChoice8::~RandomChoice8() = default;

// FIXME: implement
int RandomChoice8::doQuery() {
    return -1;
}

void RandomChoice8::loadParams(const evfl::QueryArg& arg) {}

void RandomChoice8::loadParams() {}

}  // namespace uking::query
