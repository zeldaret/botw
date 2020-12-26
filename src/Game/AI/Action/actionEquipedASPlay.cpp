#include "Game/AI/Action/actionEquipedASPlay.h"

namespace uking::action {

EquipedASPlay::EquipedASPlay(const InitArg& arg) : EquipedAction(arg) {}

EquipedASPlay::~EquipedASPlay() = default;

bool EquipedASPlay::init_(sead::Heap* heap) {
    return EquipedAction::init_(heap);
}

void EquipedASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
}

void EquipedASPlay::leave_() {
    EquipedAction::leave_();
}

void EquipedASPlay::loadParams_() {
    EquipedAction::loadParams_();
    getStaticParam(&mAS_s, "AS");
}

void EquipedASPlay::calc_() {
    EquipedAction::calc_();
}

}  // namespace uking::action
