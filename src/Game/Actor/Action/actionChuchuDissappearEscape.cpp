#include "Game/Actor/Action/actionChuchuDissappearEscape.h"

namespace uking::action {

ChuchuDissappearEscape::ChuchuDissappearEscape(const InitArg& arg) : DisappearAndEscapeBase(arg) {}

ChuchuDissappearEscape::~ChuchuDissappearEscape() = default;

bool ChuchuDissappearEscape::init_(sead::Heap* heap) {
    return DisappearAndEscapeBase::init_(heap);
}

void ChuchuDissappearEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    DisappearAndEscapeBase::enter_(params);
}

void ChuchuDissappearEscape::leave_() {
    DisappearAndEscapeBase::leave_();
}

void ChuchuDissappearEscape::loadParams_() {
    DisappearAndEscapeBase::loadParams_();
}

void ChuchuDissappearEscape::calc_() {
    DisappearAndEscapeBase::calc_();
}

}  // namespace uking::action
