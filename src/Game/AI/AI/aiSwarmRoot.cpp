#include "Game/AI/AI/aiSwarmRoot.h"

namespace uking::ai {

SwarmRoot::SwarmRoot(const InitArg& arg) : EnemyRoot(arg) {}

SwarmRoot::~SwarmRoot() = default;

bool SwarmRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void SwarmRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void SwarmRoot::leave_() {
    EnemyRoot::leave_();
}

void SwarmRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::ai
