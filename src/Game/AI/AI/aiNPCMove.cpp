#include "Game/AI/AI/aiNPCMove.h"

namespace uking::ai {

NPCMove::NPCMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCMove::~NPCMove() = default;

bool NPCMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCMove::loadParams_() {
    getStaticParam(&mTerritoryRange_s, "TerritoryRange");
    getStaticParam(&mDestination_s, "Destination");
    getStaticParam(&mMoveEndASName_s, "MoveEndASName");
}

}  // namespace uking::ai
