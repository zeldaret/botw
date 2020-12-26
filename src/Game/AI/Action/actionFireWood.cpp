#include "Game/AI/Action/actionFireWood.h"

namespace uking::action {

FireWood::FireWood(const InitArg& arg) : FireWoodBase(arg) {}

FireWood::~FireWood() = default;

bool FireWood::init_(sead::Heap* heap) {
    return FireWoodBase::init_(heap);
}

void FireWood::enter_(ksys::act::ai::InlineParamPack* params) {
    FireWoodBase::enter_(params);
}

void FireWood::leave_() {
    FireWoodBase::leave_();
}

void FireWood::loadParams_() {
    FireWoodBase::loadParams_();
    // FIXME: CALL _ZNK4ksys3act2ai6RootAi18getAITreeVariable2EPPbRKN4sead14SafeStringBaseIcEE @
    // 0x7100d66968
}

void FireWood::calc_() {
    FireWoodBase::calc_();
}

}  // namespace uking::action
