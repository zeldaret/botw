#include "Game/AI/AI/aiMagneShaftRootBase.h"

namespace uking::ai {

MagneShaftRootBase::MagneShaftRootBase(const InitArg& arg) : MagneStickRoot(arg) {}

MagneShaftRootBase::~MagneShaftRootBase() = default;

bool MagneShaftRootBase::init_(sead::Heap* heap) {
    return MagneStickRoot::init_(heap);
}

void MagneShaftRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    MagneStickRoot::enter_(params);
}

void MagneShaftRootBase::leave_() {
    MagneStickRoot::leave_();
}

void MagneShaftRootBase::loadParams_() {
    MagneStickRoot::loadParams_();
}

}  // namespace uking::ai
