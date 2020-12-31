#include "Game/AI/AI/aiCircleMovePos.h"

namespace uking::ai {

CircleMovePos::CircleMovePos(const InitArg& arg) : CircleMove(arg) {}

CircleMovePos::~CircleMovePos() = default;

bool CircleMovePos::init_(sead::Heap* heap) {
    return CircleMove::init_(heap);
}

void CircleMovePos::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMove::enter_(params);
}

void CircleMovePos::leave_() {
    CircleMove::leave_();
}

void CircleMovePos::loadParams_() {
    CircleMove::loadParams_();
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

}  // namespace uking::ai
