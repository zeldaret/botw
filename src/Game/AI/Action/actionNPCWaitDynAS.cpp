#include "Game/AI/Action/actionNPCWaitDynAS.h"

namespace uking::action {

NPCWaitDynAS::NPCWaitDynAS(const InitArg& arg) : NPCWait(arg) {}

NPCWaitDynAS::~NPCWaitDynAS() = default;

bool NPCWaitDynAS::init_(sead::Heap* heap) {
    return NPCWait::init_(heap);
}

void NPCWaitDynAS::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCWait::enter_(params);
}

void NPCWaitDynAS::leave_() {
    NPCWait::leave_();
}

void NPCWaitDynAS::loadParams_() {
    NPCWait::loadParams_();
    getDynamicParam(&mDynASName_d, "DynASName");
}

void NPCWaitDynAS::calc_() {
    NPCWait::calc_();
}

}  // namespace uking::action
