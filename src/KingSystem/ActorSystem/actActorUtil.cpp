#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/resResourceActorLink.h"

namespace ksys::act {

static ActorConstDataAccess getAccessor(BaseProcLink* link) {
    ActorConstDataAccess accessor;
    acquireActor(link, &accessor);
    return accessor;
}

bool hasTag(Actor* actor, const sead::SafeString& tag) {
    if (!actor)
        return false;
    return actor->getParam()->getRes().mActorLink->hasTag(tag.cstr());
}

bool hasTag(BaseProcLink* link, const sead::SafeString& tag) {
    return hasTag(getAccessor(link), tag);
}

bool hasTag(const ActorConstDataAccess& accessor, const sead::SafeString& tag) {
    return accessor.hasTag(tag.cstr());
}

bool hasTag(const sead::SafeString& actor, const sead::SafeString& tag) {
    auto* data = InfoData::instance();
    return data && data->hasTag(actor.cstr(), tag.cstr());
}

bool hasTag(Actor* actor, u32 tag) {
    return actor && actor->getParam()->getRes().mActorLink->hasTag(tag);
}

bool hasTag(BaseProcLink* link, u32 tag) {
    return hasTag(getAccessor(link), tag);
}

bool hasTag(const ActorConstDataAccess& accessor, u32 tag) {
    return accessor.hasTag(tag);
}

bool hasTag(const sead::SafeString& actor, u32 tag) {
    auto* data = InfoData::instance();
    return data && data->hasTag(actor.cstr(), tag);
}

bool hasOneTagAtLeast(Actor* actor, const sead::SafeString& tags) {
    sead::FixedSafeString<32> tag;
    for (auto it = tags.tokenBegin(","); tags.tokenEnd(",") != it; ++it) {
        it.get(&tag);
        if (hasTag(actor, tag))
            return true;
    }
    return false;
}

bool hasOneTagAtLeast(BaseProcLink* link, const sead::SafeString& tags) {
    sead::FixedSafeString<32> tag;
    for (auto it = tags.tokenBegin(","); tags.tokenEnd(",") != it; ++it) {
        it.get(&tag);
        if (hasTag(link, tag))
            return true;
    }
    return false;
}

bool act::hasOneTagAtLeast(const ActorConstDataAccess& accessor, const sead::SafeString& tags) {
    sead::FixedSafeString<32> tag;
    for (auto it = tags.tokenBegin(","); tags.tokenEnd(",") != it; ++it) {
        it.get(&tag);
        if (hasTag(accessor, tag))
            return true;
    }
    return false;
}

}  // namespace ksys::act
