#include "Game/AI/Action/actionAnmArmorBindAction.h"

namespace uking::action {

AnmArmorBindAction::AnmArmorBindAction(const InitArg& arg) : ArmorBindAction(arg) {}

AnmArmorBindAction::~AnmArmorBindAction() = default;

bool AnmArmorBindAction::init_(sead::Heap* heap) {
    return ArmorBindAction::init_(heap);
}

void AnmArmorBindAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ArmorBindAction::enter_(params);
}

void AnmArmorBindAction::leave_() {
    ArmorBindAction::leave_();
}

void AnmArmorBindAction::loadParams_() {
    ArmorBindAction::loadParams_();
}

void AnmArmorBindAction::calc_() {
    ArmorBindAction::calc_();
}

}  // namespace uking::action
