#include "Game/AI/AI/aiNPCTravelerRoot.h"

namespace uking::ai {

NPCTravelerRoot::NPCTravelerRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCTravelerRoot::~NPCTravelerRoot() = default;

bool NPCTravelerRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void NPCTravelerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCTravelerRoot::leave_() {
    NPCRoot::leave_();
}

void NPCTravelerRoot::loadParams_() {
    NPCRoot::loadParams_();
    getStaticParam(&mIsRiderChangableAction_s, "IsRiderChangableAction");
}

}  // namespace uking::ai
