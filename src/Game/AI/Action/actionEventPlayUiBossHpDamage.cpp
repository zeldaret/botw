#include "Game/AI/Action/actionEventPlayUiBossHpDamage.h"

namespace uking::action {

EventPlayUiBossHpDamage::EventPlayUiBossHpDamage(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiBossHpDamage::~EventPlayUiBossHpDamage() = default;

bool EventPlayUiBossHpDamage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiBossHpDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayUiBossHpDamage::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayUiBossHpDamage::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
}

void EventPlayUiBossHpDamage::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
