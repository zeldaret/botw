#include "Game/AI/AI/aiAssassinMiddleAzitoNoMemberDemo.h"

namespace uking::ai {

AssassinMiddleAzitoNoMemberDemo::AssassinMiddleAzitoNoMemberDemo(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinMiddleAzitoNoMemberDemo::~AssassinMiddleAzitoNoMemberDemo() = default;

bool AssassinMiddleAzitoNoMemberDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AssassinMiddleAzitoNoMemberDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AssassinMiddleAzitoNoMemberDemo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinMiddleAzitoNoMemberDemo::loadParams_() {
    getStaticParam(&mDelayTimeMin_s, "DelayTimeMin");
    getStaticParam(&mDelayTimeMax_s, "DelayTimeMax");
}

}  // namespace uking::ai
