#include "Game/AI/Action/actionNPCKnockBackMove.h"

namespace uking::action {

NPCKnockBackMove::NPCKnockBackMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCKnockBackMove::~NPCKnockBackMove() = default;

bool NPCKnockBackMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCKnockBackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCKnockBackMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCKnockBackMove::loadParams_() {
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mMoveDir_d, "MoveDir");
}

void NPCKnockBackMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
