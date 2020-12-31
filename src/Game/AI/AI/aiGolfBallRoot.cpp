#include "Game/AI/AI/aiGolfBallRoot.h"

namespace uking::ai {

GolfBallRoot::GolfBallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolfBallRoot::~GolfBallRoot() = default;

bool GolfBallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolfBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolfBallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolfBallRoot::loadParams_() {
    getStaticParam(&mIntSmashJudgeFrame_s, "IntSmashJudgeFrame");
    getStaticParam(&mIntSmashContinueFrame_s, "IntSmashContinueFrame");
    getStaticParam(&mFloatJudgeSmash_s, "FloatJudgeSmash");
    getStaticParam(&mFloatJudgeStop_s, "FloatJudgeStop");
}

}  // namespace uking::ai
