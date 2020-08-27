#include "KingSystem/ActorSystem/actAiClass.h"

namespace ksys::act::ai {

ActionBase::ActionBase(const ClassArg& arg)
    : mActor{arg.actor}, mDefinitionIdx{u16(arg.definitionIdx)}, mRootIdx{u8(arg.rootIdx)} {}

bool ActionBase::isFinished() {
    return mStatus.isOn(Status::Finished);
}

bool ActionBase::isFailed() {
    return mStatus.isOn(Status::Failed);
}

void ActionBase::setFinished() {
    mStatus.set(Status::Finished);
    mStatus.reset(Status::Failed);
}

void ActionBase::setFailed() {
    mStatus.set(Status::Failed);
    mStatus.reset(Status::Finished);
}

}  // namespace ksys::act::ai
