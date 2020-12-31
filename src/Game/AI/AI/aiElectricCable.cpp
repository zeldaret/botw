#include "Game/AI/AI/aiElectricCable.h"

namespace uking::ai {

ElectricCable::ElectricCable(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ElectricCable::~ElectricCable() = default;

bool ElectricCable::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ElectricCable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ElectricCable::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ElectricCable::loadParams_() {
    getMapUnitParam(&mIsDisplayOnUI_m, "IsDisplayOnUI");
}

}  // namespace uking::ai
