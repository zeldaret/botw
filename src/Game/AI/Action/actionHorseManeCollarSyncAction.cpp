#include "Game/AI/Action/actionHorseManeCollarSyncAction.h"

namespace uking::action {

HorseManeCollarSyncAction::HorseManeCollarSyncAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

HorseManeCollarSyncAction::~HorseManeCollarSyncAction() = default;

bool HorseManeCollarSyncAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseManeCollarSyncAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseManeCollarSyncAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseManeCollarSyncAction::loadParams_() {}

void HorseManeCollarSyncAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
