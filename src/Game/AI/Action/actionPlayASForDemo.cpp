#include "Game/AI/Action/actionPlayASForDemo.h"

namespace uking::action {

PlayASForDemo::PlayASForDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayASForDemo::~PlayASForDemo() = default;

bool PlayASForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayASForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayASForDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayASForDemo::loadParams_() {
    getStaticParam(&mAnimeDrivenSettings_s, "AnimeDrivenSettings");
    getDynamicParam(&mTargetIndex_d, "TargetIndex");
    getDynamicParam(&mSeqBank_d, "SeqBank");
    getDynamicParam(&mIsEnabledAnimeDriven_d, "IsEnabledAnimeDriven");
    getDynamicParam(&mClothWarpMode_d, "ClothWarpMode");
    getDynamicParam(&mMorphingFrame_d, "MorphingFrame");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mASName_d, "ASName");
}

void PlayASForDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
