#include "Game/AI/Query/queryCompareGameDataInt.h"
#include <evfl/Query.h>
#include <functional>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CompareGameDataInt::CompareGameDataInt(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CompareGameDataInt::~CompareGameDataInt() = default;

int CompareGameDataInt::doQuery() {
    int flag_value_a = 0;
    int flag_value_b = 0;

    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt)
        return 0;
    if (!gdt->getParamBypassPerm().get().getS32(&flag_value_a, mGameDataIntName_A))
        return 0;
    if (!gdt->getParamBypassPerm().get().getS32(&flag_value_b, mGameDataIntName_B))
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

void CompareGameDataInt::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "GameDataIntName_A");
    loadString(arg.param_accessor, "Operator");
    loadString(arg.param_accessor, "GameDataIntName_B");
}

void CompareGameDataInt::loadParams() {
    getDynamicParam(&mGameDataIntName_A, "GameDataIntName_A");
    getDynamicParam(&mOperator, "Operator");
    getDynamicParam(&mGameDataIntName_B, "GameDataIntName_B");
}

}  // namespace uking::query
