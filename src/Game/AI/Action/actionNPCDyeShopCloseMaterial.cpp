#include "Game/AI/Action/actionNPCDyeShopCloseMaterial.h"

namespace uking::action {

NPCDyeShopCloseMaterial::NPCDyeShopCloseMaterial(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCDyeShopCloseMaterial::~NPCDyeShopCloseMaterial() = default;

bool NPCDyeShopCloseMaterial::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCDyeShopCloseMaterial::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCDyeShopCloseMaterial::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCDyeShopCloseMaterial::loadParams_() {}

void NPCDyeShopCloseMaterial::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
