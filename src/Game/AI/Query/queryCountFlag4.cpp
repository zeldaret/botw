#include "Game/AI/Query/queryCountFlag4.h"
#include <evfl/Query.h>

namespace uking::query {

CountFlag4::CountFlag4(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CountFlag4::~CountFlag4() = default;

// FIXME: implement
int CountFlag4::doQuery() {
    return -1;
}

void CountFlag4::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "GameDataFlagNo0");
    loadString(arg.param_accessor, "GameDataFlagNo1");
    loadString(arg.param_accessor, "GameDataFlagNo2");
    loadString(arg.param_accessor, "GameDataFlagNo3");
    loadString(arg.param_accessor, "GameDataFlagNo4");
}

void CountFlag4::loadParams() {
    getDynamicParam(&mGameDataFlagNo0, "GameDataFlagNo0");
    getDynamicParam(&mGameDataFlagNo1, "GameDataFlagNo1");
    getDynamicParam(&mGameDataFlagNo2, "GameDataFlagNo2");
    getDynamicParam(&mGameDataFlagNo3, "GameDataFlagNo3");
    getDynamicParam(&mGameDataFlagNo4, "GameDataFlagNo4");
}

}  // namespace uking::query
