#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterIO.h>
#include <agl/utl/aglParameterList.h>
#include <agl/utl/aglParameterObj.h>
#include <agl/utl/aglResParameter.h>
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
class ContactLayerCollisionInfoGroup;
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
    struct ImpulseEntry;

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

    ContactLayerCollisionInfoGroup*
    makeContactLayerCollisionInfoGroup(sead::Heap* heap, ContactLayer layer, int capacity,
                                       const sead::SafeString& name);

    // endregion

    void registerContactPointInfo(ContactPointInfoBase* info);
    void unregisterContactPointInfo(ContactPointInfoBase* info);
    void freeContactPointInfo(ContactPointInfoBase* info);

    void registerCollisionInfo(CollisionInfo* info);
    void unregisterCollisionInfo(CollisionInfo* info);
    void freeCollisionInfo(CollisionInfo* info);

    void registerContactLayerCollisionInfoGroup(ContactLayerCollisionInfoGroup* group);
    void unregisterContactLayerCollisionInfoGroup(ContactLayerCollisionInfoGroup* group);
    void freeContactLayerCollisionInfoGroup(ContactLayerCollisionInfoGroup* group);

    void clearContactPoints();
    /// Remove all contact points with the specified rigid body.
    /// @note For efficiency reasons, this actually only invalidates the contact points.
    /// They will be removed at a later stage.
    void removeContactPointsWithBody(RigidBody* body);
    void removeCollisionEntriesWithBody(RigidBody* body);
    void removeImpulseEntriesWithBody(RigidBody* body);

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
    void clearCollisionEntries(ContactLayerCollisionInfoGroup* group);

    bool initLayerMasks(ContactPointInfo* info, const sead::SafeString& receiver_name) const;
    bool initLayerMasks(CollisionInfo* info, const sead::SafeString& receiver_name) const;
    bool getSensorLayerMask(SensorCollisionMask* mask, const sead::SafeString& receiver_name) const;

    /// Add a new impulse entry based on contact between the two specified rigid bodies.
    /// After this is called, contact point information must then be specified using
    /// setImpulseEntryContactInfo.
    void addImpulseEntry(RigidBody* body_a, RigidBody* body_b);

    /// Fill in an existing impulse entry with contact information.
    /// This does nothing if there is no impulse entry for the specified rigid bodies.
    void setImpulseEntryContactInfo(RigidBody* body_a, RigidBody* body_b,
                                    const sead::Vector3f& contact_point_pos,
                                    const sead::Vector3f& contact_point_normal, u32 material_a,
                                    u32 material_b);

    void processImpulseEntries();
    void clearImpulseEntries();

private:
    void processImpulseEntry(const ImpulseEntry& index);

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
    int mCollidingBodiesCapacity = 0;
    /// The number of contact points. Also the iindex of the next free ContactPoint in the pool.
    sead::Atomic<int> mNumContactPoints = 0;
    sead::OffsetList<ContactPointInfoBase> mContactPointInfoInstances;
    sead::OffsetList<CollisionInfo> mCollisionInfoInstances;
    sead::OffsetList<ContactLayerCollisionInfoGroup> mLayerColInfoGroups;
    sead::OffsetList<ImpulseEntry> mImpulseEntriesFreeList;
    sead::OffsetList<ImpulseEntry> mImpulseEntries;
    sead::Mutex mContactPointInfoMutex;
    sead::Mutex mCollisionInfoMutex;
    sead::Mutex mLayerColInfoGroupMutex;
    sead::Mutex mCollidingBodiesMutex;
    sead::Mutex mImpulseEntriesMutex;
    sead::SafeArray<ContactInfoTable, 2> mContactInfoTables{};
};

}  // namespace ksys::phys
