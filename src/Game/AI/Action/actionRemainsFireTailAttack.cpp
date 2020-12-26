#include "Game/AI/Action/actionRemainsFireTailAttack.h"

namespace uking::action {

RemainsFireTailAttack::RemainsFireTailAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RemainsFireTailAttack::~RemainsFireTailAttack() = default;

bool RemainsFireTailAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsFireTailAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsFireTailAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsFireTailAttack::loadParams_() {
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void RemainsFireTailAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
