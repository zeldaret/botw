#include "Game/AI/Action/actionKorokFlowerWait.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

KorokFlowerWait::KorokFlowerWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KorokFlowerWait::~KorokFlowerWait() = default;

bool KorokFlowerWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KorokFlowerWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KorokFlowerWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void KorokFlowerWait::loadParams_() {}

void KorokFlowerWait::calc_() {
    if (mActor->checkBasicSig()) {
        mFlags.set(Flag::Changeable);
        setFinished();
    }
}

}  // namespace uking::action
