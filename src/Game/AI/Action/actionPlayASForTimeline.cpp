#include "Game/AI/Action/actionPlayASForTimeline.h"

namespace uking::action {

PlayASForTimeline::PlayASForTimeline(const InitArg& arg) : PlayASForDemo(arg) {}

PlayASForTimeline::~PlayASForTimeline() = default;

bool PlayASForTimeline::init_(sead::Heap* heap) {
    return PlayASForDemo::init_(heap);
}

void PlayASForTimeline::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForDemo::enter_(params);
}

void PlayASForTimeline::leave_() {
    PlayASForDemo::leave_();
}

void PlayASForTimeline::loadParams_() {
    PlayASForDemo::loadParams_();
    getDynamicParam(&mClipIndex_d, "ClipIndex");
}

void PlayASForTimeline::calc_() {
    PlayASForDemo::calc_();
}

}  // namespace uking::action
