#include "KingSystem/ActorSystem/actInfoData.h"
#include <codec/seadHashCRC32.h>
#include <math/seadMathNumbers.h>
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Byaml/ByamlArrayIter.h"
#include "KingSystem/Utils/Byaml/ByamlData.h"
#include "KingSystem/Utils/Byaml/ByamlHashIter.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(InfoData)

InfoData::~InfoData() {
    if (mHashesIter)
        delete mHashesIter;

    if (mActorsIter)
        delete mActorsIter;

    if (mRootIter)
        delete mRootIter;

    mRootIter = nullptr;
    mHashesIter = nullptr;
    mActorsIter = nullptr;
    mHashesBytes = nullptr;
    mHashes = nullptr;
    mActorsBytes = nullptr;
    mActorOffsets = nullptr;
}

void InfoData::init(u8* data, sead::Heap* heap, sead::Heap* debug_heap) {
    mRootIter = new (heap) al::ByamlIter(data);
    mHashesIter = new (heap) al::ByamlIter();
    mActorsIter = new (heap) al::ByamlIter();

    if (debug_heap) {
        mDebugEntries = new (debug_heap) DebugEntry[NumDebugEntries];
        for (s32 i = 0; i != NumDebugEntries; ++i)
            mDebugEntries[i].used = false;
    } else {
        mDebugEntries = nullptr;
    }

    if (mRootIter->tryGetIterByKey(mHashesIter, "Hashes")) {
        mHashesBytes = mHashesIter->getData();
        mHashes = al::ByamlArrayIter(mHashesIter->getRootNode()).getDataTable();
    }

    if (mRootIter->tryGetIterByKey(mActorsIter, "Actors")) {
        mActorsBytes = mActorsIter->getData();
        mActorOffsets = al::ByamlArrayIter(mActorsIter->getRootNode()).getDataTable();
    }

    mNumActors = mActorsIter->getSize();
    _88 = 0;
    mDebugHeap = debug_heap;
    mTagsIdx = mRootIter->getKeyIndex("tags");
    mProfileIdx = mRootIter->getKeyIndex("profile");
    mInvalidWeathersIdx = mRootIter->getKeyIndex("invalidWeathers");
    mInvalidTimesIdx = mRootIter->getKeyIndex("invalidTimes");
    mNameIdx = mRootIter->getKeyIndex("name");
    mSystemSameGroupActorNameIdx = mRootIter->getKeyIndex("systemSameGroupActorName");
}

bool InfoData::getActorIter(al::ByamlIter* iter, const char* actor, bool x) const {
    const u32 hash = sead::HashCRC32::calcStringHash(actor);

    // Perform a binary search.
    s32 a = 0;
    s32 b = mNumActors;
    while (a < b) {
        const s32 idx = (a + b) / 2;
        const u32 hash_i = mHashes[idx];

        if (hash_i == hash) {
            *iter = al::ByamlIter(mActorsBytes, mActorsBytes + mActorOffsets[idx]);
            return true;
        }

        if (hash_i >= hash)
            b = idx;
        else
            a = idx + 1;
    }

    if (x)
        static_cast<void>(logFailure(actor));

    return false;
}

void InfoData::getRecipeInfo(const char* actor, InfoData::RecipeInfo& info) const {
    al::ByamlIter iter;
    if (getActorIter(&iter, actor)) {
        info.num_items = iter.getIntByKey("normal0StuffNum");

        info.items[0].name = iter.getStringByKey("normal0ItemName01");
        info.items[0].num = iter.getIntByKey("normal0ItemNum01");

        info.items[1].name = iter.getStringByKey("normal0ItemName02");
        info.items[1].num = iter.getIntByKey("normal0ItemNum02");

        info.items[2].name = iter.getStringByKey("normal0ItemName03");
        info.items[2].num = iter.getIntByKey("normal0ItemNum03");

    } else {
        info.num_items = 0;

        info.items[0].name = sead::SafeString::cEmptyString;
        info.items[0].num = 0;

        info.items[1].name = sead::SafeString::cEmptyString;
        info.items[1].num = 0;

        info.items[2].name = sead::SafeString::cEmptyString;
        info.items[2].num = 0;
    }
}

s32 InfoData::getIntByKey(const al::ByamlIter& iter, const char* key, s32 default_) {
    s32 value;
    return iter.tryGetIntByKey(&value, key) ? value : default_;
}

const char* InfoData::getStringByKey(const al::ByamlIter& iter, const char* key,
                                     const sead::SafeString& default_) {
    const char* value;
    return iter.tryGetStringByKey(&value, key) ? value : default_.cstr();
}

[[gnu::noinline]] static InfoData::Locator::Type
getLocatorTypeFromStr(const sead::SafeString& type) {
    static constexpr const char* types[] = {"Trunk",  "Branch",   "GlowStone",
                                            "OnTree", "MagnePos", "StopTimerPos"};
    for (s32 i = 0; i < s32(std::size(types)); ++i) {
        if (type == types[i])
            return InfoData::Locator::Type(i);
    }
    return InfoData::Locator::Type::Invalid;
}

