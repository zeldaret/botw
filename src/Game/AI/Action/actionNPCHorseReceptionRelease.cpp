#include "Game/AI/Action/actionNPCHorseReceptionRelease.h"

namespace uking::action {

NPCHorseReceptionRelease::NPCHorseReceptionRelease(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCHorseReceptionRelease::~NPCHorseReceptionRelease() = default;

void NPCHorseReceptionRelease::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCHorseReceptionRelease::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
