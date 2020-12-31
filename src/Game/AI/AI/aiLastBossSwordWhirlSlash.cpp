#include "Game/AI/AI/aiLastBossSwordWhirlSlash.h"

namespace uking::ai {

LastBossSwordWhirlSlash::LastBossSwordWhirlSlash(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossSwordWhirlSlash::~LastBossSwordWhirlSlash() = default;

bool LastBossSwordWhirlSlash::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossSwordWhirlSlash::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossSwordWhirlSlash::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossSwordWhirlSlash::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIsNoCharge_d, "IsNoCharge");
}

}  // namespace uking::ai
