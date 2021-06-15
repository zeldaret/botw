#include "Game/AI/Query/queryCheckGameDataFloat.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckGameDataFloat::CheckGameDataFloat(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckGameDataFloat::~CheckGameDataFloat() = default;

int CheckGameDataFloat::doQuery() {
    float flag_value = 0.0;
    const auto value = *mValue;

    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt || !gdt->getParamBypassPerm().get().getF32(&flag_value, mGameDataFloatName))
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

void CheckGameDataFloat::loadParams(const evfl::QueryArg& arg) {
    loadFloat(arg.param_accessor, "Value");
    loadString(arg.param_accessor, "GameDataFloatName");
    loadString(arg.param_accessor, "Operator");
}

void CheckGameDataFloat::loadParams() {
    getDynamicParam(&mValue, "Value");
    getDynamicParam(&mGameDataFloatName, "GameDataFloatName");
    getDynamicParam(&mOperator, "Operator");
}

}  // namespace uking::query
