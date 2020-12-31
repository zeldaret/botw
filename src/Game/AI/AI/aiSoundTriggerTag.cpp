#include "Game/AI/AI/aiSoundTriggerTag.h"

namespace uking::ai {

SoundTriggerTag::SoundTriggerTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SoundTriggerTag::~SoundTriggerTag() = default;

bool SoundTriggerTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SoundTriggerTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SoundTriggerTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SoundTriggerTag::loadParams_() {
    getMapUnitParam(&mSoundDelay_m, "SoundDelay");
    getMapUnitParam(&mSound_m, "Sound");
    getMapUnitParam(&mSLinkInst_m, "SLinkInst");
}

}  // namespace uking::ai
