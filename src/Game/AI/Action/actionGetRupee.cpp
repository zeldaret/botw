#include "Game/AI/Action/actionGetRupee.h"

namespace uking::action {

GetRupee::GetRupee(const InitArg& arg) : GetItem(arg) {}

bool GetRupee::init_(sead::Heap* heap) {
    return GetItem::init_(heap);
}

void GetRupee::enter_(ksys::act::ai::InlineParamPack* params) {
    GetItem::enter_(params);
}

void GetRupee::leave_() {
    GetItem::leave_();
}

void GetRupee::loadParams_() {
    GetItem::loadParams_();
}

void GetRupee::calc_() {
    GetItem::calc_();
}

}  // namespace uking::action
