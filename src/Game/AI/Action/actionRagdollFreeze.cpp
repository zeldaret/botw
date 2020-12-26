#include "Game/AI/Action/actionRagdollFreeze.h"

namespace uking::action {

RagdollFreeze::RagdollFreeze(const InitArg& arg) : Freeze(arg) {}

RagdollFreeze::~RagdollFreeze() = default;

bool RagdollFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void RagdollFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
}

void RagdollFreeze::leave_() {
    Freeze::leave_();
}

void RagdollFreeze::loadParams_() {
    Freeze::loadParams_();
    getStaticParam(&mDownFrontCtrlOffset_s, "DownFrontCtrlOffset");
    getStaticParam(&mDownBackCtrlOffset_s, "DownBackCtrlOffset");
}

void RagdollFreeze::calc_() {
    Freeze::calc_();
}

}  // namespace uking::action
