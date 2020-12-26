#include "Game/AI/Action/actionInCarryBox.h"

namespace uking::action {

InCarryBox::InCarryBox(const InitArg& arg) : ksys::act::ai::Action(arg) {}

InCarryBox::~InCarryBox() = default;

bool InCarryBox::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void InCarryBox::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void InCarryBox::leave_() {
    ksys::act::ai::Action::leave_();
}

void InCarryBox::loadParams_() {
    getAITreeVariable(&mIsInitFromCarryBox_a, "IsInitFromCarryBox");
}

void InCarryBox::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
