#include "Game/AI/Action/actionSoundOcclusionTagAction.h"

namespace uking::action {

SoundOcclusionTagAction::SoundOcclusionTagAction(const InitArg& arg) : AreaTagAction(arg) {}

SoundOcclusionTagAction::~SoundOcclusionTagAction() = default;

bool SoundOcclusionTagAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void SoundOcclusionTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void SoundOcclusionTagAction::leave_() {
    AreaTagAction::leave_();
}

void SoundOcclusionTagAction::loadParams_() {
    getStaticParam(&mOcclusionLevel_s, "OcclusionLevel");
}

void SoundOcclusionTagAction::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
