#include "Game/AI/Action/actionLookAtTheFront.h"

namespace uking::action {

LookAtTheFront::LookAtTheFront(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LookAtTheFront::~LookAtTheFront() = default;

bool LookAtTheFront::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LookAtTheFront::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LookAtTheFront::leave_() {
    ksys::act::ai::Action::leave_();
}

void LookAtTheFront::loadParams_() {
    getDynamicParam(&mIsValid_d, "IsValid");
}

void LookAtTheFront::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
