#include "Game/AI/AI/aiVehicleSelector.h"

namespace uking::ai {

VehicleSelector::VehicleSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

VehicleSelector::~VehicleSelector() = default;

void VehicleSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

}  // namespace uking::ai
