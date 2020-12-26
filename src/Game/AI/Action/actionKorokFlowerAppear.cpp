#include "Game/AI/Action/actionKorokFlowerAppear.h"

namespace uking::action {

KorokFlowerAppear::KorokFlowerAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KorokFlowerAppear::~KorokFlowerAppear() = default;

bool KorokFlowerAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KorokFlowerAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KorokFlowerAppear::leave_() {
    ksys::act::ai::Action::leave_();
}

void KorokFlowerAppear::loadParams_() {}

void KorokFlowerAppear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
