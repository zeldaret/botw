#include "Game/AI/AI/aiBossBattleRoomRoot.h"

namespace uking::ai {

BossBattleRoomRoot::BossBattleRoomRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BossBattleRoomRoot::~BossBattleRoomRoot() = default;

bool BossBattleRoomRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BossBattleRoomRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BossBattleRoomRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BossBattleRoomRoot::loadParams_() {
    getStaticParam(&mFramesRollKeepSecond_s, "FramesRollKeepSecond");
    getStaticParam(&mNumTimesRoll_s, "NumTimesRoll");
    getStaticParam(&mTitleAngle_s, "TitleAngle");
    getStaticParam(&mRollAngle_s, "RollAngle");
    getStaticParam(&mFramesRotate_s, "FramesRotate");
    getStaticParam(&mFramesReset_s, "FramesReset");
    getStaticParam(&mFramesRoll_s, "FramesRoll");
    getStaticParam(&mFramesDelayRoll_s, "FramesDelayRoll");
    getStaticParam(&mFramesRollKeepFirst_s, "FramesRollKeepFirst");
}

}  // namespace uking::ai
