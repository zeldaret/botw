#include "Game/AI/Action/actionEventAddGameDataIntAction.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

EventAddGameDataIntAction::EventAddGameDataIntAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventAddGameDataIntAction::~EventAddGameDataIntAction() = default;

bool EventAddGameDataIntAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAddGameDataIntAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);

    if (mGameDataIntSrcName_d.isEmpty() || mGameDataIntDstName_d.isEmpty()) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return;
    }

    mIsReady = true;
}

void EventAddGameDataIntAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAddGameDataIntAction::loadParams_() {
    getDynamicParam(&mIsSignInversion_d, "IsSignInversion");
    getDynamicParam(&mGameDataIntDstName_d, "GameDataIntDstName");
    getDynamicParam(&mGameDataIntSrcName_d, "GameDataIntSrcName");
}

void EventAddGameDataIntAction::calc_() {
    ksys::act::ai::Action::calc_();

    if (isFinished() || isFailed()) {
        return;
    }

    if (!mIsReady) {
        setFinished();
        mFlags.set(Flag::Changeable);
        return;
    }

    mIsReady = false;
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm == nullptr) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return;
    }

    s32 value = 0;
    if (gdm->getParam().get().getS32(&value, mGameDataIntSrcName_d)) {
        if (*mIsSignInversion_d) {
            value = -value;
        }
        gdm->incrementS32(value, mGameDataIntDstName_d);
    }
}

}  // namespace uking::action
