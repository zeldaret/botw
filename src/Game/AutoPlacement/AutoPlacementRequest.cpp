#include "Game/AutoPlacement/AutoPlacementRequest.h"
#include "Game/AutoPlacement/AutoPlacement.h"
#include "KingSystem/ActorSystem/actActor.h"
namespace uking {
void AutoPlacementRequest::onActorEvent(ksys::act::Actor* actor, s32 event) {
    if (event == 1) {
        if (!mPlacement || mPlacement->mNearFlag == 0xff)
            return;
        if (mPlacement->_14 != mPlacementGeneration ||
            mPlacement->sub_7100650144(&mPlacement->mGroups[mGroupIndex], false))
            actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        return;
    }
    if (event != 0)
        return;
    if (mActor != actor) {
        sead::FixedSafeString<1024> description;
        if (mActor)
            description.format("保持 %p:%s    ", mActor, mActor->getName().cstr());
        else
            description.format("保持 なし    ");
    }
    if (mPlacement && mPlacement->mNearFlag != 0xff && mPlacement->_14 == mPlacementGeneration) {
        auto& group = mPlacement->mGroups[mGroupIndex];
        if (actor && actor->isAutoPlacementActorReady())
            group._80.decrement();
        else
            ++group._24;
    }
    mActor = nullptr;
    mPlacement = nullptr;
}
}  // namespace uking
namespace ksys::act {
bool Actor::isAutoPlacementActorReady() const {
    return checkFlag(ActorFlag::_a) && !getActorFlags2().isOn(ActorFlag2::_8000);
}
}  // namespace ksys::act
