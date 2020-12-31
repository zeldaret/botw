#include "Game/AI/AI/aiRemainElectricCannonRoot.h"

namespace uking::ai {

RemainElectricCannonRoot::RemainElectricCannonRoot(const InitArg& arg)
    : RemainElectricCannonRootBase(arg) {}

RemainElectricCannonRoot::~RemainElectricCannonRoot() = default;

bool RemainElectricCannonRoot::init_(sead::Heap* heap) {
    return RemainElectricCannonRootBase::init_(heap);
}

void RemainElectricCannonRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainElectricCannonRootBase::enter_(params);
}

void RemainElectricCannonRoot::leave_() {
    RemainElectricCannonRootBase::leave_();
}

void RemainElectricCannonRoot::loadParams_() {
    RemainElectricCannonRootBase::loadParams_();
    getStaticParam(&mSearchMaxDistLoiter_s, "SearchMaxDistLoiter");
}

}  // namespace uking::ai
