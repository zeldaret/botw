#include "Game/AI/Action/actionCheckHorseCustomizeEdit.h"

namespace uking::action {

CheckHorseCustomizeEdit::CheckHorseCustomizeEdit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CheckHorseCustomizeEdit::~CheckHorseCustomizeEdit() = default;

bool CheckHorseCustomizeEdit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CheckHorseCustomizeEdit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CheckHorseCustomizeEdit::leave_() {
    ksys::act::ai::Action::leave_();
}

void CheckHorseCustomizeEdit::loadParams_() {}

void CheckHorseCustomizeEdit::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
