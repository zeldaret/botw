#include "Game/AI/Action/actionNPCHorseReception.h"

namespace uking::action {

NPCHorseReception::NPCHorseReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCHorseReception::~NPCHorseReception() = default;

bool NPCHorseReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCHorseReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCHorseReception::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCHorseReception::loadParams_() {}

void NPCHorseReception::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
