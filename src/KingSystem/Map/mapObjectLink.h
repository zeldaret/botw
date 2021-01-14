#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class ActorLinkConstDataAccess;
class BaseProc;
}  // namespace ksys::act

namespace ksys::map {

class Object;

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
    act::BaseProc* getObjectProc() const;
    bool getObjectProcWithAccessor(act::ActorLinkConstDataAccess& accessor) const;

    Object* other_obj;
    u32 type;
    MubinIter iter;
};
KSYS_CHECK_SIZE_NX150(ObjectLink, 0x20);

struct ObjectLinkArray {
    ObjectLink* findLinkWithType(MapLinkDefType link_type);
    u32 num_links = 0;
    ObjectLink* links = nullptr;
};
KSYS_CHECK_SIZE_NX150(ObjectLinkArray, 0x10);

class ObjectLinkData {
public:
    ObjectLinkData();

    void release(Object* obj, bool a1);

    Object* mCreateLinksSrcObj = nullptr;
    Object* mDeleteLinksSrcObj = nullptr;
    u32 mNumLinksReference = 0;

    void* mLinksReference = nullptr;
    ObjectLinkArray mLinksOther{};
    ObjectLinkArray mLinksCs{};
    ObjectLinkArray mLinksToSelf{};

    u32 field_50 = 0;
    bool field_54 = false;
    bool mAppearFade = false;
    bool mNoAutoDemoMember = false;
    bool field_57 = false;

    void* mGenGroup = nullptr;
    void* mRails = nullptr;
};
KSYS_CHECK_SIZE_NX150(ObjectLinkData, 0x68);

}  // namespace ksys::map
