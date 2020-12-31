#include "Game/AI/AI/aiNPCHeartsRoot.h"

namespace uking::ai {

NPCHeartsRoot::NPCHeartsRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCHeartsRoot::~NPCHeartsRoot() = default;

bool NPCHeartsRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void NPCHeartsRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCHeartsRoot::leave_() {
    NPCRoot::leave_();
}

void NPCHeartsRoot::loadParams_() {
    NPCRoot::loadParams_();
}

}  // namespace uking::ai
