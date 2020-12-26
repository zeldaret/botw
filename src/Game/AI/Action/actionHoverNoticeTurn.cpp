#include "Game/AI/Action/actionHoverNoticeTurn.h"

namespace uking::action {

HoverNoticeTurn::HoverNoticeTurn(const InitArg& arg) : NoticeTurn(arg) {}

HoverNoticeTurn::~HoverNoticeTurn() = default;

bool HoverNoticeTurn::init_(sead::Heap* heap) {
    return NoticeTurn::init_(heap);
}

void HoverNoticeTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    NoticeTurn::enter_(params);
}

void HoverNoticeTurn::leave_() {
    NoticeTurn::leave_();
}

void HoverNoticeTurn::loadParams_() {
    NoticeTurn::loadParams_();
}

void HoverNoticeTurn::calc_() {
    NoticeTurn::calc_();
}

}  // namespace uking::action
