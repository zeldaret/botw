#include "Game/AI/Action/actionHorseKickBackAction.h"

namespace uking::action {

HorseKickBackAction::HorseKickBackAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseKickBackAction::~HorseKickBackAction() = default;

bool HorseKickBackAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseKickBackAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseKickBackAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseKickBackAction::loadParams_() {
    getStaticParam(&mSucceedGear_s, "SucceedGear");
    getStaticParam(&mASName_s, "ASName");
}

void HorseKickBackAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
