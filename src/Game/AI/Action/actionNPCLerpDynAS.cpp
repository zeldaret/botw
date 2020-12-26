#include "Game/AI/Action/actionNPCLerpDynAS.h"

namespace uking::action {

NPCLerpDynAS::NPCLerpDynAS(const InitArg& arg) : NPCLerpAction(arg) {}

NPCLerpDynAS::~NPCLerpDynAS() = default;

bool NPCLerpDynAS::init_(sead::Heap* heap) {
    return NPCLerpAction::init_(heap);
}

void NPCLerpDynAS::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCLerpAction::enter_(params);
}

void NPCLerpDynAS::leave_() {
    NPCLerpAction::leave_();
}

void NPCLerpDynAS::loadParams_() {
    NPCLerpAction::loadParams_();
    getDynamicParam(&mDynASName_d, "DynASName");
}

void NPCLerpDynAS::calc_() {
    NPCLerpAction::calc_();
}

}  // namespace uking::action
