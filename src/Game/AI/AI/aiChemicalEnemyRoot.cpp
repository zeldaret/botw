#include "Game/AI/AI/aiChemicalEnemyRoot.h"

namespace uking::ai {

ChemicalEnemyRoot::ChemicalEnemyRoot(const InitArg& arg) : EnemyRoot(arg) {}

ChemicalEnemyRoot::~ChemicalEnemyRoot() = default;

void ChemicalEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void ChemicalEnemyRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mIsElementNoHit_s, "IsElementNoHit");
    getStaticParam(&mIsElectricWater_s, "IsElectricWater");
    getStaticParam(&mColorASName_s, "ColorASName");
}

}  // namespace uking::ai
