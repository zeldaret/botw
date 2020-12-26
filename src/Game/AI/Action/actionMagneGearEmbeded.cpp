#include "Game/AI/Action/actionMagneGearEmbeded.h"

namespace uking::action {

MagneGearEmbeded::MagneGearEmbeded(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MagneGearEmbeded::~MagneGearEmbeded() = default;

bool MagneGearEmbeded::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MagneGearEmbeded::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MagneGearEmbeded::leave_() {
    ksys::act::ai::Action::leave_();
}

void MagneGearEmbeded::loadParams_() {}

void MagneGearEmbeded::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
