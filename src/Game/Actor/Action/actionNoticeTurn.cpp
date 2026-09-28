#include "Game/Actor/Action/actionNoticeTurn.h"

namespace uking::action {

NoticeTurn::NoticeTurn(const InitArg& arg) : ASPlayRotateTurnToTarget(arg) {}

NoticeTurn::~NoticeTurn() = default;

bool NoticeTurn::init_(sead::Heap* heap) {
    return ASPlayRotateTurnToTarget::init_(heap);
}

void NoticeTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ASPlayRotateTurnToTarget::enter_(params);
}

void NoticeTurn::leave_() {
    ASPlayRotateTurnToTarget::leave_();
}

void NoticeTurn::loadParams_() {
    ASPlayRotateTurnToTarget::loadParams_();
    getStaticParam(&mNoDoubleNoticeTime_s, "NoDoubleNoticeTime");
}

void NoticeTurn::calc_() {
    ASPlayRotateTurnToTarget::calc_();
}

}  // namespace uking::action
