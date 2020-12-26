#include "Game/AI/Action/actionAscendingCurrentFixedSize.h"

namespace uking::action {

AscendingCurrentFixedSize::AscendingCurrentFixedSize(const InitArg& arg) : AscendingCurrent(arg) {}

AscendingCurrentFixedSize::~AscendingCurrentFixedSize() = default;

bool AscendingCurrentFixedSize::init_(sead::Heap* heap) {
    return AscendingCurrent::init_(heap);
}

void AscendingCurrentFixedSize::enter_(ksys::act::ai::InlineParamPack* params) {
    AscendingCurrent::enter_(params);
}

void AscendingCurrentFixedSize::leave_() {
    AscendingCurrent::leave_();
}

void AscendingCurrentFixedSize::loadParams_() {
    AscendingCurrent::loadParams_();
    getStaticParam(&mDisableInDemo_s, "DisableInDemo");
    getStaticParam(&mSize_s, "Size");
}

void AscendingCurrentFixedSize::calc_() {
    AscendingCurrent::calc_();
}

}  // namespace uking::action
