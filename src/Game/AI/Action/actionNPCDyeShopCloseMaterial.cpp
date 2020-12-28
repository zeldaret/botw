#include "Game/AI/Action/actionNPCDyeShopCloseMaterial.h"

namespace uking::action {

NPCDyeShopCloseMaterial::NPCDyeShopCloseMaterial(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCDyeShopCloseMaterial::~NPCDyeShopCloseMaterial() = default;

bool NPCDyeShopCloseMaterial::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCDyeShopCloseMaterial::loadParams_() {}

}  // namespace uking::action
