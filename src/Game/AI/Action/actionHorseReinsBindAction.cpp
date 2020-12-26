#include "Game/AI/Action/actionHorseReinsBindAction.h"

namespace uking::action {

HorseReinsBindAction::HorseReinsBindAction(const InitArg& arg) : HorseReinsDefaultAction(arg) {}

HorseReinsBindAction::~HorseReinsBindAction() = default;

bool HorseReinsBindAction::init_(sead::Heap* heap) {
    return HorseReinsDefaultAction::init_(heap);
}

void HorseReinsBindAction::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseReinsDefaultAction::enter_(params);
}

void HorseReinsBindAction::leave_() {
    HorseReinsDefaultAction::leave_();
}

void HorseReinsBindAction::loadParams_() {
    HorseReinsDefaultAction::loadParams_();
    getDynamicParam(&mIsLeftBind_d, "IsLeftBind");
    getDynamicParam(&mIsRightBind_d, "IsRightBind");
    getDynamicParam(&mRider_d, "Rider");
    getDynamicParam(&mHorse_d, "Horse");
}

void HorseReinsBindAction::calc_() {
    HorseReinsDefaultAction::calc_();
}

}  // namespace uking::action
