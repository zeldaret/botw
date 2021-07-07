#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class ActorLinkConstDataAccess;
}  // namespace ksys::act

namespace ksys::map {

class GenGroup;
class Object;
class Rail;

enum class MapLinkDefType {
    BasicSig = 0,
    AxisX = 1,
    AxisY = 2,
    AxisZ = 3,
    NAxisX = 4,
    NAxisY = 5,
    NAxisZ = 6,
    GimmickSuccess = 7,
    VelocityControl = 8,
    BasicSigOnOnly = 9,
    Remains = 10,
    DeadUp = 11,
    LifeZero = 12,
    Stable = 13,
    ChangeAtnSig = 14,
    Create = 15,
    Delete = 16,
    MtxCopyCreate = 17,
    Freeze = 18,
    ForbidAttention = 19,
    SyncLink = 20,
    CopyWaitRevival = 21,
    OffWaitRevival = 22,
    Recreate = 23,
    AreaCol = 24,
    SensorBlind = 25,
    ForSale = 26,
    ModelBind = 27,
    PlacementLOD = 28,
    DemoMember = 29,
    PhysSystemGroup = 30,
    StackLink = 31,
    FixedCs = 32,
    HingeCs = 33,
    LimitHingeCs = 34,
    SliderCs = 35,
    PulleyCs = 36,
    BAndSCs = 37,
    BAndSLimitAngYCs = 38,
    CogWheelCs = 39,
    RackAndPinionCs = 40,
    Reference = 41,
    Invalid = 42,
};

struct ObjectLink {
    ~ObjectLink() {}
    act::Actor* getObjectActor() const;
    bool getObjectProcWithAccessor(act::ActorLinkConstDataAccess& accessor) const;
    const char* getDescription() const;
    static const char* getDescriptionForType(MapLinkDefType t);
    static MapLinkDefType getTypeForName(const sead::SafeString& name);
    static bool sub_7100D4E310(MapLinkDefType t);
    static bool isPlacementLODOrForSaleLink(MapLinkDefType t);

    Object* other_obj = nullptr;
    MapLinkDefType type = MapLinkDefType::Invalid;
    MubinIter iter{};
};
KSYS_CHECK_SIZE_NX150(ObjectLink, 0x20);

struct ObjectLinkArray {
    bool checkLink(MapLinkDefType t, bool b);

    ObjectLink* findLinkWithType(MapLinkDefType type);
    ObjectLink* findLinkWithType_0(MapLinkDefType type);

    sead::Buffer<ObjectLink> links;
};
KSYS_CHECK_SIZE_NX150(ObjectLinkArray, 0x10);

class ObjectLinkData {
public:
    ObjectLinkData();

    void deleteArrays();
    void release(Object* obj, bool a1);
    bool allocLinksToSelf(s32 num_links, sead::Heap* heap);

    bool sub_7100D4EC40(Object* src, ObjectLink* link, Object* dest);
    void sub_7100D4FB78(Object* obj);
    bool checkCreateLinkObjRevival() const;
    bool checkDeleteLinkObjRevival() const;

    ObjectLink* findLinkWithType(MapLinkDefType t);
    ObjectLink* findLinkWithType_0(MapLinkDefType t);

    void setGenGroup(GenGroup* group);

    void x_1(act::Actor* actor, Object* obj);

    bool checkCreateOrDeleteLinkObjRevival() const {
        return checkDeleteLinkObjRevival() || checkCreateLinkObjRevival();
    }

    Object* mCreateLinksSrcObj = nullptr;
    Object* mDeleteLinksSrcObj = nullptr;

    sead::Buffer<Object*> mObjects;
    ObjectLinkArray mLinksOther{};
    ObjectLinkArray mLinksCs{};
    ObjectLinkArray mLinksToSelf{};

    u32 field_50 = 0;
    bool field_54 = false;
    bool mAppearFade = false;
    bool mNoAutoDemoMember = false;
    bool field_57 = false;

    GenGroup* mGenGroup = nullptr;
    Rail* mRails = nullptr;
};
KSYS_CHECK_SIZE_NX150(ObjectLinkData, 0x68);

}  // namespace ksys::map
