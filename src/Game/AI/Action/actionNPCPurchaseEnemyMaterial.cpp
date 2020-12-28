#include "Game/AI/Action/actionNPCPurchaseEnemyMaterial.h"

namespace uking::action {

NPCPurchaseEnemyMaterial::NPCPurchaseEnemyMaterial(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCPurchaseEnemyMaterial::~NPCPurchaseEnemyMaterial() = default;

bool NPCPurchaseEnemyMaterial::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCPurchaseEnemyMaterial::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCPurchaseEnemyMaterial::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
