#include "Game/AI/Action/actionHorseWaitAndLookAtNPC.h"

namespace uking::action {

HorseWaitAndLookAtNPC::HorseWaitAndLookAtNPC(const InitArg& arg) : HorseWaitAction(arg) {}

HorseWaitAndLookAtNPC::~HorseWaitAndLookAtNPC() = default;

bool HorseWaitAndLookAtNPC::init_(sead::Heap* heap) {
    return HorseWaitAction::init_(heap);
}

void HorseWaitAndLookAtNPC::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseWaitAction::enter_(params);
}

void HorseWaitAndLookAtNPC::leave_() {
    HorseWaitAction::leave_();
}

void HorseWaitAndLookAtNPC::loadParams_() {
    HorseWaitAction::loadParams_();
}

void HorseWaitAndLookAtNPC::calc_() {
    HorseWaitAction::calc_();
}

}  // namespace uking::action
