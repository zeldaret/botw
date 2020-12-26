#include "Game/AI/Action/actionHideBarrelCarried.h"

namespace uking::action {

HideBarrelCarried::HideBarrelCarried(const InitArg& arg) : Carried(arg) {}

HideBarrelCarried::~HideBarrelCarried() = default;

bool HideBarrelCarried::init_(sead::Heap* heap) {
    return Carried::init_(heap);
}

void HideBarrelCarried::enter_(ksys::act::ai::InlineParamPack* params) {
    Carried::enter_(params);
}

void HideBarrelCarried::leave_() {
    Carried::leave_();
}

void HideBarrelCarried::loadParams_() {
    Carried::loadParams_();
    getStaticParam(&mCutLength_s, "CutLength");
}

void HideBarrelCarried::calc_() {
    Carried::calc_();
}

}  // namespace uking::action
