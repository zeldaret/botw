#include "Game/AI/AI/aiSwitchElectric.h"

namespace uking::ai {

SwitchElectric::SwitchElectric(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool SwitchElectric::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchElectric::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwitchElectric::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchElectric::loadParams_() {
    getStaticParam(&mElecReq_s, "ElecReq");
    getStaticParam(&mVolReq_s, "VolReq");
}

}  // namespace uking::ai
