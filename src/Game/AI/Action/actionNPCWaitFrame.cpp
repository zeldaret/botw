#include "Game/AI/Action/actionNPCWaitFrame.h"

namespace uking::action {

NPCWaitFrame::NPCWaitFrame(const InitArg& arg) : NPCWait(arg) {}

NPCWaitFrame::~NPCWaitFrame() = default;

bool NPCWaitFrame::init_(sead::Heap* heap) {
    return NPCWait::init_(heap);
}

void NPCWaitFrame::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCWait::enter_(params);
}

void NPCWaitFrame::leave_() {
    NPCWait::leave_();
}

void NPCWaitFrame::loadParams_() {
    NPCWait::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
}

void NPCWaitFrame::calc_() {
    NPCWait::calc_();
}

}  // namespace uking::action
