#include "Game/AI/Action/actionEventAddGameDataToRupeeAction.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::action {

EventAddGameDataToRupeeAction::EventAddGameDataToRupeeAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventAddGameDataToRupeeAction::~EventAddGameDataToRupeeAction() = default;

bool EventAddGameDataToRupeeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAddGameDataToRupeeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);

    s32 val = 0;
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm->getParam().get().getS32(&val, mGameDataIntAddValueName_d)) {
        ksys::ui::initRupeeCounter();
        return;
    }

    if (*mIsSignInversion_d) {
        val = -val;
    }
    gdm->incrementS32(val, "CurrentRupee");
    ksys::ui::initRupeeCounter();
}

void EventAddGameDataToRupeeAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAddGameDataToRupeeAction::loadParams_() {
    getDynamicParam(&mIsSignInversion_d, "IsSignInversion");
    getDynamicParam(&mGameDataIntAddValueName_d, "GameDataIntAddValueName");
}

void EventAddGameDataToRupeeAction::calc_() {
    ksys::act::ai::Action::calc_();

    if (!ksys::ui::isRupeeCounterActive()) {
        setFinished();
    }
}

}  // namespace uking::action
