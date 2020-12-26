#include "Game/AI/Action/actionNPCTargetMoveDynAs.h"

namespace uking::action {

NPCTargetMoveDynAs::NPCTargetMoveDynAs(const InitArg& arg) : NPCTargetMove(arg) {}

NPCTargetMoveDynAs::~NPCTargetMoveDynAs() = default;

bool NPCTargetMoveDynAs::init_(sead::Heap* heap) {
    return NPCTargetMove::init_(heap);
}

void NPCTargetMoveDynAs::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCTargetMove::enter_(params);
}

void NPCTargetMoveDynAs::leave_() {
    NPCTargetMove::leave_();
}

void NPCTargetMoveDynAs::loadParams_() {
    NPCTargetMove::loadParams_();
    getDynamicParam(&mDynASKeyName_d, "DynASKeyName");
}

void NPCTargetMoveDynAs::calc_() {
    NPCTargetMove::calc_();
}

}  // namespace uking::action
