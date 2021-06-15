#include "KingSystem/ActorSystem/actInfoData.h"
#include <KingSystem/Resource/resModelResourceDivide.h>
#include <codec/seadHashCRC32.h>
#include <math/seadMathNumbers.h>
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/Event/evtEvent.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Resource/Actor/resResourceModelList.h"
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

void InfoData::getModelInfo(const char* actor, InfoData::ModelInfo& info) const {
    const char** ptr;
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor)) {
        static_cast<void>(logFailure(actor));
        ptr = &info.bfres;
    } else {
        const auto getFloat = [&](f32* value, const char* key, float default_) {
            if (!iter.tryGetFloatByKey(value, key))
                *value = default_;
        };

        getFloat(&info.baseScale.x, "baseScaleX", 1.0);
        getFloat(&info.baseScale.y, "baseScaleY", 1.0);
        getFloat(&info.baseScale.z, "baseScaleZ", 1.0);

        getFloat(&info.addColor.r, "addColorR", 0.0);
        getFloat(&info.addColor.g, "addColorG", 0.0);
        getFloat(&info.addColor.b, "addColorB", 0.0);
        getFloat(&info.addColor.a, "addColorA", 0.0);

        getFloat(&info.mulColor.r, "mulColorR", 1.0);
        getFloat(&info.mulColor.g, "mulColorG", 1.0);
        getFloat(&info.mulColor.b, "mulColorB", 1.0);
        getFloat(&info.mulColor.a, "mulColorA", 1.0);

        if (!iter.tryGetStringByKey(&info.bfres, "bfres"))
            info.bfres = nullptr;

        if (!iter.tryGetStringByKey(&info.mainModel, "mainModel"))
            info.mainModel = nullptr;

        if (!info.bfres)
            return;

        if (info.mainModel) {
            const char* model_resource =
                res::ModelResourceDivide::instance()->getModelResource(info.bfres, info.mainModel);
            if (model_resource)
                info.bfres = model_resource;
        }

        if (!info.bfres || sead::SafeString(info.bfres) != "dammy_data")
            return;

        info.bfres = nullptr;
        ptr = &info.mainModel;
    }

    *ptr = nullptr;
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

bool InfoData::logFailure(const sead::SafeString& actor_name) const {
#ifdef MATCHING_HACK_NX_CLANG
    // This is required to prevent LLVM from detecting that 'this' is unused
    // and optimizing out the passing of 'this' in callers.
    __builtin_assume(mActorsBytes);
#endif

    auto* event = evt::Manager::instance()->getActiveEvent();
    if (event && event->hasFlag(evt::Event::Flag::_80000000000))
        return false;

    if (!ActorCreator::instance()->get5a())
        return false;

    if (ActorDebug::instance() && ActorDebug::instance()->hasFlag(ActorDebug::Flag::_10000000))
        return false;

    if (actor_name.startsWith("MergedGrudge"))
        return false;

    if (actor_name.startsWith("Armor_50"))
        return false;

    if (actor_name == "Weapon_Sword_DemoCheck")
        return false;

    return true;
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

s32 InfoData::getIntByKey(const al::ByamlIter& iter, const char* key, s32 default_, bool) {
    s32 value;
    return iter.tryGetIntByKey(&value, key) ? value : default_;
}

const char* InfoData::getStringByKey(const al::ByamlIter& iter, const char* key,
                                     const sead::SafeString& default_, bool) {
    const char* value;
    return iter.tryGetStringByKey(&value, key) ? value : default_.cstr();
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
        locator.type =
            type_str ? res::ModelList::getLocatorTypeFromStr(type_str) : Locator::Type::Invalid;

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

void InfoData::getInvalidLifeConditions(const char* actor, InvalidLifeConditions& info) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor))
        return;

    al::ByamlData data;
    al::ByamlHashIter hash_iter{iter.getRootNode()};

    if (hash_iter.getDataByKey(&data, mInvalidTimesIdx)) {
        al::ByamlIter it{iter.getData(), iter.getData() + data.getValue()};
        for (s32 i = 0, n = it.getSize(); i < n; ++i) {
            const char* time = nullptr;
            if (!it.tryGetStringByIndex(&time, i))
                continue;

            info.times[info.num_times] = time;
            ++info.num_times;
        }
    }

    if (hash_iter.getDataByKey(&data, mInvalidWeathersIdx)) {
        al::ByamlIter it{iter.getData(), iter.getData() + data.getValue()};
        for (s32 i = 0, n = it.getSize(); i < n; ++i) {
            const char* weather = nullptr;
            if (!it.tryGetStringByIndex(&weather, i))
                continue;

            info.weathers[info.num_weathers] = weather;
            ++info.num_weathers;
        }
    }
}

