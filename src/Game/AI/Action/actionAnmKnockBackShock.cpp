#include "Game/AI/Action/actionAnmKnockBackShock.h"

namespace uking::action {

AnmKnockBackShock::AnmKnockBackShock(const InitArg& arg) : KnockBackShock(arg) {}

AnmKnockBackShock::~AnmKnockBackShock() = default;

bool AnmKnockBackShock::init_(sead::Heap* heap) {
    return KnockBackShock::init_(heap);
}

void AnmKnockBackShock::enter_(ksys::act::ai::InlineParamPack* params) {
    KnockBackShock::enter_(params);
}

void AnmKnockBackShock::leave_() {
    KnockBackShock::leave_();
}

void AnmKnockBackShock::loadParams_() {
    KnockBackShock::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void AnmKnockBackShock::calc_() {
    KnockBackShock::calc_();
}

}  // namespace uking::action
