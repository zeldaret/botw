#include "Game/AI/Action/actionOwnedHorseObserveAction.h"

namespace uking::action {

OwnedHorseObserveAction::OwnedHorseObserveAction(const InitArg& arg) : AreaTagAction(arg) {}

OwnedHorseObserveAction::~OwnedHorseObserveAction() = default;

bool OwnedHorseObserveAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void OwnedHorseObserveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void OwnedHorseObserveAction::loadParams_() {
    getMapUnitParam(&mSaveFlag_m, "SaveFlag");
}

void OwnedHorseObserveAction::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
