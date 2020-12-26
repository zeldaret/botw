#include "Game/AI/Action/actionChuchuDissappearEscape.h"

namespace uking::action {

ChuchuDissappearEscape::ChuchuDissappearEscape(const InitArg& arg)
    : ChuchuDissappearEscapeBase(arg) {}

ChuchuDissappearEscape::~ChuchuDissappearEscape() = default;

bool ChuchuDissappearEscape::init_(sead::Heap* heap) {
    return ChuchuDissappearEscapeBase::init_(heap);
}

void ChuchuDissappearEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ChuchuDissappearEscapeBase::enter_(params);
}

void ChuchuDissappearEscape::leave_() {
    ChuchuDissappearEscapeBase::leave_();
}

void ChuchuDissappearEscape::loadParams_() {
    ChuchuDissappearEscapeBase::loadParams_();
}

void ChuchuDissappearEscape::calc_() {
    ChuchuDissappearEscapeBase::calc_();
}

}  // namespace uking::action
