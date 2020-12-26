#include "Game/AI/Action/actionNPCDyeShopSelectMaterial.h"

namespace uking::action {

NPCDyeShopSelectMaterial::NPCDyeShopSelectMaterial(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCDyeShopSelectMaterial::~NPCDyeShopSelectMaterial() = default;

bool NPCDyeShopSelectMaterial::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCDyeShopSelectMaterial::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCDyeShopSelectMaterial::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCDyeShopSelectMaterial::loadParams_() {}

void NPCDyeShopSelectMaterial::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
