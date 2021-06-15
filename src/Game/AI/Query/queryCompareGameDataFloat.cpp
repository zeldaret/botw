#include "Game/AI/Query/queryCompareGameDataFloat.h"
#include <evfl/Query.h>
#include <functional>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CompareGameDataFloat::CompareGameDataFloat(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CompareGameDataFloat::~CompareGameDataFloat() = default;

int CompareGameDataFloat::doQuery() {
    float flag_value_a = 0.0;
    float flag_value_b = 0.0;

    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt)
        return 0;
    if (!gdt->getParamBypassPerm().get().getF32(&flag_value_a, mGameDataFloatName_A))
        return 0;
    if (!gdt->getParamBypassPerm().get().getF32(&flag_value_b, mGameDataFloatName_B))
        return 0;

    const auto invert = std::logical_not<>();

    sead::FixedSafeString<32> op = mOperator;
    if (op == "Equal")
        return invert(flag_value_a == flag_value_b);
    if (op == "NotEqual")
        return invert(flag_value_a != flag_value_b);
    if (op == "GreaterThan")
        return invert(flag_value_a > flag_value_b);
    if (op == "GreaterThanOrEqualTo")
        return invert(flag_value_a >= flag_value_b);
    if (op == "LessThan")
        return invert(flag_value_a < flag_value_b);
    if (op == "LessThanOrEqualTo")
        return invert(flag_value_a <= flag_value_b);

    return 0;
}

void CompareGameDataFloat::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "GameDataFloatName_A");
    loadString(arg.param_accessor, "Operator");
    loadString(arg.param_accessor, "GameDataFloatName_B");
}

void CompareGameDataFloat::loadParams() {
    getDynamicParam(&mGameDataFloatName_A, "GameDataFloatName_A");
    getDynamicParam(&mOperator, "Operator");
    getDynamicParam(&mGameDataFloatName_B, "GameDataFloatName_B");
}

}  // namespace uking::query
