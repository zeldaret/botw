#include "Game/AI/Action/actionForkIgniteCarriedActor.h"

namespace uking::action {

ForkIgniteCarriedActor::ForkIgniteCarriedActor(const InitArg& arg) : Fork(arg) {}

ForkIgniteCarriedActor::~ForkIgniteCarriedActor() = default;

bool ForkIgniteCarriedActor::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkIgniteCarriedActor::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkIgniteCarriedActor::leave_() {
    Fork::leave_();
}

void ForkIgniteCarriedActor::loadParams_() {
    Fork::loadParams_();
}

void ForkIgniteCarriedActor::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
