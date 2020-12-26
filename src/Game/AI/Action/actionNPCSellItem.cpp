#include "Game/AI/Action/actionNPCSellItem.h"

namespace uking::action {

NPCSellItem::NPCSellItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSellItem::~NPCSellItem() = default;

bool NPCSellItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCSellItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCSellItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCSellItem::loadParams_() {}

void NPCSellItem::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
