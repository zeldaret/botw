#include "Game/AI/Action/actionNPCPurchaseMaterial.h"

namespace uking::action {

NPCPurchaseMaterial::NPCPurchaseMaterial(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCPurchaseMaterial::~NPCPurchaseMaterial() = default;

bool NPCPurchaseMaterial::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCPurchaseMaterial::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCPurchaseMaterial::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCPurchaseMaterial::loadParams_() {}

void NPCPurchaseMaterial::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
