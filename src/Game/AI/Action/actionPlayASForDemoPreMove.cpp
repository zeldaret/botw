#include "Game/AI/Action/actionPlayASForDemoPreMove.h"

namespace uking::action {

PlayASForDemoPreMove::PlayASForDemoPreMove(const InitArg& arg) : PlayASForDemo(arg) {}

PlayASForDemoPreMove::~PlayASForDemoPreMove() = default;

bool PlayASForDemoPreMove::init_(sead::Heap* heap) {
    return PlayASForDemo::init_(heap);
}

void PlayASForDemoPreMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForDemo::enter_(params);
}

void PlayASForDemoPreMove::leave_() {
    PlayASForDemo::leave_();
}

void PlayASForDemoPreMove::loadParams_() {
    PlayASForDemo::loadParams_();
}

void PlayASForDemoPreMove::calc_() {
    PlayASForDemo::calc_();
}

}  // namespace uking::action
