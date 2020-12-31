#include "Game/AI/AI/aiNpcTebaRoot.h"

namespace uking::ai {

NpcTebaRoot::NpcTebaRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NpcTebaRoot::~NpcTebaRoot() = default;

bool NpcTebaRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NpcTebaRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NpcTebaRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NpcTebaRoot::loadParams_() {
    getStaticParam(&mShowMessageLockonMinInterval_s, "ShowMessageLockonMinInterval");
    getStaticParam(&mApproachPlayerHeight_s, "ApproachPlayerHeight");
    getStaticParam(&mShowMessageDoDist_s, "ShowMessageDoDist");
}

}  // namespace uking::ai