bool InfoData::hasTag(const char* actor, const char* tag) const {
    al::ByamlIter iter;
    return getActorIter(&iter, actor) && hasTag(iter, sead::HashCRC32::calcStringHash(tag));
}

bool InfoData::hasTag(const al::ByamlIter& actor_iter, u32 tag) const {
    al::ByamlHashIter tags_iter{actor_iter.getRootNode()};
    al::ByamlData data;
    if (!tags_iter.getDataByKey(&data, mTagsIdx))
        return false;

    al::ByamlIter iter{actor_iter.getData(), actor_iter.getData() + data.getValue()};
    if (!iter.isValid())
        return false;

    // Binary search.

    s32 a = 0;
    s32 b = iter.getSize();
    if (b <= 0)
        return false;

    al::ByamlHashIter hash_iter{iter.getRootNode()};
    const auto pair_table = hash_iter.getPairTable();

    while (a < b) {
        const s32 idx = (a + b) / 2;

        const auto* pair = &pair_table[idx];
        if (!pair)
            break;

        al::ByamlData hash_data{pair};
        u32 hash;
        if (!iter.tryConvertUInt(&hash, &hash_data))
            break;

        if (hash == tag)
            return true;

        if (hash >= tag)
            b = idx;
        else
            a = idx + 1;
    }

    return false;
}

bool InfoData::hasTag(const char* actor, u32 tag_hash) const {
    al::ByamlIter iter;
    return getActorIter(&iter, actor) && hasTag(iter, tag_hash);
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

const char* InfoData::getSameGroupActorName(const al::ByamlIter& iter) const {
    al::ByamlHashIter hash_iter{iter.getRootNode()};
    al::ByamlData data;
    if (hash_iter.getDataByKey(&data, mSystemSameGroupActorNameIdx)) {
        const char* name;
        if (iter.tryConvertString(&name, &data))
            return name;
    }
    return sead::SafeString::cEmptyString.cstr();
}

s32 InfoData::getTerrainTextures(const char* actor, InfoData::TerrainTextures& info) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor))
        return 0;

    al::ByamlIter textures_iter;
    if (!iter.tryGetIterByKey(&textures_iter, "terrainTextures"))
        return 0;

    s32 count = 0;
    for (s32 i = 0; i < textures_iter.getSize(); ++i) {
        u32 value;
        textures_iter.tryGetUIntByIndex(&value, i);

        if (u8(value) != 0xFF)
            info.textures[count++] = u8(value);
        if (u8(value >> 8) != 0xFF)
            info.textures[count++] = u8(value >> 8);
        if (u8(value >> 16) != 0xFF)
            info.textures[count++] = u8(value >> 16);
        if (u8(value >> 24) != 0xFF)
            info.textures[count++] = u8(value >> 24);
    }
    return count;
}

bool InfoData::getDrops(al::ByamlIter* drops_iter, const char* actor) const {
    al::ByamlIter iter;
    return getActorIter(&iter, actor) && iter.tryGetIterByKey(drops_iter, "drops");
}

const char* InfoData::getName(const char* actor) const {
    return getString(actor, "name", "");
}

const char* InfoData::getString(const char* actor, const char* key,
                                const sead::SafeString& default_, bool x) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor, x))
        return default_.cstr();

    return getStringByKey(iter, key, default_);
}

const char* InfoData::getUnknown(const char* actor, u32) const {
    return actor;
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

bool InfoData::getActorProfile(const char** profile, const al::ByamlIter& iter) const {
    al::ByamlHashIter hash_iter{iter.getRootNode()};
    al::ByamlData data;
    if (hash_iter.getDataByKey(&data, mProfileIdx))
        return iter.tryConvertString(profile, &data);
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

f32 InfoData::getFloatByKey(const al::ByamlIter& iter, const char* key, f32 default_, bool) {
    f32 value;
    return iter.tryGetFloatByKey(&value, key) ? value : default_;
}

bool InfoData::getBoolByKey(const al::ByamlIter& iter, const char* key, bool default_, bool) {
    bool value;
    return iter.tryGetBoolByKey(&value, key) ? value != 0 : default_;
}

bool InfoData::getActorIter(al::ByamlIter* iter, u32 hash, bool x) const {
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
        static_cast<void>(evt::Manager::instance()->getActiveEvent());

    return false;
}

bool InfoData::hasBurnableParam(const al::ByamlIter& iter) {
    al::ByamlIter chemical_it;
    if (!iter.tryGetIterByKey(&chemical_it, "Chemical"))
        return false;
    s32 dummy = 0;
    return chemical_it.tryGetIntByKey(&dummy, "Burnable");
}

bool InfoData::hasCapaciterParam(const al::ByamlIter& iter) {
    al::ByamlIter chemical_it;
    if (!iter.tryGetIterByKey(&chemical_it, "Chemical"))
        return false;
    s32 dummy = 0;
    return chemical_it.tryGetIntByKey(&dummy, "Capaciter");
}

bool InfoData::hasCapaciterParam(const char* actor) const {
    al::ByamlIter iter;
    return getActorIter(&iter, actor) && hasCapaciterParam(iter);
}

f32 InfoData::getScale(const char* actor) const {
    return getFloat(actor, "actorScale", 1.0);
}

f32 InfoData::getAdjustedLookAtOffsetY(const char* actor) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor))
        return 0.0;

    return iter.getFloatByKey("lookAtOffsetY") + iter.getFloatByKey("rigidBodyCenterY");
}

