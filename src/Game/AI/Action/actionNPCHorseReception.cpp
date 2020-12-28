#include "Game/AI/Action/actionNPCHorseReception.h"

namespace uking::action {

NPCHorseReception::NPCHorseReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCHorseReception::~NPCHorseReception() = default;

void NPCHorseReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCHorseReception::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
