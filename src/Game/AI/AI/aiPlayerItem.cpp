#include "Game/AI/AI/aiPlayerItem.h"

namespace uking::ai {

PlayerItem::PlayerItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerItem::loadParams_() {}

}  // namespace uking::ai
