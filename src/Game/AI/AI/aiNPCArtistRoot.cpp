#include "Game/AI/AI/aiNPCArtistRoot.h"

namespace uking::ai {

NPCArtistRoot::NPCArtistRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCArtistRoot::~NPCArtistRoot() = default;

bool NPCArtistRoot::init_(sead::Heap* heap) {
    return NPCRoot::init_(heap);
}

void NPCArtistRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCArtistRoot::leave_() {
    NPCRoot::leave_();
}

void NPCArtistRoot::loadParams_() {
    NPCRoot::loadParams_();
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai
