#include "Game/AI/AI/aiNPCClerkRoot.h"

namespace uking::ai {

NPCClerkRoot::NPCClerkRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCClerkRoot::~NPCClerkRoot() = default;

bool NPCClerkRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void NPCClerkRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCClerkRoot::leave_() {
    NPCRoot::leave_();
}

void NPCClerkRoot::loadParams_() {
    NPCRoot::loadParams_();
}

}  // namespace uking::ai
