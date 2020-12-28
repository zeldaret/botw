#include "Game/AI/Action/actionNPCDyeShopReception.h"

namespace uking::action {

NPCDyeShopReception::NPCDyeShopReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCDyeShopReception::~NPCDyeShopReception() = default;

bool NPCDyeShopReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCDyeShopReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCDyeShopReception::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
