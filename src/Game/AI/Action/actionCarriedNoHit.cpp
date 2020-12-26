#include "Game/AI/Action/actionCarriedNoHit.h"

namespace uking::action {

CarriedNoHit::CarriedNoHit(const InitArg& arg) : Carried(arg) {}

CarriedNoHit::~CarriedNoHit() = default;

bool CarriedNoHit::init_(sead::Heap* heap) {
    return Carried::init_(heap);
}

void CarriedNoHit::enter_(ksys::act::ai::InlineParamPack* params) {
    Carried::enter_(params);
}

void CarriedNoHit::leave_() {
    Carried::leave_();
}

void CarriedNoHit::loadParams_() {
    getStaticParam(&mBindType_s, "BindType");
    getStaticParam(&mFailDistance_s, "FailDistance");
    getStaticParam(&mIsCreateItem_s, "IsCreateItem");
    getStaticParam(&mIsRecoverCharCtrlAxis_s, "IsRecoverCharCtrlAxis");
    getStaticParam(&mIsUseConstraint_s, "IsUseConstraint");
    getStaticParam(&mIsOnBaseLink_s, "IsOnBaseLink");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mHoldOnXLinkKey_s, "HoldOnXLinkKey");
}

void CarriedNoHit::calc_() {
    Carried::calc_();
}

}  // namespace uking::action
