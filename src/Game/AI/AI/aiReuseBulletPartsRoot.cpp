#include "Game/AI/AI/aiReuseBulletPartsRoot.h"

namespace uking::ai {

ReuseBulletPartsRoot::ReuseBulletPartsRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReuseBulletPartsRoot::~ReuseBulletPartsRoot() = default;

bool ReuseBulletPartsRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReuseBulletPartsRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ReuseBulletPartsRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReuseBulletPartsRoot::loadParams_() {}

}  // namespace uking::ai
