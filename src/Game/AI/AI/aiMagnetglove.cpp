#include "Game/AI/AI/aiMagnetglove.h"

namespace uking::ai {

Magnetglove::Magnetglove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

Magnetglove::~Magnetglove() = default;

bool Magnetglove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void Magnetglove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void Magnetglove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void Magnetglove::loadParams_() {}

}  // namespace uking::ai
