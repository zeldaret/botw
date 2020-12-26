#include "Game/AI/Action/actionOpenItemCategory.h"

namespace uking::action {

OpenItemCategory::OpenItemCategory(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenItemCategory::~OpenItemCategory() = default;

bool OpenItemCategory::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenItemCategory::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenItemCategory::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenItemCategory::loadParams_() {
    getDynamicParam(&mCategory_d, "Category");
}

void OpenItemCategory::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
