#include "Game/AI/Action/actionNPCCloseHorseCustom.h"

namespace uking::action {

NPCCloseHorseCustom::NPCCloseHorseCustom(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCCloseHorseCustom::~NPCCloseHorseCustom() = default;

bool NPCCloseHorseCustom::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCCloseHorseCustom::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCCloseHorseCustom::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCCloseHorseCustom::loadParams_() {}

void NPCCloseHorseCustom::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
