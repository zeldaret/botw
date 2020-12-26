#include "Game/AI/Action/actionForkModelFadeOut.h"

namespace uking::action {

ForkModelFadeOut::ForkModelFadeOut(const InitArg& arg) : Fork(arg) {}

ForkModelFadeOut::~ForkModelFadeOut() = default;

bool ForkModelFadeOut::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkModelFadeOut::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkModelFadeOut::leave_() {
    Fork::leave_();
}

void ForkModelFadeOut::loadParams_() {
    Fork::loadParams_();
}

void ForkModelFadeOut::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
