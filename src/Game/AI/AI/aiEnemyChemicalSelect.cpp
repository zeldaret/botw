#include "Game/AI/AI/aiEnemyChemicalSelect.h"

namespace uking::ai {

EnemyChemicalSelect::EnemyChemicalSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyChemicalSelect::~EnemyChemicalSelect() = default;

bool EnemyChemicalSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyChemicalSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyChemicalSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyChemicalSelect::loadParams_() {
    getStaticParam(&mIsCheckActive_s, "IsCheckActive");
    getStaticParam(&mChmObjName_s, "ChmObjName");
}

}  // namespace uking::ai
