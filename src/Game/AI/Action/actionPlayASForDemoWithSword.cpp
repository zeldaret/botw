#include "Game/AI/Action/actionPlayASForDemoWithSword.h"

namespace uking::action {

PlayASForDemoWithSword::PlayASForDemoWithSword(const InitArg& arg) : PlayASForDemo(arg) {}

PlayASForDemoWithSword::~PlayASForDemoWithSword() = default;

bool PlayASForDemoWithSword::init_(sead::Heap* heap) {
    return PlayASForDemo::init_(heap);
}

void PlayASForDemoWithSword::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForDemo::enter_(params);
}

void PlayASForDemoWithSword::leave_() {
    PlayASForDemo::leave_();
}

void PlayASForDemoWithSword::loadParams_() {
    PlayASForDemo::loadParams_();
    getDynamicParam(&mIsHold_d, "IsHold");
}

void PlayASForDemoWithSword::calc_() {
    PlayASForDemo::calc_();
}

}  // namespace uking::action
