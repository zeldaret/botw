#include "Game/AI/Action/actionSetCookItemInDemo.h"
#include "Game/Cooking/cookManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"

namespace uking::action {

SetCookItemInDemo::SetCookItemInDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetCookItemInDemo::~SetCookItemInDemo() = default;

bool SetCookItemInDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SetCookItemInDemo::oneShot_() {
    CookItem cook_item{};

    CookingMgr::BoostArg boost_arg{};

    s32 adjusted_set_num = sead::Mathi::clampMin(*mSetNum_d, 1);

    bool result = CookingMgr::instance()->cookWithItems(mPorchItemName01_d, mPorchItemName02_d,
                                                        mPorchItemName03_d, mPorchItemName04_d,
                                                        mPorchItemName05_d, cook_item, boost_arg);

    if (!ui::PauseMenuDataMgr::instance() || !result)
        return false;

    for (int i = 0; i < adjusted_set_num; i++) {
        ui::PauseMenuDataMgr::instance()->cookItemGet(cook_item);
    }

    return true;
}

void SetCookItemInDemo::loadParams_() {
    getDynamicParam(&mSetNum_d, "SetNum");
    getDynamicParam(&mPorchItemName01_d, "PorchItemName01");
    getDynamicParam(&mPorchItemName02_d, "PorchItemName02");
    getDynamicParam(&mPorchItemName03_d, "PorchItemName03");
    getDynamicParam(&mPorchItemName04_d, "PorchItemName04");
    getDynamicParam(&mPorchItemName05_d, "PorchItemName05");
}

}  // namespace uking::action
