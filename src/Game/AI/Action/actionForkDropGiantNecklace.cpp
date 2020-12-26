#include "Game/AI/Action/actionForkDropGiantNecklace.h"

namespace uking::action {

ForkDropGiantNecklace::ForkDropGiantNecklace(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDropGiantNecklace::~ForkDropGiantNecklace() = default;

bool ForkDropGiantNecklace::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkDropGiantNecklace::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkDropGiantNecklace::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkDropGiantNecklace::loadParams_() {
    getAITreeVariable(&mGiantNecklaceUnit_a, "GiantNecklaceUnit");
}

void ForkDropGiantNecklace::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
