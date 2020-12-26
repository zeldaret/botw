#include "Game/AI/Action/actionAirOctaNoticeTurn.h"

namespace uking::action {

AirOctaNoticeTurn::AirOctaNoticeTurn(const InitArg& arg) : NoticeTurn(arg) {}

AirOctaNoticeTurn::~AirOctaNoticeTurn() = default;

bool AirOctaNoticeTurn::init_(sead::Heap* heap) {
    return NoticeTurn::init_(heap);
}

void AirOctaNoticeTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    NoticeTurn::enter_(params);
}

void AirOctaNoticeTurn::leave_() {
    NoticeTurn::leave_();
}

void AirOctaNoticeTurn::loadParams_() {
    NoticeTurn::loadParams_();
}

void AirOctaNoticeTurn::calc_() {
    NoticeTurn::calc_();
}

}  // namespace uking::action
