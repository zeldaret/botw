#include "Game/AI/Action/actionCarried.h"

namespace uking::action {

Carried::Carried(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Carried::~Carried() = default;

bool Carried::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Carried::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Carried::leave_() {
    ksys::act::ai::Action::leave_();
}

void Carried::loadParams_() {
    getStaticParam(&mBindType_s, "BindType");
    getStaticParam(&mFailDistance_s, "FailDistance");
    getStaticParam(&mIsCreateItem_s, "IsCreateItem");
    getStaticParam(&mIsRecoverCharCtrlAxis_s, "IsRecoverCharCtrlAxis");
    getStaticParam(&mIsUseConstraint_s, "IsUseConstraint");
    getStaticParam(&mIsOnBaseLink_s, "IsOnBaseLink");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mHoldOnXLinkKey_s, "HoldOnXLinkKey");
}

void Carried::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
