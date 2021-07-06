#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {

namespace {
BaseProcLink sDummyBaseProcLink;
}  // namespace

BaseProcLink& getDummyBaseProcLink() {
    return sDummyBaseProcLink;
}

const sead::SafeString& Actor::getProfile() const {
    return mActorParam->getProfile();
}

}  // namespace ksys::act
