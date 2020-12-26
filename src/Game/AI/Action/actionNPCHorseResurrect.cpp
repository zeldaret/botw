#include "Game/AI/Action/actionNPCHorseResurrect.h"

namespace uking::action {

NPCHorseResurrect::NPCHorseResurrect(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCHorseResurrect::~NPCHorseResurrect() = default;

bool NPCHorseResurrect::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCHorseResurrect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCHorseResurrect::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCHorseResurrect::loadParams_() {}

void NPCHorseResurrect::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
