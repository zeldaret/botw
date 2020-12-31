#include "Game/AI/AI/aiMagneShaftRoot.h"

namespace uking::ai {

MagneShaftRoot::MagneShaftRoot(const InitArg& arg) : MagneShaftRootBase(arg) {}

MagneShaftRoot::~MagneShaftRoot() = default;

bool MagneShaftRoot::init_(sead::Heap* heap) {
    return MagneShaftRootBase::init_(heap);
}

void MagneShaftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    MagneShaftRootBase::enter_(params);
}

void MagneShaftRoot::leave_() {
    MagneShaftRootBase::leave_();
}

void MagneShaftRoot::loadParams_() {
    MagneShaftRootBase::loadParams_();
}

}  // namespace uking::ai
