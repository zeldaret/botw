#include "Game/AI/Action/actionNPCSaleCollectedItem.h"

namespace uking::action {

NPCSaleCollectedItem::NPCSaleCollectedItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSaleCollectedItem::~NPCSaleCollectedItem() = default;

bool NPCSaleCollectedItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCSaleCollectedItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCSaleCollectedItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCSaleCollectedItem::loadParams_() {
    getDynamicParam(&mTableName_d, "TableName");
}

void NPCSaleCollectedItem::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
