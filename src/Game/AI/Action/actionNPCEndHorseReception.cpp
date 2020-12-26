#include "Game/AI/Action/actionNPCEndHorseReception.h"

namespace uking::action {

NPCEndHorseReception::NPCEndHorseReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCEndHorseReception::~NPCEndHorseReception() = default;

bool NPCEndHorseReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCEndHorseReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCEndHorseReception::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCEndHorseReception::loadParams_() {}

void NPCEndHorseReception::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
