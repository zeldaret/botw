#include "Game/AI/Action/actionGetItem.h"

namespace uking::action {

GetItem::GetItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool GetItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GetItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GetItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void GetItem::loadParams_() {}

void GetItem::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
