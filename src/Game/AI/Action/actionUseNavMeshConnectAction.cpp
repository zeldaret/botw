#include "Game/AI/Action/actionUseNavMeshConnectAction.h"

namespace uking::action {

UseNavMeshConnectAction::UseNavMeshConnectAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

UseNavMeshConnectAction::~UseNavMeshConnectAction() = default;

bool UseNavMeshConnectAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void UseNavMeshConnectAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void UseNavMeshConnectAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void UseNavMeshConnectAction::loadParams_() {}

void UseNavMeshConnectAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
