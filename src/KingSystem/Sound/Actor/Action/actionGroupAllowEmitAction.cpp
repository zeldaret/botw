#include "KingSystem/Sound/Actor/Action/actionGroupAllowEmitAction.h"

namespace ksys::snd {

GroupAllowEmitAction::GroupAllowEmitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GroupAllowEmitAction::~GroupAllowEmitAction() = default;

bool GroupAllowEmitAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GroupAllowEmitAction::loadParams_() {
    getDynamicParam(&mGroupName_d, "GroupName");
}

}  // namespace ksys::snd
