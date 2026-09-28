#include "KingSystem/Sound/Actor/Action/actionSoundOcclusionTagAction.h"

namespace ksys::snd {

SoundOcclusionTagAction::SoundOcclusionTagAction(const InitArg& arg) : AreaActionBase(arg) {}

SoundOcclusionTagAction::~SoundOcclusionTagAction() = default;

bool SoundOcclusionTagAction::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void SoundOcclusionTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void SoundOcclusionTagAction::leave_() {
    AreaActionBase::leave_();
}

void SoundOcclusionTagAction::loadParams_() {
    getStaticParam(&mOcclusionLevel_s, "OcclusionLevel");
}

void SoundOcclusionTagAction::calc_() {
    AreaActionBase::calc_();
}

}  // namespace ksys::snd
