#include "Game/AI/Action/actionGiveCookResultForNpc.h"

namespace uking::action {

GiveCookResultForNpc::GiveCookResultForNpc(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GiveCookResultForNpc::~GiveCookResultForNpc() = default;

bool GiveCookResultForNpc::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GiveCookResultForNpc::loadParams_() {
    getDynamicParam(&mCount_d, "Count");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
    getDynamicParam(&mCookEffectType_d, "CookEffectType");
}

}  // namespace uking::action
