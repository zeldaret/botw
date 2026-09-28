#include "Game/Actor/Action/actionAnmKnockBackShock.h"

namespace uking::action {

AnmKnockBackShock::AnmKnockBackShock(const InitArg& arg) : SimpleKnockBackShock(arg) {}

AnmKnockBackShock::~AnmKnockBackShock() = default;

bool AnmKnockBackShock::init_(sead::Heap* heap) {
    return SimpleKnockBackShock::init_(heap);
}

void AnmKnockBackShock::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleKnockBackShock::enter_(params);
}

void AnmKnockBackShock::leave_() {
    SimpleKnockBackShock::leave_();
}

void AnmKnockBackShock::loadParams_() {
    SimpleKnockBackShock::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void AnmKnockBackShock::calc_() {
    SimpleKnockBackShock::calc_();
}

}  // namespace uking::action