void InfoData::getLocators(const char* actor, Locators& info) const {
    info.num = 0;

    al::ByamlIter iter;
    if (!getActorIter(&iter, actor))
        return;

    al::ByamlIter iter_locators;
    if (!iter.tryGetIterByKey(&iter_locators, "locators"))
        return;

    info.num = iter_locators.getSize();
    for (s32 i = 0; i < info.num; ++i) {
        al::ByamlIter it;
        if (!iter_locators.tryGetIterByIndex(&it, i))
            continue;

        const char* type_str{};
        auto& locator = info.locators[i];

        it.tryGetFloatByKey(&locator.pos.x, "pos_x");
        it.tryGetFloatByKey(&locator.pos.y, "pos_y");
        it.tryGetFloatByKey(&locator.pos.z, "pos_z");

        it.tryGetFloatByKey(&locator.rot.x, "rot_x");
        it.tryGetFloatByKey(&locator.rot.y, "rot_y");
        it.tryGetFloatByKey(&locator.rot.z, "rot_z");

        it.tryGetStringByKey(&type_str, "type");
        locator.type = type_str ? getLocatorTypeFromStr(type_str) : Locator::Type::Invalid;

        locator.rot *= 2 * sead::numbers::pi / 360.0;
    }
}

void InfoData::getHomeAreas(const char* actor, HomeAreas& info) const {
    info.names.fill("");

    al::ByamlIter iter;
    if (!getActorIter(&iter, actor))
        return;

    al::ByamlIter home_area;
    if (!iter.tryGetIterByKey(&home_area, "homeArea"))
        return;

    for (s32 i = 0, n = home_area.getSize(); i < info.names.size() && i < n; ++i) {
        al::ByamlIter it;
        if (home_area.tryGetIterByIndex(&it, i))
            it.tryGetStringByKey(&info.names[i], "name");
    }
}

const char* InfoData::getSameGroupActorName(const char* actor) const {
    al::ByamlIter iter;
    return [&] {
        if (getActorIter(&iter, actor, false)) {
            al::ByamlHashIter hash_iter{iter.getRootNode()};
            al::ByamlData data;
            if (hash_iter.getDataByKey(&data, mSystemSameGroupActorNameIdx)) {
                const char* name;
                if (iter.tryConvertString(&name, &data))
                    return name;
            }
        }
        return sead::SafeString::cEmptyString.cstr();
    }();
}

const char* InfoData::getString(const char* actor, const char* key,
                                const sead::SafeString& default_, bool x) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor, x))
        return default_.cstr();

    return getStringByKey(iter, key, default_);
}

const char* InfoData::getSLinkUser(const char* actor) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor))
        return "Dummy";

    return getStringByKey(iter, "slink", "Dummy");
}

bool InfoData::getSLinkAndELinkUsers(const char* actor, const char** elink,
                                     const char** slink) const {
    al::ByamlIter iter;
    if (getActorIter(&iter, actor)) {
        *elink = getStringByKey(iter, "elink", "Dummy");
        *slink = getStringByKey(iter, "slink", "Dummy");
        return true;
    }
    *elink = "Dummy";
    *slink = "Dummy";
    return false;
}

const char* InfoData::getXLinkUser(const char* actor) const {
    return getString(actor, "xlink", "Dummy");
}

bool InfoData::getActorProfile(const char** profile, const char* actor) const {
    al::ByamlIter iter;
    if (getActorIter(&iter, actor)) {
        al::ByamlHashIter hash_iter{iter.getRootNode()};
        al::ByamlData data;
        if (hash_iter.getDataByKey(&data, mProfileIdx))
            return iter.tryConvertString(profile, &data);
    }
    *profile = "Dummy";
    return false;
}

s32 InfoData::getInt(const char* actor, const char* key, s32 default_, bool x) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor, x))
        return default_;

    return getIntByKey(iter, key, default_);
}

f32 InfoData::getFloat(const char* actor, const char* key, f32 default_, bool x) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor, x))
        return default_;

    return getFloatByKey(iter, key, default_);
}

bool InfoData::getBool(const char* actor, const char* key, bool default_, bool x) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor, x))
        return default_;

    return getBoolByKey(iter, key, default_);
}

f32 InfoData::getFloatByKey(const al::ByamlIter& iter, const char* key, f32 default_) {
    f32 value;
    return iter.tryGetFloatByKey(&value, key) ? value : default_;
}

bool InfoData::getBoolByKey(const al::ByamlIter& iter, const char* key, bool default_) {
    bool value;
    return iter.tryGetBoolByKey(&value, key) ? value != 0 : default_;
}

f32 InfoData::getScale(const char* actor) const {
    return getFloat(actor, "actorScale", 1.0);
}

}  // namespace ksys::act
