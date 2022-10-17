#include "Game/AI/Action/actionKorokFlowerAppear.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

KorokFlowerAppear::KorokFlowerAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KorokFlowerAppear::~KorokFlowerAppear() = default;

bool KorokFlowerAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KorokFlowerAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);

    auto* main_body = mActor->getMainBody();
    auto* tgt_body = mActor->getTgtBody();
    if (main_body != nullptr && tgt_body != nullptr) {
        main_body->setContactNone();
        main_body->resetFlag200();
        tgt_body->setContactNone();
        tgt_body->resetFlag200();
    }
    mFlags.set(Flag::Changeable);
    setFinished();
}

void KorokFlowerAppear::leave_() {
    ksys::act::ai::Action::leave_();
}

void KorokFlowerAppear::loadParams_() {}

void KorokFlowerAppear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
