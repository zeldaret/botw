#include "Game/AI/Action/actionAppearGameOver.h"

namespace uking::action {

AppearGameOver::AppearGameOver(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearGameOver::~AppearGameOver() = default;

bool AppearGameOver::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearGameOver::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AppearGameOver::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearGameOver::loadParams_() {
    getDynamicParam(&mDelay_d, "Delay");
}

void AppearGameOver::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
