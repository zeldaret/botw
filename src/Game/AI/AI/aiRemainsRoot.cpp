#include "Game/AI/AI/aiRemainsRoot.h"

namespace uking::ai {

RemainsRoot::RemainsRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsRoot::~RemainsRoot() = default;

bool RemainsRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsRoot::loadParams_() {
    getStaticParam(&mRemainsTypeID_s, "RemainsTypeID");
    getStaticParam(&mIsAllowRotAxisX_s, "IsAllowRotAxisX");
}

}  // namespace uking::ai
