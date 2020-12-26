#include "Game/AI/Action/actionNpcRideWaitAction.h"

namespace uking::action {

NpcRideWaitAction::NpcRideWaitAction(const InitArg& arg) : NPCWaitAction(arg) {}

NpcRideWaitAction::~NpcRideWaitAction() = default;

bool NpcRideWaitAction::init_(sead::Heap* heap) {
    return NPCWaitAction::init_(heap);
}

void NpcRideWaitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCWaitAction::enter_(params);
}

void NpcRideWaitAction::leave_() {
    NPCWaitAction::leave_();
}

void NpcRideWaitAction::loadParams_() {
    NPCWaitAction::loadParams_();
    getDynamicParam(&mGearSpeed_d, "GearSpeed");
}

void NpcRideWaitAction::calc_() {
    NPCWaitAction::calc_();
}

}  // namespace uking::action
