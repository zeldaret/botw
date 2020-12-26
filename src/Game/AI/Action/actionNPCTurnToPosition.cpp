#include "Game/AI/Action/actionNPCTurnToPosition.h"

namespace uking::action {

NPCTurnToPosition::NPCTurnToPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTurnToPosition::~NPCTurnToPosition() = default;

bool NPCTurnToPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCTurnToPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTurnToPosition::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCTurnToPosition::loadParams_() {
    getDynamicParam(&mPosX_d, "PosX");
    getDynamicParam(&mPosY_d, "PosY");
    getDynamicParam(&mPosZ_d, "PosZ");
}

void NPCTurnToPosition::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
