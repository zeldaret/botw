#include "Game/Actor/AI/aiSimpleBeamExplode.h"

namespace uking::ai {

SimpleBeamExplode::SimpleBeamExplode(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleBeamExplode::~SimpleBeamExplode() = default;

bool SimpleBeamExplode::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleBeamExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SimpleBeamExplode::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleBeamExplode::loadParams_() {
    getStaticParam(&mMaxDistance_s, "MaxDistance");
    getStaticParam(&mIsDelete_s, "IsDelete");
}

}  // namespace uking::ai
