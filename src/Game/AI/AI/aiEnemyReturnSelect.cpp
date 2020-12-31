#include "Game/AI/AI/aiEnemyReturnSelect.h"

namespace uking::ai {

EnemyReturnSelect::EnemyReturnSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyReturnSelect::~EnemyReturnSelect() = default;

bool EnemyReturnSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyReturnSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyReturnSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyReturnSelect::loadParams_() {
    getStaticParam(&mNotReturnDist_s, "NotReturnDist");
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

}  // namespace uking::ai
