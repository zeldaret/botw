#include "Game/AI/Query/queryRandomChoice2.h"
#include <evfl/Query.h>
#include <random/seadGlobalRandom.h>

namespace uking::query {

RandomChoice2::RandomChoice2(const InitArg& arg) : ksys::act::ai::Query(arg) {}

RandomChoice2::~RandomChoice2() = default;

int RandomChoice2::doQuery() {
    return sead::GlobalRandom::instance()->getU32(2);
}

}  // namespace uking::query
