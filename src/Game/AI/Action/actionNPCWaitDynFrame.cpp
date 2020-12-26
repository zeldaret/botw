#include "Game/AI/Action/actionNPCWaitDynFrame.h"

namespace uking::action {

NPCWaitDynFrame::NPCWaitDynFrame(const InitArg& arg) : NPCWaitFrame(arg) {}

NPCWaitDynFrame::~NPCWaitDynFrame() = default;

bool NPCWaitDynFrame::init_(sead::Heap* heap) {
    return NPCWaitFrame::init_(heap);
}

void NPCWaitDynFrame::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCWaitFrame::enter_(params);
}

void NPCWaitDynFrame::leave_() {
    NPCWaitFrame::leave_();
}

void NPCWaitDynFrame::loadParams_() {
    NPCWaitFrame::loadParams_();
    getDynamicParam(&mDynWaitFrame_d, "DynWaitFrame");
    getDynamicParam(&mDynASName_d, "DynASName");
}

void NPCWaitDynFrame::calc_() {
    NPCWaitFrame::calc_();
}

}  // namespace uking::action
