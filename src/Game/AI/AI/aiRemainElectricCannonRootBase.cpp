#include "Game/AI/AI/aiRemainElectricCannonRootBase.h"

namespace uking::ai {

RemainElectricCannonRootBase::RemainElectricCannonRootBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

bool RemainElectricCannonRootBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainElectricCannonRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainElectricCannonRootBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainElectricCannonRootBase::loadParams_() {
    getStaticParam(&mSearchMaxDist_s, "SearchMaxDist");
    getStaticParam(&mSearchMinDist_s, "SearchMinDist");
    getStaticParam(&mSearchDistMargin_s, "SearchDistMargin");
}

}  // namespace uking::ai
