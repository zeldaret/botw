#include "KingSystem/ActorSystem/actAiActionBase.h"

namespace ksys::act::ai {

ActionBase::ActionBase(const InitArg& arg)
    : mActor{arg.actor}, mDefinitionIdx{u16(arg.def_idx)}, mRootIdx{u8(arg.root_idx)} {}

bool ActionBase::isFinished() const {
    return mFlags.isOn(Flag::Finished);
}

bool ActionBase::isFailed() const {
    return mFlags.isOn(Flag::Failed);
}

bool ActionBase::isFlag4Set() const {
    return mFlags.isOn(Flag::_4);
}

void ActionBase::setFinished() {
    mFlags.set(Flag::Finished);
    mFlags.reset(Flag::Failed);
}

void ActionBase::setFailed() {
    mFlags.set(Flag::Failed);
    mFlags.reset(Flag::Finished);
}

}  // namespace ksys::act::ai
