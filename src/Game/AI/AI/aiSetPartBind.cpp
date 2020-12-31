#include "Game/AI/AI/aiSetPartBind.h"

namespace uking::ai {

SetPartBind::SetPartBind(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SetPartBind::~SetPartBind() = default;

void SetPartBind::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SetPartBind::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetPartBind::loadParams_() {
    getStaticParam(&mBaseNodeName_s, "BaseNodeName");
    getStaticParam(&mPartialNodeName_s, "PartialNodeName");
}

}  // namespace uking::ai
