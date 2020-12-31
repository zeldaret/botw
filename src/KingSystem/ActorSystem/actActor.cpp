#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"

namespace ksys::act {

const sead::SafeString& Actor::getProfile() const {
    return mActorParam->getProfile();
}

}  // namespace ksys::act
