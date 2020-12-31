#include "Game/AI/AI/aiLifeChangeDemoCaller.h"

namespace uking::ai {

LifeChangeDemoCaller::LifeChangeDemoCaller(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LifeChangeDemoCaller::~LifeChangeDemoCaller() = default;

bool LifeChangeDemoCaller::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LifeChangeDemoCaller::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LifeChangeDemoCaller::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LifeChangeDemoCaller::loadParams_() {
    getStaticParam(&mLifeRatio_s, "LifeRatio");
    getStaticParam(&mOnlyOnce_s, "OnlyOnce");
    getStaticParam(&mIsIgnorePlayerLand_s, "IsIgnorePlayerLand");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mDemoEntryPoint_s, "DemoEntryPoint");
}

}  // namespace uking::ai
