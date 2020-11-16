#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <gfx/seadColor.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
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

    void init(u8* data, sead::Heap* heap, sead::Heap* debug_heap);

    void getModelInfo(const char* actor, ModelInfo& info) const;
    bool getActorIter(al::ByamlIter* iter, const char* actor, bool x = true) const;
    bool logFailure(const sead::SafeString& actor_name) const;
    void getRecipeInfo(const char* actor, RecipeInfo& info) const;
    void getLocators(const char* actor, Locators& info) const;
    void getHomeAreas(const char* actor, HomeAreas& info) const;
    // TODO: invalid time function
    // TODO: tag functions
    const char* getSameGroupActorName(const char* actor) const;
    // TODO: more functions
    const char* getSLinkUser(const char* actor) const;
    bool getSLinkAndELinkUsers(const char* actor, const char** elink, const char** slink) const;
    const char* getXLinkUser(const char* actor) const;
    bool getActorProfile(const char** profile, const char* actor) const;
    // TODO: more functions
    f32 getScale(const char* actor) const;

    const char* getString(const char* actor, const char* key, const sead::SafeString& default_,
                          bool x = true) const;
    s32 getInt(const char* actor, const char* key, s32 default_ = 0, bool x = true) const;
    f32 getFloat(const char* actor, const char* key, f32 default_ = 0, bool x = true) const;
    bool getBool(const char* actor, const char* key, bool default_ = false, bool x = true) const;

    static s32 getIntByKey(const al::ByamlIter& iter, const char* key, s32 default_ = 0);
    static f32 getFloatByKey(const al::ByamlIter& iter, const char* key, f32 default_ = 0);
    static bool getBoolByKey(const al::ByamlIter& iter, const char* key, bool default_ = false);
    static const char* getStringByKey(const al::ByamlIter& iter, const char* key,
                                      const sead::SafeString& default_);

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
