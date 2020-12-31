#include "Game/AI/AI/aiOctarockRootBase.h"

namespace uking::ai {

OctarockRootBase::OctarockRootBase(const InitArg& arg) : EnemyRoot(arg) {}

OctarockRootBase::~OctarockRootBase() = default;

bool OctarockRootBase::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void OctarockRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void OctarockRootBase::leave_() {
    EnemyRoot::leave_();
}

void OctarockRootBase::loadParams_() {
    EnemyRoot::loadParams_();
}

}  // namespace uking::ai
