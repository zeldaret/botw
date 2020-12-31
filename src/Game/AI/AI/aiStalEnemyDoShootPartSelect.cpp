#include "Game/AI/AI/aiStalEnemyDoShootPartSelect.h"

namespace uking::ai {

StalEnemyDoShootPartSelect::StalEnemyDoShootPartSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

StalEnemyDoShootPartSelect::~StalEnemyDoShootPartSelect() = default;

bool StalEnemyDoShootPartSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyDoShootPartSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalEnemyDoShootPartSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalEnemyDoShootPartSelect::loadParams_() {
    getStaticParam(&mShootRate_s, "ShootRate");
}

}  // namespace uking::ai
