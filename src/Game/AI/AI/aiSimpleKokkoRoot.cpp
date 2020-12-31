#include "Game/AI/AI/aiSimpleKokkoRoot.h"

namespace uking::ai {

SimpleKokkoRoot::SimpleKokkoRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleKokkoRoot::~SimpleKokkoRoot() = default;

bool SimpleKokkoRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleKokkoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SimpleKokkoRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleKokkoRoot::loadParams_() {
    getStaticParam(&mAliveTime_s, "AliveTime");
    getAITreeVariable(&mAttackTargetActorLink_a, "AttackTargetActorLink");
}

}  // namespace uking::ai
