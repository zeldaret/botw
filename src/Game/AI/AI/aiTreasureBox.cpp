#include "Game/AI/AI/aiTreasureBox.h"

namespace uking::ai {

TreasureBox::TreasureBox(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TreasureBox::~TreasureBox() = default;

bool TreasureBox::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TreasureBox::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TreasureBox::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TreasureBox::loadParams_() {
    getMapUnitParam(&mSharpWeaponJudgeType_m, "SharpWeaponJudgeType");
    getMapUnitParam(&mDropActor_m, "DropActor");
    getMapUnitParam(&mDropTable_m, "DropTable");
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
    getAITreeVariable(&mIsSetupDropActor_a, "IsSetupDropActor");
    getAITreeVariable(&mDropActorName_a, "DropActorName");
    getAITreeVariable(&mSharpWeaponAddParam_a, "SharpWeaponAddParam");
}

}  // namespace uking::ai
