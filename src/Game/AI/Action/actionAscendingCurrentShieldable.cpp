#include "Game/AI/Action/actionAscendingCurrentShieldable.h"

namespace uking::action {

AscendingCurrentShieldable::AscendingCurrentShieldable(const InitArg& arg)
    : AscendingCurrent(arg) {}

AscendingCurrentShieldable::~AscendingCurrentShieldable() = default;

bool AscendingCurrentShieldable::init_(sead::Heap* heap) {
    return AscendingCurrent::init_(heap);
}

void AscendingCurrentShieldable::enter_(ksys::act::ai::InlineParamPack* params) {
    AscendingCurrent::enter_(params);
}

void AscendingCurrentShieldable::leave_() {
    AscendingCurrent::leave_();
}

void AscendingCurrentShieldable::loadParams_() {
    AscendingCurrent::loadParams_();
}

void AscendingCurrentShieldable::calc_() {
    AscendingCurrent::calc_();
}

}  // namespace uking::action
