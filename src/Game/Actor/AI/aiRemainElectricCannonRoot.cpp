#include "Game/Actor/AI/aiRemainElectricCannonRoot.h"

namespace uking::ai {

RemainElectricCannonRoot::RemainElectricCannonRoot(const InitArg& arg) : LargeCannonRoot(arg) {}

RemainElectricCannonRoot::~RemainElectricCannonRoot() = default;

bool RemainElectricCannonRoot::init_(sead::Heap* heap) {
    return LargeCannonRoot::init_(heap);
}

void RemainElectricCannonRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    LargeCannonRoot::enter_(params);
}

void RemainElectricCannonRoot::leave_() {
    LargeCannonRoot::leave_();
}

void RemainElectricCannonRoot::loadParams_() {
    LargeCannonRoot::loadParams_();
    getStaticParam(&mSearchMaxDistLoiter_s, "SearchMaxDistLoiter");
}

}  // namespace uking::ai
