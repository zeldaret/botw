#include "Game/AI/AI/aiAddCarriedBase.h"

namespace uking::ai {

AddCarriedBase::AddCarriedBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddCarriedBase::~AddCarriedBase() = default;

bool AddCarriedBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddCarriedBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AddCarriedBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddCarriedBase::loadParams_() {
    getStaticParam(&mFailDistance_s, "FailDistance");
    getStaticParam(&mIsRecoverCharCtrlAxis_s, "IsRecoverCharCtrlAxis");
    getStaticParam(&mIsUseConstraint_s, "IsUseConstraint");
    getStaticParam(&mHoldOnXLinkKey_s, "HoldOnXLinkKey");
}

}  // namespace uking::ai
