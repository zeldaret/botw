#include "Game/AI/Action/actionRestorePouchForQuest.h"

namespace uking::action {

RestorePouchForQuest::RestorePouchForQuest(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RestorePouchForQuest::~RestorePouchForQuest() = default;

bool RestorePouchForQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RestorePouchForQuest::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RestorePouchForQuest::leave_() {
    ksys::act::ai::Action::leave_();
}

void RestorePouchForQuest::loadParams_() {}

void RestorePouchForQuest::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
