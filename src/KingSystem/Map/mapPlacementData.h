#pragma once

#include <container/seadSafeArray.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>

#include "KingSystem/Map/mapStagePreActorCache.h"
#include "KingSystem/Map/mapTypes.h"
#include "KingSystem/Utils/Types.h"

#ifdef SEAD_DEBUG
#define CHECK_OFFSET(CLASS, MEMBER, OFFSET)
#else
#define CHECK_OFFSET(CLASS, MEMBER, OFFSET) static_assert(offsetof(CLASS, MEMBER) == OFFSET)
#endif

namespace ksys::map {

class LazyTraverseList;
class MubinIter;

struct PlacementData {
    PlacementData();
    ~PlacementData() {
        _29aa4_count = 0;
    }

    bool parseAreas(const sead::SafeString& unitConfigName, const MubinIter& objIter);
    void _d1e578(); // x
    void _d1e9b0();
    void _d1eb24();
    void _d1f4d8();
    void _d1f5cc();
    void _d1f734();
    void _d1f900();
    void _d1facc();
    void _d1fc98();
    void _d1fe1c();
    void _d1fe78();
    void _d20bcc();
    void _d21a88();
    void _d21c3c();
    void _d21ddc();
    void _d224f8();
    void _d226ac();
    void _d22968();
    void _d22c3c();
    void _d22ef8();
    void _d231cc();
    void _d2388c();
    void _d242dc();
    void _d24400(); // postPlaceActors1
    void _d2449c(); // x_0
    void _d24638();

    // not axis and probably not in this class but I dunno what it does
    // contains + and - of each x, y, z as a vector
    class Axis { 
    public:
        Axis() = default;
        Axis(const sead::Vector3f& v) : Axis(v, v) {}

        // parameter names only based on default values
        Axis(const sead::Vector3f& plus, const sead::Vector3f& minus) {
            data[0] = { 0.0f - minus.x, 0.0f, 0.0f };
            data[1] = { 0.0f + plus.x, 0.0f, 0.0f };
            data[2] = { 0.0f, 0.0f, 0.0f - minus.z };
            data[3] = { 0.0f, 0.0f, 0.0f + plus.z };
            data[4] = { 0.0f, 0.0f - minus.y, 0.0f };
            data[5] = { 0.0f, 0.0f + plus.y, 0.0f };
        }

        // needs an assert
        sead::Vector3f& operator[](size_t idx) {
            return data[idx];
        }

    private:
        sead::Vector3f data[6]{};
    };

    struct Unknown1 {  // only _148 appears in PlacementData's ctor
        enum class Culling : s32 { // parseObj
            _0,
            _1,
            _2,
            _3,
            _4,
            _5,
            _6,
            _7,
            _8,
            _9,
            _A,
            _B,
            _C
        };

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
        u8 _12c; // something to do with _29C54, potentially another enum?
        u8 hideRoomNum;
        u8 _130_idx;
        sead::SafeArray<int, 6> _130{}; // used with field_8, parent?
        struct Params { // _148 : u16
            bool hideOutSide : 1;
            bool isConnectNeighborArea : 1;
            bool _4 : 1;
            bool _8 : 1;
            bool _10 : 1;
            bool _20 : 1;
            CullingType culling : 8; 
        } params;
        KSYS_CHECK_SIZE_NX150(Params, 0x2);

        Unknown1() {
            memset(&params, 0, sizeof(params));
        }
    };
    KSYS_CHECK_SIZE_NX150(Unknown1, 0x14C);

    struct OuterNPCMementary {
        sead::Vector3f translate;
        f32 scale;
    };
    KSYS_CHECK_SIZE_NX150(OuterNPCMementary, 0x10);

    struct GeneralArea { // InnerOn?
        enum class Type : s16 {
            None = 0,
            LoadOpt = 2
        };

        sead::BoundBox3f bb{};
        u32 id;
        Type type;
        bool _1d;
    };
    KSYS_CHECK_SIZE_NX150(GeneralArea, 0x20);

    struct JudgeArea {
        sead::BoundBox3f bb{};
        sead::SafeArray<GeneralArea*, 8> parentAreas{};
        sead::SafeArray<u32, 8> parentIds{};
        u32 parentCount = 0;
    };
    KSYS_CHECK_SIZE_NX150(JudgeArea, 0x80);

    struct Unknown4 {
        GeneralArea* parentArea;
        sead::FixedSafeString<16> id{};
    };
    KSYS_CHECK_SIZE_NX150(Unknown4, 0x30);

    struct FarModel {
        sead::Vector3f translate;
        sead::Vector3f rotate;
        sead::Vector3f scale;
        sead::FixedSafeString<16> id{};
    };
    KSYS_CHECK_SIZE_NX150(FarModel, 0x50);

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

    sead::TypedBitFlag<Flag> mFlags;
    bool mIsOneHitChallengeActive = false;
    bool notAocField = false;
    bool _4 = false;
    sead::SafeArray<Unknown1, 512> _8{}; // parseObj
    s32 _8_count;
    Unknown1 alpha{}, omega{};  // parseObj
    sead::SafeArray<OuterNPCMementary, 26> _29aa4{};
    static s32 _29aa4_count;
    sead::Vector3f playerPos;
    f32 cameraAngleMaybe = 50.0f;  // fov?
    u32 _29c54; // enum?
    LazyTraverseList* objects = StagePreActorCache::instance()->getObjects();
    sead::SafeArray<JudgeArea, 16> mJudgeArea{};
    s32 mJudgeArea_count;
    sead::SafeArray<char, 128> _2a468{}; // probably not char
    s32 _2a468_count;
    sead::SafeArray<GeneralArea, 64> _2a4ec{};
    s32 _2a4ec_count;
    sead::SafeArray<Unknown4, 4> _2acf0{};
    s32 _2acf0_count;
    Unknown4* _2adb8;
    sead::SafeArray<FarModel, 128> _2adc0{};
    s32 _2adc0_count;
    f32 _2d5c4; // distance? also doesn't align
    u8 _2d5c8 = 0; // enum potentially

    enum UnkFlag : u8 {
        _40 = 1 << 6, 
        _80 = 1 << 7 
    };

    static sead::TypedBitFlag<UnkFlag> unkFlag;
};
KSYS_CHECK_SIZE_NX150(PlacementData, 0x2D5D0);
CHECK_OFFSET(PlacementData, _29aa4, 0x29aa4);

}  // namespace ksys::map