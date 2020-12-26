#include "Game/AI/Action/actionHover.h"

namespace uking::action {

Hover::Hover(const InitArg& arg) : HoverBase(arg) {}

Hover::~Hover() = default;

bool Hover::init_(sead::Heap* heap) {
    return HoverBase::init_(heap);
}

void Hover::enter_(ksys::act::ai::InlineParamPack* params) {
    HoverBase::enter_(params);
}

void Hover::leave_() {
    HoverBase::leave_();
}

void Hover::loadParams_() {
    HoverBase::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mASName_s, "ASName");
}

void Hover::calc_() {
    HoverBase::calc_();
}

}  // namespace uking::action
