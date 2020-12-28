#include "Game/AI/Action/actionNPCWaitDynAS.h"

namespace uking::action {

NPCWaitDynAS::NPCWaitDynAS(const InitArg& arg) : NPCWait(arg) {}

NPCWaitDynAS::~NPCWaitDynAS() = default;

void NPCWaitDynAS::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCWait::enter_(params);
}

void NPCWaitDynAS::loadParams_() {
    NPCWait::loadParams_();
    getDynamicParam(&mDynASName_d, "DynASName");
}

}  // namespace uking::action
