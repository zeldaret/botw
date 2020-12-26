#include "Game/AI/Action/actionGetSmallKeyItemGet.h"

namespace uking::action {

GetSmallKeyItemGet::GetSmallKeyItemGet(const InitArg& arg) : GetItem(arg) {}

GetSmallKeyItemGet::~GetSmallKeyItemGet() = default;

bool GetSmallKeyItemGet::init_(sead::Heap* heap) {
    return GetItem::init_(heap);
}

void GetSmallKeyItemGet::enter_(ksys::act::ai::InlineParamPack* params) {
    GetItem::enter_(params);
}

void GetSmallKeyItemGet::leave_() {
    GetItem::leave_();
}

void GetSmallKeyItemGet::loadParams_() {
    GetItem::loadParams_();
}

void GetSmallKeyItemGet::calc_() {
    GetItem::calc_();
}

}  // namespace uking::action
