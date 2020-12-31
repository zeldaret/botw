#include "Game/AI/AI/aiSwitchRightAndWrong.h"

namespace uking::ai {

SwitchRightAndWrong::SwitchRightAndWrong(const InitArg& arg) : SwitchAI(arg) {}

SwitchRightAndWrong::~SwitchRightAndWrong() = default;

bool SwitchRightAndWrong::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchRightAndWrong::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
}

void SwitchRightAndWrong::leave_() {
    SwitchAI::leave_();
}

void SwitchRightAndWrong::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mWaitTime_s, "WaitTime");
}

}  // namespace uking::ai
