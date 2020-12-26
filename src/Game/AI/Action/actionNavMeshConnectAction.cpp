#include "Game/AI/Action/actionNavMeshConnectAction.h"

namespace uking::action {

NavMeshConnectAction::NavMeshConnectAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NavMeshConnectAction::~NavMeshConnectAction() = default;

bool NavMeshConnectAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NavMeshConnectAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NavMeshConnectAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void NavMeshConnectAction::loadParams_() {}

void NavMeshConnectAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
