#include "Game/AI/Action/actionOnCorrect.h"

namespace uking::action {

OnCorrect::OnCorrect(const InitArg& arg) : On(arg) {}

OnCorrect::~OnCorrect() = default;

bool OnCorrect::init_(sead::Heap* heap) {
    return On::init_(heap);
}

void OnCorrect::enter_(ksys::act::ai::InlineParamPack* params) {
    On::enter_(params);
}

void OnCorrect::leave_() {
    On::leave_();
}

void OnCorrect::loadParams_() {
    On::loadParams_();
}

void OnCorrect::calc_() {
    On::calc_();
}

}  // namespace uking::action
