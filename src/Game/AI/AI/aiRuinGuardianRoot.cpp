#include "Game/AI/AI/aiRuinGuardianRoot.h"

namespace uking::ai {

RuinGuardianRoot::RuinGuardianRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RuinGuardianRoot::~RuinGuardianRoot() = default;

bool RuinGuardianRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RuinGuardianRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RuinGuardianRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RuinGuardianRoot::loadParams_() {
    getStaticParam(&mSweepFrame_s, "SweepFrame");
    getStaticParam(&mDropThreshold_s, "DropThreshold");
}

}  // namespace uking::ai
