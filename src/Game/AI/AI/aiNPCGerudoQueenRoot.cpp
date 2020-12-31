#include "Game/AI/AI/aiNPCGerudoQueenRoot.h"

namespace uking::ai {

NPCGerudoQueenRoot::NPCGerudoQueenRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCGerudoQueenRoot::~NPCGerudoQueenRoot() = default;

bool NPCGerudoQueenRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void NPCGerudoQueenRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCGerudoQueenRoot::leave_() {
    NPCRoot::leave_();
}

void NPCGerudoQueenRoot::loadParams_() {
    NPCRoot::loadParams_();
    getMapUnitParam(&mIsOnHelmet_m, "IsOnHelmet");
}

}  // namespace uking::ai
