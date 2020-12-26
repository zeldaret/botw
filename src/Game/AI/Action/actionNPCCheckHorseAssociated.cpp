#include "Game/AI/Action/actionNPCCheckHorseAssociated.h"

namespace uking::action {

NPCCheckHorseAssociated::NPCCheckHorseAssociated(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCCheckHorseAssociated::~NPCCheckHorseAssociated() = default;

bool NPCCheckHorseAssociated::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCCheckHorseAssociated::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCCheckHorseAssociated::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCCheckHorseAssociated::loadParams_() {}

void NPCCheckHorseAssociated::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
