#pragma once

#include <container/seadSafeArray.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>

#include "KingSystem/Map/mapStagePreActorCache.h"
#include "KingSystem/Map/mapTypes.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::gdt {
class Manager;
}

namespace ksys::map {

class LazyTraverseList;
class MubinIter;
class Object;

class PlacementAreaMgr {
    // not "Axis" and probably not in this class but I dunno what it does
    // contains + and - of each x, y, z as a vector
    class Axis {
    public:
        Axis() = default;
        explicit Axis(const sead::Vector3f& v) : Axis(v, v) {}

        // parameter names only based on default values
        Axis(const sead::Vector3f& plus, const sead::Vector3f& minus) {
            data[0] = {0.0f - minus.x, 0.0f, 0.0f};
            data[1] = {0.0f + plus.x, 0.0f, 0.0f};
            data[2] = {0.0f, 0.0f, 0.0f - minus.z};
            data[3] = {0.0f, 0.0f, 0.0f + plus.z};
            data[4] = {0.0f, 0.0f - minus.y, 0.0f};
            data[5] = {0.0f, 0.0f + plus.y, 0.0f};
        }

        // needs an assert
        sead::Vector3f& operator[](size_t idx) { return data[idx]; }

        const sead::Vector3f& operator[](size_t idx) const { return data[idx]; }

    private:
        sead::Vector3f data[6]{};
    };

    struct Unknown1 {  // only params appears in PlacementAreaMgr's ctor
        // unsure about these culling enums and the params bitfield
        enum class CullingOption : s32 { _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C };

        enum class CullingType : u8 {
            None,
            Culling_1 = 1 << 0,
            Culling_2 = 1 << 1,
            Culling_4 = 1 << 2,
            Culling_8 = 1 << 3,
            Culling_10 = 1 << 4,
            Culling_20 = 1 << 5,
            Culling_40 = 1 << 6,
            Culling_80 = 1 << 7,

            Culling_3 = Culling_2 | Culling_1,
            Culling_B = Culling_8 | Culling_3,
            Culling_F = Culling_8 | Culling_4 | Culling_3,
            Culling_13 = Culling_10 | Culling_3,
            Culling_18 = Culling_10 | Culling_8,
            Culling_1B = Culling_10 | Culling_B,
            Culling_1F = Culling_10 | Culling_F,
            Culling_30 = Culling_20 | Culling_10,
            Culling_33 = Culling_30 | Culling_3,
            Culling_3B = Culling_30 | Culling_B,
            Culling_43 = Culling_40 | Culling_3,
            Culling_9B = Culling_80 | Culling_1B,
        };

        Axis base{}, calc{}, load{}, _d8{};
        sead::Vector3f translate{};
        s8 _12c;  // something to do with _29C54/mActiveNpc
        u8 hide_room_num;
        u8 _130_count;
        sead::SafeArray<int, 6> _130{};  // used to index mInnerHide, parent idx?
        struct Params {                  // _148 : u16
            bool hide_out_side : 1;
            bool is_connect_neighbor_area : 1;
            bool _4 : 1;
            bool _8 : 1;
            bool _10 : 1;
            bool _20 : 1;
            CullingType culling : 8;
        } params{};
        KSYS_CHECK_SIZE_NX150(Params, 0x2);

        // helpers
        Unknown1() { memset(&params, 0, sizeof(params)); }

        void addLink(const int& idx);  // unsure about name
    };
    KSYS_CHECK_SIZE_NX150(Unknown1, 0x14C);

    struct OuterNPCMementary {
        sead::Vector3f translate;
        f32 scale;

        // should probably remove
        bool isInside(const sead::Vector3f& pos) const {
            return (pos - translate).squaredLength() < sead::Mathf::square(scale);
        }
    };
    KSYS_CHECK_SIZE_NX150(OuterNPCMementary, 0x10);

    struct GeneralArea {  // InnerOn?
        enum class Type : u8 { None = 0, LoadOpt = 2 };

        sead::BoundBox3f bb{};
        u32 id;
        Type type;
        bool loaded;
    };
    KSYS_CHECK_SIZE_NX150(GeneralArea, 0x20);

    struct JudgeArea {
        sead::BoundBox3f bb{};
        sead::SafeArray<GeneralArea*, 8> parent_areas{};
        sead::SafeArray<u32, 8> parent_ids{};
        s32 parent_count = 0;
    };
    KSYS_CHECK_SIZE_NX150(JudgeArea, 0x80);

    struct OptArea {
        GeneralArea* parent_area;
        sead::FixedSafeString<16> id{};
    };
    KSYS_CHECK_SIZE_NX150(OptArea, 0x30);

