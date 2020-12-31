#include "Game/AI/AI/aiNpcTebaTrainingRoot.h"

namespace uking::ai {

NpcTebaTrainingRoot::NpcTebaTrainingRoot(const InitArg& arg) : NPCRoot(arg) {}

NpcTebaTrainingRoot::~NpcTebaTrainingRoot() = default;

bool NpcTebaTrainingRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void NpcTebaTrainingRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NpcTebaTrainingRoot::leave_() {
    NPCRoot::leave_();
}

void NpcTebaTrainingRoot::loadParams_() {
    NPCRoot::loadParams_();
}

}  // namespace uking::ai
