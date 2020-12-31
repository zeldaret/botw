#include "Game/AI/AI/aiSwarmEscapeDie.h"

namespace uking::ai {

SwarmEscapeDie::SwarmEscapeDie(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmEscapeDie::~SwarmEscapeDie() = default;

bool SwarmEscapeDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwarmEscapeDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwarmEscapeDie::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwarmEscapeDie::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mRiseHeight_s, "RiseHeight");
    getStaticParam(&mRiseDist_s, "RiseDist");
    getStaticParam(&mEndDist_s, "EndDist");
}

}  // namespace uking::ai
