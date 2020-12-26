#include "Game/AI/Action/actionNPCDyeGoods.h"

namespace uking::action {

NPCDyeGoods::NPCDyeGoods(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCDyeGoods::~NPCDyeGoods() = default;

bool NPCDyeGoods::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCDyeGoods::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCDyeGoods::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCDyeGoods::loadParams_() {}

void NPCDyeGoods::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