f32 InfoData::getCursorOffsetY(const char* actor) const {
    return getFloat(actor, "cursorOffsetY", 0.0, false);
}

f32 InfoData::getTraverseDist(const char* actor) const {
    return getFloat(actor, "traverseDist", 0.0);
}

bool InfoData::getYLimitAlgorithm(const char** algorithm, const char* actor) const {
    *algorithm = getString(actor, "yLimitAlgorithm", "NoLimit");
    return algorithm != nullptr;
}

f32 InfoData::getAabbNorm(const char* actor, bool x) const {
    sead::Vector3f min, max;
    if (getAAbbMinMax(actor, &min, &max, x))
        return sead::norm2(max - min);
    return 0.0;
}

bool InfoData::getAAbbMinMax(const char* actor, sead::Vector3f* min, sead::Vector3f* max,
                             bool x) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor, x))
        return false;

    bool min_ok, max_ok;

    if (al::tryGetByamlV3f(min, iter, "aabbMin")) {
        min_ok = true;
    } else {
        *min = sead::Vector3f::zero;
        min_ok = false;
    }

    if (al::tryGetByamlV3f(max, iter, "aabbMax")) {
        max_ok = true;
    } else {
        *max = sead::Vector3f::zero;
        max_ok = false;
    }

    return min_ok && max_ok;
}

s32 InfoData::getSortKey(const char* actor) const {
    return getInt(actor, "sortKey", 0, false);
}

f32 InfoData::getBoundingForTraverse(const char* actor) const {
    return getFloat(actor, "boundingForTraverse", 0, false);
}

f32 InfoData::getAabbNormHalf(const char* actor) const {
    return getAabbNorm(actor, true) * 0.5f;
}

bool InfoData::isHasFar(const char* actor) const {
    return getBool(actor, "isHasFar", false, false);
}

bool InfoData::hasDropEntry(const char* actor, const char* key) const {
    al::ByamlIter iter;
    getDrops(&iter, actor);
    return iter.isExistKey(key);
}

s32 InfoData::getInstSize(const char* actor) const {
    return getInt(actor, "instSize", 0, false);
}

u32 InfoData::getBugMask(const char* actor) const {
    return getInt(actor, "bugMask");
}

u32 InfoData::getModelFlags(const char* actor) const {
    u32 flags = 0x4000;
    if (!actor)
        return flags;

    bool is_map_const = false;

    {
        const char* profile;
        if (getActorProfile(&profile, actor)) {
            const sead::SafeString profile_ = profile;
            if (profile_ == "MapConstPassive" || profile_ == "MapConstActive")
                is_map_const = true;
        }
    }

    {
        al::ByamlIter iter;
        if (getActorIter(&iter, actor)) {
            if (!hasTag(iter, tags::Tree))
                flags |= 0x1000;
        } else {
            flags |= 0x1000;
        }
    }

    s32 type = -1;
    {
        al::ByamlIter iter;
        if (getActorIter(&iter, actor)) {
            if (hasTag(iter, tags::Unk_0x4F4E1426))
                type = 0;
            else if (hasTag(iter, tags::PasteGrudgeSlime))
                type = 1;
        }
    }

    if (is_map_const)
        flags &= ~0x1000;

    if (type == 0 || (type != 1 && !is_map_const))
        flags |= 0x2000;

    if (is_map_const && type == 1)
        flags |= 0x1000;

    return flags;
}

bool InfoData::getVariationMatAnim(const char* actor, const char** anim, f32* frame) const {
    al::ByamlIter iter;
    if (!getActorIter(&iter, actor))
        return false;

    *anim = getStringByKey(iter, "variationMatAnim", sead::SafeString::cEmptyString);
    *frame = getIntByKey(iter, "variationMatAnimFrame");
    return (*anim)[0] != 0;
}

bool InfoData::getName(al::ByamlIter* iter, const char** name, s32 idx) const {
    if (idx < 0 || idx >= mNumActors)
        return false;

    *iter = {mActorsBytes, mActorsBytes + mActorOffsets[idx]};
    al::ByamlHashIter hash_iter{iter->getRootNode()};
    al::ByamlData data;
    if (!hash_iter.getDataByKey(&data, mNameIdx))
        return false;

    return iter->tryConvertString(name, &data);
}

}  // namespace ksys::act
