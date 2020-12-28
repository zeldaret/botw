#include "Game/AI/Action/actionOpenItemCategory.h"

namespace uking::action {

OpenItemCategory::OpenItemCategory(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenItemCategory::~OpenItemCategory() = default;

bool OpenItemCategory::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenItemCategory::loadParams_() {
    getDynamicParam(&mCategory_d, "Category");
}

}  // namespace uking::action
