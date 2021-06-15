#include "Game/AI/Query/queryRandomChoice4.h"
#include <evfl/Query.h>
#include <random/seadGlobalRandom.h>

namespace uking::query {

RandomChoice4::RandomChoice4(const InitArg& arg) : ksys::act::ai::Query(arg) {}

RandomChoice4::~RandomChoice4() = default;

int RandomChoice4::doQuery() {
    return sead::GlobalRandom::instance()->getU32(4);
}

}  // namespace uking::query
