#include "Game/Actor/Action/actionFireWood.h"

namespace uking::action {

FireWood::FireWood(const InitArg& arg) : FireBurnBase(arg) {}

FireWood::~FireWood() = default;

bool FireWood::init_(sead::Heap* heap) {
    return FireBurnBase::init_(heap);
}

void FireWood::enter_(ksys::act::ai::InlineParamPack* params) {
    FireBurnBase::enter_(params);
}

void FireWood::leave_() {
    FireBurnBase::leave_();
}

void FireWood::loadParams_() {
    FireBurnBase::loadParams_();
    // FIXME: CALL _ZNK4ksys3act2ai6RootAi18getAITreeVariable2EPPbRKN4sead14SafeStringBaseIcEE @
    // 0x7100d66968
}

void FireWood::calc_() {
    FireBurnBase::calc_();
}

}  // namespace uking::action
