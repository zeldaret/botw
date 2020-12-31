#include "Game/AI/AI/aiDungeonCannonBallAutoDelete.h"

namespace uking::ai {

DungeonCannonBallAutoDelete::DungeonCannonBallAutoDelete(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

DungeonCannonBallAutoDelete::~DungeonCannonBallAutoDelete() = default;

bool DungeonCannonBallAutoDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonCannonBallAutoDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonCannonBallAutoDelete::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonCannonBallAutoDelete::loadParams_() {
    getStaticParam(&mTriggerVelocityKeepTime_s, "TriggerVelocityKeepTime");
    getStaticParam(&mTriggerVelocity_s, "TriggerVelocity");
}

}  // namespace uking::ai
