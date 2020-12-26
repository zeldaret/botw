#include "Game/AI/Action/actionGetItemIntoBag.h"

namespace uking::action {

GetItemIntoBag::GetItemIntoBag(const InitArg& arg) : GetItem(arg) {}

GetItemIntoBag::~GetItemIntoBag() = default;

bool GetItemIntoBag::init_(sead::Heap* heap) {
    return GetItem::init_(heap);
}

void GetItemIntoBag::enter_(ksys::act::ai::InlineParamPack* params) {
    GetItem::enter_(params);
}

void GetItemIntoBag::leave_() {
    GetItem::leave_();
}

void GetItemIntoBag::loadParams_() {
    GetItem::loadParams_();
}

void GetItemIntoBag::calc_() {
    GetItem::calc_();
}

}  // namespace uking::action
