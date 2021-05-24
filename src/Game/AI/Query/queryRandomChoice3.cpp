#include "Game/AI/Query/queryRandomChoice3.h"
#include <evfl/Query.h>
#include <random/seadGlobalRandom.h>

namespace uking::query {

RandomChoice3::RandomChoice3(const InitArg& arg) : ksys::act::ai::Query(arg) {}

RandomChoice3::~RandomChoice3() = default;

int RandomChoice3::doQuery() {
    return sead::GlobalRandom::instance()->getU32(3);
}

void RandomChoice3::loadParams(const evfl::QueryArg& arg) {}

void RandomChoice3::loadParams() {}

}  // namespace uking::query
