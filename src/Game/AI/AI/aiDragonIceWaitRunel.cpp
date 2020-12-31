#include "Game/AI/AI/aiDragonIceWaitRunel.h"

namespace uking::ai {

DragonIceWaitRunel::DragonIceWaitRunel(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DragonIceWaitRunel::~DragonIceWaitRunel() = default;

bool DragonIceWaitRunel::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DragonIceWaitRunel::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DragonIceWaitRunel::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DragonIceWaitRunel::loadParams_() {}

}  // namespace uking::ai
