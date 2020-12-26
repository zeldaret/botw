#include "Game/AI/Action/actionNPCHorseReceptionRelease.h"

namespace uking::action {

NPCHorseReceptionRelease::NPCHorseReceptionRelease(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCHorseReceptionRelease::~NPCHorseReceptionRelease() = default;

bool NPCHorseReceptionRelease::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCHorseReceptionRelease::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCHorseReceptionRelease::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCHorseReceptionRelease::loadParams_() {}

void NPCHorseReceptionRelease::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
