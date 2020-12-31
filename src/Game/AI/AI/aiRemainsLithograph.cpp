#include "Game/AI/AI/aiRemainsLithograph.h"

namespace uking::ai {

RemainsLithograph::RemainsLithograph(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsLithograph::~RemainsLithograph() = default;

bool RemainsLithograph::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsLithograph::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsLithograph::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsLithograph::loadParams_() {}

}  // namespace uking::ai
