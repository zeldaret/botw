#include "Game/AI/AI/aiClusterRenderCheckTag.h"

namespace uking::ai {

ClusterRenderCheckTag::ClusterRenderCheckTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ClusterRenderCheckTag::~ClusterRenderCheckTag() = default;

bool ClusterRenderCheckTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ClusterRenderCheckTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ClusterRenderCheckTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ClusterRenderCheckTag::loadParams_() {}

}  // namespace uking::ai
