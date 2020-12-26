#include "Game/AI/Action/actionKokkoCreateDrop.h"

namespace uking::action {

KokkoCreateDrop::KokkoCreateDrop(const InitArg& arg) : KokkoCreateDropBase(arg) {}

KokkoCreateDrop::~KokkoCreateDrop() = default;

bool KokkoCreateDrop::init_(sead::Heap* heap) {
    return KokkoCreateDropBase::init_(heap);
}

void KokkoCreateDrop::enter_(ksys::act::ai::InlineParamPack* params) {
    KokkoCreateDropBase::enter_(params);
}

void KokkoCreateDrop::leave_() {
    KokkoCreateDropBase::leave_();
}

void KokkoCreateDrop::loadParams_() {
    KokkoCreateDropBase::loadParams_();
}

void KokkoCreateDrop::calc_() {
    KokkoCreateDropBase::calc_();
}

}  // namespace uking::action
