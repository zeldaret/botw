#include "Game/AI/AI/aiRestreintTired.h"

namespace uking::ai {

RestreintTired::RestreintTired(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RestreintTired::~RestreintTired() = default;

bool RestreintTired::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RestreintTired::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RestreintTired::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RestreintTired::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mCentralPos_d, "CentralPos");
    getAITreeVariable(&mIsTryingReturnRestreint_a, "IsTryingReturnRestreint");
}

}  // namespace uking::ai
