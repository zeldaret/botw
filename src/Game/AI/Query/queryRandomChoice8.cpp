#include "Game/AI/Query/queryRandomChoice8.h"
#include <evfl/Query.h>
#include <random/seadGlobalRandom.h>

namespace uking::query {

RandomChoice8::RandomChoice8(const InitArg& arg) : ksys::act::ai::Query(arg) {}

RandomChoice8::~RandomChoice8() = default;

// FIXME: implement
int RandomChoice8::doQuery() {
    return sead::GlobalRandom::instance()->getU32(8);
}

}  // namespace uking::query
