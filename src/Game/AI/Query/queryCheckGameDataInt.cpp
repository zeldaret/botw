#include "Game/AI/Query/queryCheckGameDataInt.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckGameDataInt::CheckGameDataInt(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckGameDataInt::~CheckGameDataInt() = default;

int CheckGameDataInt::doQuery() {
    int flag_value = 0;
    const auto value = *mValue;

    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt || !gdt->getParamBypassPerm().get().getS32(&flag_value, mGameDataIntName))
        return 0;

    sead::FixedSafeString<32> op = mOperator;
    if (op == "Equal")
        return value == flag_value;
    if (op == "NotEqual")
        return value != flag_value;
    if (op == "GreaterThan")
        return value < flag_value;
    if (op == "GreaterThanOrEqualTo")
        return value <= flag_value;
    if (op == "LessThan")
        return value > flag_value;
    if (op == "LessThanOrEqualTo")
        return value >= flag_value;

    return 0;
}

void CheckGameDataInt::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Value");
    loadString(arg.param_accessor, "GameDataIntName");
    loadString(arg.param_accessor, "Operator");
}

void CheckGameDataInt::loadParams() {
    getDynamicParam(&mValue, "Value");
    getDynamicParam(&mGameDataIntName, "GameDataIntName");
    getDynamicParam(&mOperator, "Operator");
}

}  // namespace uking::query
