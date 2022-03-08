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
#include <prim/seadScopedLock.h>
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

struct CollidingBodies;
class CollisionInfo;
class ContactLayerCollisionInfo;
class ContactPointInfoBase;
class QueryContactPointInfo;
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
        /// Whether this contact point should be skipped when iterating over contact points.
        Invalid = 1 << 0,
        /// Whether the two bodies are penetrating.
        Penetrating = 1 << 1,
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

    // region Factories for collision tracking structures

    ContactPointInfo* makeContactPointInfo(sead::Heap* heap, int num, const sead::SafeString& name,
                                           int a, int b, int c);

    LayerContactPointInfo* makeLayerContactPointInfo(sead::Heap* heap, int num, int num2,
                                                     const sead::SafeString& name, int a, int b,
                                                     int c);

    CollisionInfo* makeCollisionInfo(sead::Heap* heap, const sead::SafeString& name);

    // endregion

    void registerContactPointInfo(ContactPointInfoBase* info);
    void unregisterContactPointInfo(ContactPointInfoBase* info);
    void freeContactPointInfo(ContactPointInfoBase* info);

    void registerCollisionInfo(CollisionInfo* info);
    void unregisterCollisionInfo(CollisionInfo* info);
    void freeCollisionInfo(CollisionInfo* info);

    void clearContactPoints();
    /// Remove all contact points with the specified rigid body.
    /// @note For efficiency reasons, this actually only invalidates the contact points.
    /// They will be removed at a later stage.
    void removeContactPointsWithBody(RigidBody* body);
    void removeCollisionEntriesWithBody(RigidBody* body);
    // TODO: figure out what this removes
    // 0x0000007100fb31b8
    void removeUnkWithBody(RigidBody* body);

    /// @param colliding_body_masks The collision masks of the colliding rigid bodies.
    /// @returns whether contact should be disabled.
    bool registerContactPoint(ContactPointInfo* info, const ContactPoint& point,
                              const RigidBodyCollisionMasks& colliding_body_masks,
                              bool penetrating);

    bool registerContactPoint(QueryContactPointInfo* info, const ContactPoint& point,
                              bool penetrating);

    void registerContactPoint(LayerContactPointInfo* info, const ContactPoint& point,
                              bool penetrating);

    void registerCollision(CollisionInfo* info, RigidBody* body_a, RigidBody* body_b);
    void registerCollision(ContactLayerCollisionInfo* info, RigidBody* body_a, RigidBody* body_b);
    void unregisterCollision(CollisionInfo* info, RigidBody* body_a, RigidBody* body_b);
    void unregisterCollision(ContactLayerCollisionInfo* info, RigidBody* body_a, RigidBody* body_b);
    /// Unregister all collision pairs involving the specified rigid body.
    void unregisterCollisionWithBody(ContactLayerCollisionInfo* info, RigidBody* body);

    void clearCollisionEntries(CollisionInfo* info);

    bool initLayerMasks(ContactPointInfo* info, const sead::SafeString& receiver_name) const;
    bool initLayerMasks(CollisionInfo* info, const sead::SafeString& receiver_name) const;
    bool getSensorLayerMask(SensorCollisionMask* mask, const sead::SafeString& receiver_name) const;

    // 0x0000007100fb4228
    void x_26(RigidBody* body_a, RigidBody* body_b);
    // 0x0000007100fb42f4
    void x_27(RigidBody* body_a, RigidBody* body_b, const sead::Vector3f&, const sead::Vector3f&,
              u32 material_a, u32 material_b);
    // 0x0000007100fb4738
    void x_28(void* unk);
    // 0x0000007100fb49d4
    void x_14();
    // 0x0000007100fb4a90
    void x_29();

private:
    void doLoadContactInfoTable(agl::utl::ResParameterArchive archive, ContactLayerType type,
                                bool skip_params);

    /// @return an index into mContactPointPool or -1 if the pool is exhausted.
    int allocateContactPoint();

    void freeCollidingBodiesEntry(CollidingBodies* entry) {
        auto lock = sead::makeScopedLock(mCollidingBodiesMutex);
        mCollidingBodiesFreeList.pushBack(entry);
    }

    /// Used to optimise ContactPoint allocations.
    sead::Buffer<ContactPoint> mContactPointPool;
    sead::OffsetList<CollidingBodies> mCollidingBodiesFreeList;
    int mList0Size = 0;
    /// The number of contact points. Also the iindex of the next free ContactPoint in the pool.
    sead::Atomic<int> mNumContactPoints = 0;
    sead::OffsetList<ContactPointInfoBase> mContactPointInfoInstances;
    sead::OffsetList<CollisionInfo> mCollisionInfoInstances;
    sead::OffsetList<void*> mList3;
    sead::OffsetList<void*> mList4;
    sead::OffsetList<void*> mList5;
    // TODO: rename these members
    sead::Mutex mContactPointInfoMutex;
    sead::Mutex mCollisionInfoMutex;
    sead::Mutex mMutex3;
    sead::Mutex mCollidingBodiesMutex;
    sead::Mutex mMutex5;
    sead::SafeArray<ContactInfoTable, 2> mContactInfoTables{};
};

}  // namespace ksys::phys
