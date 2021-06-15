#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <gfx/seadColor.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Utils/Types.h"

namespace al {
class ByamlIter;
}

namespace ksys::act {

class InfoData {
    SEAD_SINGLETON_DISPOSER(InfoData)
    InfoData() = default;
    virtual ~InfoData();

public:
    struct ModelInfo {
        sead::Vector3f baseScale;
        sead::Color4f addColor;
        sead::Color4f mulColor;
        const char* bfres;
        const char* mainModel;
    };
    KSYS_CHECK_SIZE_NX150(ModelInfo, 0x40);

    struct RecipeInfo {
        struct Item {
            sead::FixedSafeString<64> name;
            s32 num;
        };

        s32 num_items;
        Item items[3];
    };
    KSYS_CHECK_SIZE_NX150(RecipeInfo, 0x128);

    struct Locator {
        enum class Type {
            Invalid = -1,
            Trunk = 0,
            Branch = 1,
            GlowStone = 2,
            OnTree = 3,
            MagnePos = 4,
            StopTimerPos = 5,
        };

        Type type;
        sead::Vector3f pos;
        sead::Vector3f rot;
    };
    KSYS_CHECK_SIZE_NX150(Locator, 0x1c);

    struct Locators {
        s32 num;
        sead::SafeArray<Locator, 8> locators;
    };
    KSYS_CHECK_SIZE_NX150(Locators, 0xe4);

    struct HomeAreas {
        sead::SafeArray<const char*, 3> names;
    };
    KSYS_CHECK_SIZE_NX150(HomeAreas, 0x18);

    struct InvalidLifeConditions {
        s32 num_times;
        sead::SafeArray<sead::SafeString, 16> times;
        s32 num_weathers;
        sead::SafeArray<sead::SafeString, 16> weathers;
    };
    KSYS_CHECK_SIZE_NX150(InvalidLifeConditions, 0x210);

    struct TerrainTextures {
        sead::SafeArray<u8, 0x20> textures;
    };
    KSYS_CHECK_SIZE_NX150(TerrainTextures, 0x20);

    void init(u8* data, sead::Heap* heap, sead::Heap* debug_heap);

    void getModelInfo(const char* actor, ModelInfo& info) const;
    bool getActorIter(al::ByamlIter* iter, const char* actor, bool x = true) const;
    bool logFailure(const sead::SafeString& actor_name) const;
    void getRecipeInfo(const char* actor, RecipeInfo& info) const;
    void getLocators(const char* actor, Locators& info) const;
    void getHomeAreas(const char* actor, HomeAreas& info) const;
    void getInvalidLifeConditions(const char* actor, InvalidLifeConditions& info) const;
    bool hasTag(const char* actor, const char* tag) const;
    bool hasTag(const al::ByamlIter& actor_iter, u32 tag_hash) const;
    bool hasTag(const char* actor, u32 tag_hash) const;
    const char* getSameGroupActorName(const char* actor) const;
    const char* getSameGroupActorName(const al::ByamlIter& iter) const;
    s32 getTerrainTextures(const char* actor, TerrainTextures& info) const;
    bool getDrops(al::ByamlIter* drops_iter, const char* actor) const;
    const char* getName(const char* actor) const;
    const char* getUnknown(const char* actor, u32 x) const;
    const char* getSLinkUser(const char* actor) const;
    bool getSLinkAndELinkUsers(const char* actor, const char** elink, const char** slink) const;
    const char* getXLinkUser(const char* actor) const;
    bool getActorProfile(const char** profile, const char* actor) const;
    bool getActorProfile(const char** profile, const al::ByamlIter& iter) const;
    bool getActorIter(al::ByamlIter* iter, u32 actor_name_hash, bool x = true) const;
    static bool hasBurnableParam(const al::ByamlIter& iter);
    static bool hasCapaciterParam(const al::ByamlIter& iter);
    bool hasCapaciterParam(const char* actor) const;
    f32 getScale(const char* actor) const;
    f32 getAdjustedLookAtOffsetY(const char* actor) const;
    f32 getCursorOffsetY(const char* actor) const;
    f32 getTraverseDist(const char* actor) const;
    bool getYLimitAlgorithm(const char** algorithm, const char* actor) const;
    f32 getAabbNorm(const char* actor, bool x) const;
    bool getAAbbMinMax(const char* actor, sead::Vector3f* min, sead::Vector3f* max, bool x) const;
    s32 getSortKey(const char* actor) const;
    f32 getBoundingForTraverse(const char* actor) const;
    f32 getAabbNormHalf(const char* actor) const;
    bool isHasFar(const char* actor) const;
    bool hasDropEntry(const char* actor, const char* key) const;
    s32 getInstSize(const char* actor) const;
    u32 getBugMask(const char* actor) const;
    u32 getModelFlags(const char* actor) const;
    bool getVariationMatAnim(const char* actor, const char** anim, f32* frame) const;
    bool getName(al::ByamlIter* iter, const char** name, s32 idx) const;

    const char* getString(const char* actor, const char* key,
                          const sead::SafeString& default_ = sead::SafeString::cEmptyString,
                          bool x = true) const;
    s32 getInt(const char* actor, const char* key, s32 default_ = 0, bool x = true) const;
    f32 getFloat(const char* actor, const char* key, f32 default_ = 0, bool x = true) const;
    bool getBool(const char* actor, const char* key, bool default_ = false, bool x = true) const;

    static s32 getIntByKey(const al::ByamlIter& iter, const char* key, s32 default_ = 0,
                           bool x = true);
    static f32 getFloatByKey(const al::ByamlIter& iter, const char* key, f32 default_ = 0,
                             bool x = true);
    static bool getBoolByKey(const al::ByamlIter& iter, const char* key, bool default_ = false,
                             bool x = true);
    static const char*
    getStringByKey(const al::ByamlIter& iter, const char* key,
                   const sead::SafeString& default_ = sead::SafeString::cEmptyString,
                   bool x = true);

private:
    struct DebugEntry {
        sead::FixedSafeString<64> str;
        bool used;
    };
    KSYS_CHECK_SIZE_NX150(DebugEntry, 0x60);

    al::ByamlIter* mRootIter{};
    al::ByamlIter* mHashesIter{};
    al::ByamlIter* mActorsIter{};

    const u8* mHashesBytes{};
    const u32* mHashes{};

    const u8* mActorsBytes{};
    const u32* mActorOffsets{};

    s32 mTagsIdx = -1;
    s32 mInvalidWeathersIdx = -1;
    s32 mInvalidTimesIdx = -1;
    s32 mSystemSameGroupActorNameIdx = -1;
    s32 mNameIdx = -1;
    s32 mProfileIdx = -1;

    s32 mNumActors = 0;
    DebugEntry* mDebugEntries{};
    u32 _88 = 0;
    sead::Heap* mDebugHeap{};

    static constexpr s32 NumDebugEntries = 512;
};
KSYS_CHECK_SIZE_NX150(InfoData, 0x98);

}  // namespace ksys::act
