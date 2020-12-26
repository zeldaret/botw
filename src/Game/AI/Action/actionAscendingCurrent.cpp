#include "Game/AI/Action/actionAscendingCurrent.h"

namespace uking::action {

AscendingCurrent::AscendingCurrent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AscendingCurrent::~AscendingCurrent() = default;

bool AscendingCurrent::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AscendingCurrent::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AscendingCurrent::leave_() {
    ksys::act::ai::Action::leave_();
}

void AscendingCurrent::loadParams_() {
    getStaticParam(&mWindSpeed_s, "WindSpeed");
}

void AscendingCurrent::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
