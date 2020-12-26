#include "Game/AI/Action/actionChuchuDissappearEscapeBase.h"

namespace uking::action {

ChuchuDissappearEscapeBase::ChuchuDissappearEscapeBase(const InitArg& arg) : ActionWithAS(arg) {}

ChuchuDissappearEscapeBase::~ChuchuDissappearEscapeBase() = default;

bool ChuchuDissappearEscapeBase::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void ChuchuDissappearEscapeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void ChuchuDissappearEscapeBase::leave_() {
    ActionWithAS::leave_();
}

void ChuchuDissappearEscapeBase::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void ChuchuDissappearEscapeBase::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
