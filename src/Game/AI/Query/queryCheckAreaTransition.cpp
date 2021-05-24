#include "Game/AI/Query/queryCheckAreaTransition.h"
#include <evfl/Query.h>

namespace uking::query {

CheckAreaTransition::CheckAreaTransition(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckAreaTransition::~CheckAreaTransition() = default;

// FIXME: implement
int CheckAreaTransition::doQuery() {
    return -1;
}

void CheckAreaTransition::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CurrentAreaNo");
    loadInt(arg.param_accessor, "PostAreaNo");
}

void CheckAreaTransition::loadParams() {
    getStaticParam(&mCheckDistFront, "CheckDistFront");
    getDynamicParam(&mCurrentAreaNo, "CurrentAreaNo");
    getDynamicParam(&mPostAreaNo, "PostAreaNo");
}

}  // namespace uking::query
