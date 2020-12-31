#include "Game/AI/AI/aiKeepBackSelect.h"

namespace uking::ai {

KeepBackSelect::KeepBackSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeepBackSelect::~KeepBackSelect() = default;

bool KeepBackSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KeepBackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KeepBackSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KeepBackSelect::loadParams_() {
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mBaseAxis_s, "BaseAxis");
    getStaticParam(&mBackAngle_s, "BackAngle");
    getStaticParam(&mXZOnly_s, "XZOnly");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mLocalOffset_s, "LocalOffset");
}

}  // namespace uking::ai
