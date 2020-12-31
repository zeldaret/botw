#include "Game/AI/AI/aiKeeseSwarmRoam.h"

namespace uking::ai {

KeeseSwarmRoam::KeeseSwarmRoam(const InitArg& arg) : CircleMove(arg) {}

KeeseSwarmRoam::~KeeseSwarmRoam() = default;

bool KeeseSwarmRoam::init_(sead::Heap* heap) {
    return CircleMove::init_(heap);
}

void KeeseSwarmRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMove::enter_(params);
}

void KeeseSwarmRoam::leave_() {
    CircleMove::leave_();
}

void KeeseSwarmRoam::loadParams_() {
    CircleMove::loadParams_();
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

}  // namespace uking::ai
