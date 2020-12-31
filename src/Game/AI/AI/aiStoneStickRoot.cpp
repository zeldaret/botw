#include "Game/AI/AI/aiStoneStickRoot.h"

namespace uking::ai {

StoneStickRoot::StoneStickRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StoneStickRoot::~StoneStickRoot() = default;

bool StoneStickRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StoneStickRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StoneStickRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StoneStickRoot::loadParams_() {
    getStaticParam(&mFixPoint_s, "FixPoint");
}

}  // namespace uking::ai
