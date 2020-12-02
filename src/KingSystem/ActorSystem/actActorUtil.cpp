#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/resResourceActorLink.h"

namespace ksys::act {

bool hasTag(Actor* actor, const sead::SafeString& tag) {
    if (!actor)
        return false;
    return actor->getParam()->getRes().mActorLink->hasTag(tag.cstr());
}

bool hasTag(const sead::SafeString& actor, const sead::SafeString& tag) {
    auto* data = InfoData::instance();
    return data && data->hasTag(actor.cstr(), tag.cstr());
}

}  // namespace ksys::act
