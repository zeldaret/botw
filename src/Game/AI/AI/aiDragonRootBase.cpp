#include "Game/AI/AI/aiDragonRootBase.h"

namespace uking::ai {

DragonRootBase::DragonRootBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DragonRootBase::~DragonRootBase() = default;

bool DragonRootBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DragonRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DragonRootBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DragonRootBase::loadParams_() {}

}  // namespace uking::ai