    struct FarModel {
        sead::Vector3f translate;
        sead::Vector3f rotate;
        sead::Vector3f scale;
        sead::FixedSafeString<16> id{};
    };
    KSYS_CHECK_SIZE_NX150(FarModel, 0x50);

public:
    enum class Flag : u16 {
        Remains = 1 << 0,
        AocField = 1 << 1,
        FireOrWindRemains = 1 << 2,
        _8 = 1 << 3,
        _10 = 1 << 4,
        WindRelicFlag = 1 << 5,
        FirstInCastleBossRoom = 1 << 6,
        LastBoss = 1 << 7,
        _100 = 1 << 8,
        _200 = 1 << 9,
        _400 = 1 << 10,
        _800 = 1 << 11,
        _1000 = 1 << 12,
        _2000 = 1 << 13,
        _4000 = 1 << 14,
        FinalTrial = 1 << 15
    };

    // d1f4d8
    static bool getIsPlayedDemo145AndFirstInCastleBossRoom(ksys::gdt::Manager& gdm,
                                                           bool* first_in_ganon_boss_room,
                                                           bool* played_demo_145);

    // d1c8c0
    PlacementAreaMgr();
    ~PlacementAreaMgr();

    // d1cecc
    bool parseAreas(const sead::SafeString& unit_config_name, const MubinIter& obj_iter);
    // d1e578
    void x();
    void addLinkPair(const int& idx, const int& sub_idx);
    // d1eb24
    void postPlaceActorsUpdateFlagsAndLazyTraverse();
    bool insideInnerHideTrans(const int& idx);
    bool insideInnerHideBase(const int& idx);
    bool insideInnerHideCalc(const int& idx);
    bool insideInnerHideLoad(const int& idx);
    void loadDemoCulling(const sead::SafeString& demo_name);
    void unloadDemoCulling();
    // d1fe78
    bool shouldSkipSpawnOneHitChallengeActor(const Object& obj);
    // d20bcc
    bool shouldSkipSpawn(const Object& obj, bool a3);
    bool insideInnerHideBase(const sead::Vector3f& pos, const float& dist_from_face,
                             const int& idx);
    bool isPlayerInsideNpc(const sead::Vector3f& pos);
    // d21ddc
    void boundsChecking();
    bool insideInnerHideCalc(const sead::Vector3f& pos, const float& dist_from_face,
                             const int& idx);
    bool insideAlphaBase(const sead::Vector3f& pos, const float& dist_from_face);
    bool insideOmegaBase();
    bool insideOmegaBase(const sead::Vector3f& pos, const float& dist_from_face);
    bool insideAlphaBase();
    // d231cc
    void boundsChecking_1();  // looks eerily similar to boundsChecking
    // d2388c
    void weirdSetup();  // perhaps used with teleport feature?
    bool isInsideNpc(const sead::Vector3f& pos);
    // d24400
    void pushFarModels();
    // d2449c
    bool x_0(const int& idx, const int& sub_idx);

    s8 isInsideNpcIdx(const sead::Vector3f& pos);
    GeneralArea* findGeneralArea(const u32& id);

    sead::TypedBitFlag<Flag> mFlags;
    bool mIsOneHitChallengeActive = false;
    bool mNotAocField = false;
    bool _4 = false;
    sead::SafeArray<Unknown1, 512> mInnerHide{};  // parseObj
    s32 mInnerHideCount;
    Unknown1 mAlpha{}, mOmega{};  // parseObj
    sead::SafeArray<OuterNPCMementary, 26> mNpc{};
    sead::Vector3f mPlayerPos;
    f32 mCameraAngleMaybe = 50.0f;  // fov?
    s32 mActiveNpc;                 // 0 - 25
    LazyTraverseList* mObjects = StagePreActorCache::instance()->getObjects();
    sead::SafeArray<JudgeArea, 16> mJudgeArea{};
    s32 mJudgeAreaCount;
    sead::SafeArray<char, 128> _2a468{};  // probably not char
    s32 _2a468Count;
    sead::SafeArray<GeneralArea, 64> mGeneralAreas{};
    s32 mGeneralAreasCount;
    sead::SafeArray<OptArea, 4> mOptAreas{};
    s32 mOptAreasCount;
    OptArea* mIntroArea;
    sead::SafeArray<FarModel, 128> mFarModels{};
    s32 mFarModelsCount;
    f32 _2d5c4;     // distance?
    u8 _2d5c8 = 0;  // enum potentially
};
KSYS_CHECK_SIZE_NX150(PlacementAreaMgr, 0x2D5D0);

}  // namespace ksys::map