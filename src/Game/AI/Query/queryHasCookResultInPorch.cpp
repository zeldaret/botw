#include "Game/AI/Query/queryHasCookResultInPorch.h"
#include <evfl/Query.h>
#include "Game/UI/uiUtils.h"

namespace uking::query {

HasCookResultInPorch::HasCookResultInPorch(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasCookResultInPorch::~HasCookResultInPorch() = default;

int HasCookResultInPorch::doQuery() {
    s32 num;

    if (mCookEffectType == "AllOK")
        num = ui::countCookResultsAllOk(mPorchItemName);
    else
        num = ui::countCookResultsCheck(mPorchItemName, getEffect());

    if (num < *mCount)
        return 0;
    else if (num == *mCount)
        return 1;
    else if (num > *mCount)
        return 2;
    return 0;
}

int HasCookResultInPorch::getEffect() const {
    if (mCookEffectType == "None")
        return -1;
    if (mCookEffectType == "ResistHot")
        return 4;
    if (mCookEffectType == "ResistCold")
        return 5;
    if (mCookEffectType == "ResistElectric")
        return 6;
    if (mCookEffectType == "AttackUp")
        return 10;
    if (mCookEffectType == "DefenseUp")
        return 11;
    if (mCookEffectType == "Quietness")
        return 12;
    if (mCookEffectType == "AllSpeed")
        return 13;
    if (mCookEffectType == "Fireproof")
        return 16;
    if (mCookEffectType == "GutsRecover")
        return 14;
    if (mCookEffectType == "ExGutsMaxUp")
        return 15;
    if (mCookEffectType == "LifeMaxUp")
        return 2;
    return -1;
}

void HasCookResultInPorch::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
    loadString(arg.param_accessor, "PorchItemName");
    loadString(arg.param_accessor, "CookEffectType");
}

void HasCookResultInPorch::loadParams() {
    getDynamicParam(&mCount, "Count");
    getDynamicParam(&mPorchItemName, "PorchItemName");
    getDynamicParam(&mCookEffectType, "CookEffectType");
}

}  // namespace uking::query
