#include "Game/AI/Action/actionGetItemGet.h"

namespace uking::action {

GetItemGet::GetItemGet(const InitArg& arg) : GetItem(arg) {}

void GetItemGet::enter_(ksys::act::ai::InlineParamPack* params) {
    GetItem::enter_(params);
}

void GetItemGet::leave_() {
    GetItem::leave_();
}

void GetItemGet::loadParams_() {
    GetItem::loadParams_();
}

void GetItemGet::calc_() {
    GetItem::calc_();
}

}  // namespace uking::action
