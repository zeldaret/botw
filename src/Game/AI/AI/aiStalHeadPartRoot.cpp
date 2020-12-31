#include "Game/AI/AI/aiStalHeadPartRoot.h"

namespace uking::ai {

StalHeadPartRoot::StalHeadPartRoot(const InitArg& arg) : EnemyRoot(arg) {}

StalHeadPartRoot::~StalHeadPartRoot() = default;

bool StalHeadPartRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void StalHeadPartRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void StalHeadPartRoot::leave_() {
    EnemyRoot::leave_();
}

void StalHeadPartRoot::loadParams_() {
    EnemyRoot::loadParams_();
}

}  // namespace uking::ai
