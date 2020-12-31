#include "Game/AI/AI/aiChuchuRoot.h"

namespace uking::ai {

ChuchuRoot::ChuchuRoot(const InitArg& arg) : EnemyRoot(arg) {}

ChuchuRoot::~ChuchuRoot() = default;

bool ChuchuRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void ChuchuRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void ChuchuRoot::leave_() {
    EnemyRoot::leave_();
}

void ChuchuRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mChemicalScaleTime_s, "ChemicalScaleTime");
    getStaticParam(&mClothStiffness30_s, "ClothStiffness30");
    getStaticParam(&mClothStiffness20_s, "ClothStiffness20");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mChemicalFieldKey_s, "ChemicalFieldKey");
    // FIXME: CALL _ZNK4ksys3act2ai6RootAi18getAITreeVariable2EPPbRKN4sead14SafeStringBaseIcEE @
    // 0x7100d66968
}

}  // namespace uking::ai
