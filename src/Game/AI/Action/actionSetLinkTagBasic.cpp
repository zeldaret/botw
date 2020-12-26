#include "Game/AI/Action/actionSetLinkTagBasic.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetLinkTagBasic::SetLinkTagBasic(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetLinkTagBasic::~SetLinkTagBasic() = default;

bool SetLinkTagBasic::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetLinkTagBasic::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);

    if (*mIsOn_s)
        mActor->emitBasicSigOn();
    else
        mActor->emitBasicSigOff();

    setFinished();
}

void SetLinkTagBasic::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetLinkTagBasic::loadParams_() {
    getStaticParam(&mIsOn_s, "IsOn");
}

void SetLinkTagBasic::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
