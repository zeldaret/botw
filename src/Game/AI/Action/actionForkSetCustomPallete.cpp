#include "Game/AI/Action/actionForkSetCustomPallete.h"

namespace uking::action {

ForkSetCustomPallete::ForkSetCustomPallete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSetCustomPallete::~ForkSetCustomPallete() = default;

bool ForkSetCustomPallete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSetCustomPallete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSetCustomPallete::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSetCustomPallete::loadParams_() {
    getStaticParam(&mPalleteType_s, "PalleteType");
}

void ForkSetCustomPallete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
