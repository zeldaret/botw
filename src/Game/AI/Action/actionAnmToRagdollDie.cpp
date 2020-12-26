#include "Game/AI/Action/actionAnmToRagdollDie.h"

namespace uking::action {

AnmToRagdollDie::AnmToRagdollDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmToRagdollDie::~AnmToRagdollDie() = default;

bool AnmToRagdollDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmToRagdollDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnmToRagdollDie::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmToRagdollDie::loadParams_() {
    getStaticParam(&mChangeRagdollFrame_s, "ChangeRagdollFrame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mPosBaseRagdollRbName_s, "PosBaseRagdollRbName");
    getStaticParam(&mRagdollControllerName_s, "RagdollControllerName");
}

void AnmToRagdollDie::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
