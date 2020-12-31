#include "Game/AI/AI/aiDuckRoot.h"

namespace uking::ai {

DuckRoot::DuckRoot(const InitArg& arg) : PreyRoot(arg) {}

DuckRoot::~DuckRoot() = default;

bool DuckRoot::init_(sead::Heap* heap) {
    return PreyRoot::init_(heap);
}

void DuckRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyRoot::enter_(params);
}

void DuckRoot::leave_() {
    PreyRoot::leave_();
}

void DuckRoot::loadParams_() {
    PreyRoot::loadParams_();
}

}  // namespace uking::ai
