#include "Game/AI/Query/queryRandomChoiceExceptOnFlag.h"
#include <evfl/query.h>

namespace uking::query {

RandomChoiceExceptOnFlag::RandomChoiceExceptOnFlag(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

RandomChoiceExceptOnFlag::~RandomChoiceExceptOnFlag() = default;

// FIXME: implement
int RandomChoiceExceptOnFlag::doQuery() {
    return -1;
}

void RandomChoiceExceptOnFlag::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "CheckFlag0");
    loadString(arg.param_accessor, "CheckFlag1");
    loadString(arg.param_accessor, "CheckFlag2");
    loadString(arg.param_accessor, "CheckFlag3");
    loadString(arg.param_accessor, "CheckFlag4");
    loadString(arg.param_accessor, "CheckFlag5");
    loadString(arg.param_accessor, "CheckFlag6");
    loadString(arg.param_accessor, "CheckFlag7");
    loadString(arg.param_accessor, "CheckFlag8");
    loadString(arg.param_accessor, "CheckFlag9");
}

void RandomChoiceExceptOnFlag::loadParams() {
    getDynamicParam(&mCheckFlag0, "CheckFlag0");
    getDynamicParam(&mCheckFlag1, "CheckFlag1");
    getDynamicParam(&mCheckFlag2, "CheckFlag2");
    getDynamicParam(&mCheckFlag3, "CheckFlag3");
    getDynamicParam(&mCheckFlag4, "CheckFlag4");
    getDynamicParam(&mCheckFlag5, "CheckFlag5");
    getDynamicParam(&mCheckFlag6, "CheckFlag6");
    getDynamicParam(&mCheckFlag7, "CheckFlag7");
    getDynamicParam(&mCheckFlag8, "CheckFlag8");
    getDynamicParam(&mCheckFlag9, "CheckFlag9");
}

}  // namespace uking::query
