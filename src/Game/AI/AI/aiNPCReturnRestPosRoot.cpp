#include "Game/AI/AI/aiNPCReturnRestPosRoot.h"

namespace uking::ai {

NPCReturnRestPosRoot::NPCReturnRestPosRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCReturnRestPosRoot::~NPCReturnRestPosRoot() = default;

bool NPCReturnRestPosRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCReturnRestPosRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCReturnRestPosRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCReturnRestPosRoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
