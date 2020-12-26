#include "Game/AI/Action/actionHorseRideMoveToCommand.h"

namespace uking::action {

HorseRideMoveToCommand::HorseRideMoveToCommand(const InitArg& arg) : HorseRideMoveCommand(arg) {}

HorseRideMoveToCommand::~HorseRideMoveToCommand() = default;

bool HorseRideMoveToCommand::init_(sead::Heap* heap) {
    return HorseRideMoveCommand::init_(heap);
}

void HorseRideMoveToCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideMoveCommand::enter_(params);
}

void HorseRideMoveToCommand::leave_() {
    HorseRideMoveCommand::leave_();
}

void HorseRideMoveToCommand::loadParams_() {
    HorseRideMoveCommand::loadParams_();
}

void HorseRideMoveToCommand::calc_() {
    HorseRideMoveCommand::calc_();
}

}  // namespace uking::action
