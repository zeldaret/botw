#include "Game/AI/AI/aiMotorcycleRootBase.h"

namespace uking::ai {

MotorcycleRootBase::MotorcycleRootBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MotorcycleRootBase::~MotorcycleRootBase() = default;

bool MotorcycleRootBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MotorcycleRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MotorcycleRootBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MotorcycleRootBase::loadParams_() {}

}  // namespace uking::ai
