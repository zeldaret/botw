#include "Game/AI/Query/queryRandomChoiceExceptOnFlag.h"
#include <evfl/Query.h>
#include <prim/seadBitFlag.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

RandomChoiceExceptOnFlag::RandomChoiceExceptOnFlag(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

RandomChoiceExceptOnFlag::~RandomChoiceExceptOnFlag() = default;

static bool isFlagForbidden(const sead::SafeString& flag) {
    bool value = false;
    if (flag.isEmpty())
        return true;
    if (!ksys::gdt::Manager::instance()->getParamBypassPerm().get().getBool(&value, flag))
        return true;
    return value;
}

// TODO: stack issues for the booleans in isFlagForbidden
int RandomChoiceExceptOnFlag::doQuery() {
    using Manager = ksys::gdt::Manager;
    if (!Manager::instance())
        return 10;

    sead::BitFlag16 forbidden_values;
#define CHECK_FLAG_(BIT) forbidden_values.changeBit(BIT, isFlagForbidden(mCheckFlag##BIT));
    CHECK_FLAG_(0)
    CHECK_FLAG_(1)
    CHECK_FLAG_(2)
    CHECK_FLAG_(3)
    CHECK_FLAG_(4)
    CHECK_FLAG_(5)
    CHECK_FLAG_(6)
    CHECK_FLAG_(7)
    CHECK_FLAG_(8)
    CHECK_FLAG_(9)
#undef CHECK_FLAG_

    const auto num_allowed_values = 10 - forbidden_values.countOnBit();
    if (num_allowed_values == 0)
        return 10;

    s32 count = sead::GlobalRandom::instance()->getU32(num_allowed_values) + 1;
    for (s32 i = 0; i < 10; ++i) {
        if (forbidden_values.isOffBit(i)) {
            if (count < 2)
                return i;
            --count;
        }
    }
    return 10;
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
