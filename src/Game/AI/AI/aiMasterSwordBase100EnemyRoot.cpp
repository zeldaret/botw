#include "Game/AI/AI/aiMasterSwordBase100EnemyRoot.h"

namespace uking::ai {

MasterSwordBase100EnemyRoot::MasterSwordBase100EnemyRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

MasterSwordBase100EnemyRoot::~MasterSwordBase100EnemyRoot() = default;

bool MasterSwordBase100EnemyRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MasterSwordBase100EnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MasterSwordBase100EnemyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MasterSwordBase100EnemyRoot::loadParams_() {
    getStaticParam(&mKillAttentionWaitFrame_s, "KillAttentionWaitFrame");
}

}  // namespace uking::ai
