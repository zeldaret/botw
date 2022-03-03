#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <agl/Utils/aglResParameter.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include <thread/seadMutex.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {

enum class IsIndoorStage;

class CollisionInfo;
class ContactLayerCollisionInfo;
class ContactPointInfoBase;
class RigidBody;
struct RigidBodyCollisionMasks;
class ContactPointInfo;
class LayerContactPointInfo;

struct ContactInfoTable {
    struct Receiver : agl::utl::ParameterObj {
        const char* name = nullptr;
        // TODO: figure out what these masks are
        u32 layer_mask = 0;
        u32 layer_mask2 = 0;
        int num_layers = 0;
        sead::SafeArray<agl::utl::Parameter<int>, MaxNumLayersPerType> layer_values;

    protected:
        void postRead_() override;
    };

    agl::utl::IParameterIO param_io;
    agl::utl::ParameterList contact_info_table_plist;
    sead::Buffer<Receiver> receivers;
};

struct ContactPoint {
    enum class Flag {
        _1 = 1 << 0,
        _2 = 1 << 1,
    };

    RigidBody* body_a;
    RigidBody* body_b;
    sead::Vector3f position;
    sead::Vector3f separating_normal;
    float separating_distance;
    MaterialMask material_mask_a;
    MaterialMask material_mask_b;
    u32 shape_key_a;
    u32 shape_key_b;
    sead::TypedBitFlag<Flag, u8> flags;
};
KSYS_CHECK_SIZE_NX150(ContactPoint, 0x70);

class ContactMgr : public sead::hostio::Node {
public:
    ContactMgr();
    virtual ~ContactMgr();

    void init(sead::Heap* heap);

    void initContactPointPool(sead::Heap* heap, IsIndoorStage indoor);
    void freeContactPointPool();

    void loadContactInfoTable(sead::Heap* heap, agl::utl::ResParameterArchive archive,
                              ContactLayerType type);

    bool getSensorLayerMask(SensorCollisionMask* mask, const sead::SafeString& receiver_type) const;

    ContactPointInfo* allocContactPoints(sead::Heap* heap, int num, const sead::SafeString& name,
                                         int a, int b, int c);
    LayerContactPointInfo* allocContactPointsEx(sead::Heap* heap, int num, int num2,
                                                const sead::SafeString& name, int a, int b, int c);
    void registerContactPointInfo(ContactPointInfoBase* info);
    void freeContactPointInfo(ContactPointInfoBase* info);

    // 0x0000007100fb3284
    /// @param colliding_body_masks The collision masks of the colliding rigid bodies.
    /// @returns whether contact should be disabled.
    bool x_13(ContactPointInfo* info, const ContactPoint& point,
              const RigidBodyCollisionMasks& colliding_body_masks, bool penetrating);

    // 0x0000007100fb3478
    void x_15(LayerContactPointInfo* info, const ContactPoint& point, bool penetrating);

    // 0x0000007100fb3744
    void x_17(CollisionInfo* info, RigidBody* body_a, RigidBody* body_b);
    // 0x0000007100fb37d4
    void x_18(ContactLayerCollisionInfo* info, RigidBody* body_a, RigidBody* body_b);
    // 0x0000007100fb3854
    void x_19(CollisionInfo* info, RigidBody* body_a, RigidBody* body_b);
    // 0x0000007100fb3938
    void x_20(ContactLayerCollisionInfo* info, RigidBody* body_a, RigidBody* body_b);
    // 0x0000007100fb3a2c
    void x_21(ContactLayerCollisionInfo* info, RigidBody* body);

private:
    void doLoadContactInfoTable(agl::utl::ResParameterArchive archive, ContactLayerType type,
                                bool skip_params);

    // Used to optimise ContactPoint allocations.
    sead::Buffer<ContactPoint> mContactPointPool;
    sead::OffsetList<void*> mList0;
    int mList0Size = 0;
    sead::Atomic<int> _34 = 0;
    sead::OffsetList<ContactPointInfoBase> mRigidContactPoints;
    sead::OffsetList<void*> mList2;
    sead::OffsetList<void*> mList3;
    sead::OffsetList<void*> mList4;
    sead::OffsetList<void*> mList5;
    sead::Mutex mMutex1;
    sead::Mutex mMutex2;
    sead::Mutex mMutex3;
    sead::Mutex mMutex4;
    sead::Mutex mMutex5;
    sead::SafeArray<ContactInfoTable, 2> mContactInfoTables{};
};

}  // namespace ksys::phys
