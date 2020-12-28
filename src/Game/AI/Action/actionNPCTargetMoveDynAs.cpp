#include "Game/AI/Action/actionNPCTargetMoveDynAs.h"

namespace uking::action {

NPCTargetMoveDynAs::NPCTargetMoveDynAs(const InitArg& arg) : NPCTargetMove(arg) {}

NPCTargetMoveDynAs::~NPCTargetMoveDynAs() = default;

void NPCTargetMoveDynAs::loadParams_() {
    NPCTargetMove::loadParams_();
    getDynamicParam(&mDynASKeyName_d, "DynASKeyName");
}

}  // namespace uking::action
