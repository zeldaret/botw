#include "Game/AI/Action/actionAirWallAction.h"

namespace uking::action {

AirWallAction::AirWallAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void AirWallAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
