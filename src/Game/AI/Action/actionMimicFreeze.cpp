#include "Game/AI/Action/actionMimicFreeze.h"

namespace uking::action {

MimicFreeze::MimicFreeze(const InitArg& arg) : Freeze(arg) {}

MimicFreeze::~MimicFreeze() = default;

bool MimicFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void MimicFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
}

void MimicFreeze::leave_() {
    Freeze::leave_();
}

void MimicFreeze::loadParams_() {
    Freeze::loadParams_();
}

void MimicFreeze::calc_() {
    Freeze::calc_();
}

}  // namespace uking::action
