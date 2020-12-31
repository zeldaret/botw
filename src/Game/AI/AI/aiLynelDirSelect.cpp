#include "Game/AI/AI/aiLynelDirSelect.h"

namespace uking::ai {

LynelDirSelect::LynelDirSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelDirSelect::~LynelDirSelect() = default;

bool LynelDirSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelDirSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelDirSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelDirSelect::loadParams_() {
    getStaticParam(&mBasePosOffsetFront_s, "BasePosOffsetFront");
    getStaticParam(&mBasePosOffsetBack_s, "BasePosOffsetBack");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mBackAngle_s, "BackAngle");
    getStaticParam(&mIsCheckOnlyXZ_s, "IsCheckOnlyXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
