#include "Game/AI/Action/actionSetRequestAttention.h"

namespace uking::action {

SetRequestAttention::SetRequestAttention(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetRequestAttention::~SetRequestAttention() = default;

bool SetRequestAttention::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetRequestAttention::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetRequestAttention::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetRequestAttention::loadParams_() {
    getStaticParam(&mIsOn_s, "IsOn");
    getStaticParam(&mIsAll_s, "IsAll");
    getStaticParam(&mAttName_s, "AttName");
}

void SetRequestAttention::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
