#include "Game/AI/Action/actionHorseSaddleBindAction.h"

namespace uking::action {

HorseSaddleBindAction::HorseSaddleBindAction(const InitArg& arg) : HorseSaddleDefaultAction(arg) {}

HorseSaddleBindAction::~HorseSaddleBindAction() = default;

bool HorseSaddleBindAction::init_(sead::Heap* heap) {
    return HorseSaddleDefaultAction::init_(heap);
}

void HorseSaddleBindAction::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseSaddleDefaultAction::enter_(params);
}

void HorseSaddleBindAction::leave_() {
    HorseSaddleDefaultAction::leave_();
}

void HorseSaddleBindAction::loadParams_() {
    HorseSaddleDefaultAction::loadParams_();
    getDynamicParam(&mIsLeftBind_d, "IsLeftBind");
    getDynamicParam(&mIsRightBind_d, "IsRightBind");
    getDynamicParam(&mIsZelda_d, "IsZelda");
    getDynamicParam(&mRider_d, "Rider");
    getDynamicParam(&mHorse_d, "Horse");
}

void HorseSaddleBindAction::calc_() {
    HorseSaddleDefaultAction::calc_();
}

}  // namespace uking::action
