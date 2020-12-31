#include "Game/AI/AI/aiFldObjIvyBurnRoot.h"

namespace uking::ai {

FldObjIvyBurnRoot::FldObjIvyBurnRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FldObjIvyBurnRoot::~FldObjIvyBurnRoot() = default;

bool FldObjIvyBurnRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FldObjIvyBurnRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FldObjIvyBurnRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FldObjIvyBurnRoot::loadParams_() {}

}  // namespace uking::ai
