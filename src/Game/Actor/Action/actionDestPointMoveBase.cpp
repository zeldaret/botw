#include "Game/Actor/Action/actionDestPointMoveBase.h"

namespace uking::action {

DestPointMoveBase::DestPointMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DestPointMoveBase::~DestPointMoveBase() = default;

bool DestPointMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DestPointMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DestPointMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void DestPointMoveBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getDynamicParam(&mASSlot_d, "ASSlot");
    getDynamicParam(&mSequenceBank_d, "SequenceBank");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mASName_d, "ASName");
}

void DestPointMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
