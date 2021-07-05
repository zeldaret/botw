#include "Game/AI/Query/queryCountFlag4.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CountFlag4::CountFlag4(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CountFlag4::~CountFlag4() = default;

int CountFlag4::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm == nullptr)
        return 0;

    bool x = false;
    int result = 0;

    auto isOn = [&](const sead::SafeString& s) {
        return gdm->getParamBypassPerm().get().getBool(&x, s) && x;
    };

    if (!mGameDataFlagNo0.isEmpty())
        result += isOn(mGameDataFlagNo0);
    if (!mGameDataFlagNo1.isEmpty())
        result += isOn(mGameDataFlagNo1);
    if (!mGameDataFlagNo2.isEmpty())
        result += isOn(mGameDataFlagNo2);
    if (!mGameDataFlagNo3.isEmpty())
        result += isOn(mGameDataFlagNo3);
    if (!mGameDataFlagNo4.isEmpty())
        result += isOn(mGameDataFlagNo4);

    return result;
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
