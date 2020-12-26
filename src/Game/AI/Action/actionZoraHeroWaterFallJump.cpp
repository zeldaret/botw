#include "Game/AI/Action/actionZoraHeroWaterFallJump.h"

namespace uking::action {

ZoraHeroWaterFallJump::ZoraHeroWaterFallJump(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ZoraHeroWaterFallJump::~ZoraHeroWaterFallJump() = default;

bool ZoraHeroWaterFallJump::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ZoraHeroWaterFallJump::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ZoraHeroWaterFallJump::leave_() {
    ksys::act::ai::Action::leave_();
}

void ZoraHeroWaterFallJump::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

void ZoraHeroWaterFallJump::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
