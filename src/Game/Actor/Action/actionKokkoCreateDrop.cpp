#include "Game/Actor/Action/actionKokkoCreateDrop.h"

namespace uking::action {

KokkoCreateDrop::KokkoCreateDrop(const InitArg& arg) : CreateDropBase(arg) {}

KokkoCreateDrop::~KokkoCreateDrop() = default;

bool KokkoCreateDrop::init_(sead::Heap* heap) {
    return CreateDropBase::init_(heap);
}

void KokkoCreateDrop::enter_(ksys::act::ai::InlineParamPack* params) {
    CreateDropBase::enter_(params);
}

void KokkoCreateDrop::leave_() {
    CreateDropBase::leave_();
}

void KokkoCreateDrop::loadParams_() {
    CreateDropBase::loadParams_();
}

void KokkoCreateDrop::calc_() {
    CreateDropBase::calc_();
}

}  // namespace uking::action
