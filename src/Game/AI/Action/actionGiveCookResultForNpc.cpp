#include "Game/AI/Action/actionGiveCookResultForNpc.h"

namespace uking::action {

GiveCookResultForNpc::GiveCookResultForNpc(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GiveCookResultForNpc::~GiveCookResultForNpc() = default;

bool GiveCookResultForNpc::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GiveCookResultForNpc::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GiveCookResultForNpc::leave_() {
    ksys::act::ai::Action::leave_();
}

void GiveCookResultForNpc::loadParams_() {
    getDynamicParam(&mCount_d, "Count");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
    getDynamicParam(&mCookEffectType_d, "CookEffectType");
}

void GiveCookResultForNpc::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
