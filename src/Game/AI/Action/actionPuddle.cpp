#include "Game/AI/Action/actionPuddle.h"

namespace uking::action {

Puddle::Puddle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Puddle::~Puddle() = default;

bool Puddle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Puddle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Puddle::leave_() {
    ksys::act::ai::Action::leave_();
}

void Puddle::loadParams_() {}

void Puddle::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
