#include "Game/AI/Action/actionNPCMakeArtifact.h"

namespace uking::action {

NPCMakeArtifact::NPCMakeArtifact(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCMakeArtifact::~NPCMakeArtifact() = default;

bool NPCMakeArtifact::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCMakeArtifact::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCMakeArtifact::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCMakeArtifact::loadParams_() {}

void NPCMakeArtifact::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
