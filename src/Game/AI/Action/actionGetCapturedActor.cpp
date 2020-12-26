#include "Game/AI/Action/actionGetCapturedActor.h"

namespace uking::action {

GetCapturedActor::GetCapturedActor(const InitArg& arg) : GetItem(arg) {}

GetCapturedActor::~GetCapturedActor() = default;

bool GetCapturedActor::init_(sead::Heap* heap) {
    return GetItem::init_(heap);
}

void GetCapturedActor::enter_(ksys::act::ai::InlineParamPack* params) {
    GetItem::enter_(params);
}

void GetCapturedActor::leave_() {
    GetItem::leave_();
}

void GetCapturedActor::loadParams_() {
    GetItem::loadParams_();
}

void GetCapturedActor::calc_() {
    GetItem::calc_();
}

}  // namespace uking::action
