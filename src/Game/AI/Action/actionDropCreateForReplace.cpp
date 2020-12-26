#include "Game/AI/Action/actionDropCreateForReplace.h"

namespace uking::action {

DropCreateForReplace::DropCreateForReplace(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DropCreateForReplace::~DropCreateForReplace() = default;

bool DropCreateForReplace::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DropCreateForReplace::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DropCreateForReplace::leave_() {
    ksys::act::ai::Action::leave_();
}

void DropCreateForReplace::loadParams_() {}

void DropCreateForReplace::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
