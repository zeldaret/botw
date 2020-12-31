#include "Game/AI/AI/aiAddDemoCall.h"

namespace uking::ai {

AddDemoCall::AddDemoCall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddDemoCall::~AddDemoCall() = default;

bool AddDemoCall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddDemoCall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AddDemoCall::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddDemoCall::loadParams_() {
    getStaticParam(&mOnlyOne_s, "OnlyOne");
    getStaticParam(&mIsBroadCastOnlyOne_s, "IsBroadCastOnlyOne");
    getStaticParam(&mEntryPoint_s, "EntryPoint");
    getStaticParam(&mDemoName_s, "DemoName");
}

}  // namespace uking::ai
