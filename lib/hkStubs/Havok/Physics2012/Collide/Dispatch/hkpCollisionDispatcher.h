#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Geometry/Collide/Shapes/hkcdShape.h>
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidableQualityType.h>
#include <Havok/Physics2012/Collide/Agent/hkpCollisionQualityInfo.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeType.h>

class hkpCdBody;
class hkpCdBodyPairCollector;
class hkpCdPointCollector;
class hkpCollisionAgent;
struct hkpCollisionInput;
class hkpContactMgr;
class hkpContactMgrFactory;
class hkpLinearCastCollisionInput;

namespace hkAgent3 {
enum Symmetric : int;
}

// FIXME: incomplete
class hkpCollisionDispatcher : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCollisionDispatcher)

    enum {
        HK_MAX_RESPONSE_TYPE = 8,
        HK_MAX_SHAPE_TYPE = hkcdShapeType::MAX_PPU_SHAPE_TYPE,
        HK_MAX_AGENT2_TYPES = 64,
        HK_MAX_AGENT3_TYPES = 18,
        HK_MAX_COLLISION_QUALITIES = 8
    };

    using CreateFunc = hkpCollisionAgent* (*)(const hkpCdBody& collA, const hkpCdBody& collB,
                                              const hkpCollisionInput& env, hkpContactMgr* mgr);

    using GetPenetrationsFunc = void (*)(const hkpCdBody& bodyA, const hkpCdBody& bodyB,
                                         const hkpCollisionInput& input,
                                         hkpCdBodyPairCollector& collector);

    using GetClosestPointsFunc = void (*)(const hkpCdBody& bodyA, const hkpCdBody& bodyB,
                                          const hkpCollisionInput& input,
                                          hkpCdPointCollector& output);

    using LinearCastFunc = void (*)(const hkpCdBody& bodyA, const hkpCdBody& bodyB,
                                    const hkpLinearCastCollisionInput& input,
                                    hkpCdPointCollector& castCollector,
                                    hkpCdPointCollector* startCollector);

    struct ShapeInheritance {
        HK_DECLARE_CLASS_ALLOCATOR(ShapeInheritance)

        hkpShapeType m_primaryType;
        hkpShapeType m_alternateType;
    };

    struct AgentFuncs {
        HK_DECLARE_CLASS_ALLOCATOR(AgentFuncs)

        CreateFunc m_createFunc;
        GetPenetrationsFunc m_getPenetrationsFunc;
        GetClosestPointsFunc m_getClosestPointFunc;
        LinearCastFunc m_linearCastFunc;
        hkBool m_isFlipped = false;
        hkBool m_isPredictive = false;
    };

    // FIXME: types
    struct Agent3Funcs {
        HK_DECLARE_CLASS_ALLOCATOR(Agent3Funcs)

        Agent3Funcs() {
            m_updateFilterFunc = nullptr;
            m_invalidateTimFunc = nullptr;
            m_warpTimeFunc = nullptr;
            m_sepNormalFunc = nullptr;
        }

        alignas(16) void* m_createFunc;
        void* m_destroyFunc;
        void* m_cleanupFunc;

        void* m_removePointFunc;
        void* m_commitPotentialFunc;
        void* m_createZombieFunc;

        void* m_updateFilterFunc;
        void* m_invalidateTimFunc;
        void* m_warpTimeFunc;

        void* m_sepNormalFunc;
        void* m_processFunc;

        hkBool m_isPredictive = false;
        hkBool m_ignoreSymmetricVersion = false;
        hkBool m_reusePreviousEntry = false;
    };

    struct Agent3FuncsIntern : Agent3Funcs {
        HK_DECLARE_CLASS_ALLOCATOR(Agent3FuncsIntern)

        hkAgent3::Symmetric m_symmetric;
    };

    hkpCollisionDispatcher(CreateFunc defaultCreationFunction,
                           hkpContactMgrFactory* defaultContactMgrFactory);
    ~hkpCollisionDispatcher() override;

    inline hkBool32 hasAlternateType(hkpShapeType type, hkpShapeType alternateType) const {
        return m_hasAlternateType[type] & (1 << alternateType);
    }

    CreateFunc m_defaultCollisionAgent;
    hkpContactMgrFactory* m_contactMgrFactory[HK_MAX_RESPONSE_TYPE][HK_MAX_RESPONSE_TYPE];
    alignas(16) hkUint32 m_hasAlternateType[HK_MAX_SHAPE_TYPE];

    int m_numAgent2Types;
    alignas(16) hkUchar m_agent2Types[HK_MAX_SHAPE_TYPE][HK_MAX_SHAPE_TYPE];
    hkUchar m_agent2TypesPred[HK_MAX_SHAPE_TYPE][HK_MAX_SHAPE_TYPE];
    AgentFuncs m_agent2Func[HK_MAX_AGENT2_TYPES];

    int m_numAgent3Types;
    alignas(16) hkUchar m_agent3Types[HK_MAX_SHAPE_TYPE][HK_MAX_SHAPE_TYPE];
    alignas(16) hkUchar m_agent3TypesPred[HK_MAX_SHAPE_TYPE][HK_MAX_SHAPE_TYPE];
    Agent3FuncsIntern m_agent3Func[HK_MAX_AGENT3_TYPES];

    alignas(16) hkChar
        m_collisionQualityTable[HK_COLLIDABLE_QUALITY_MAX][HK_COLLIDABLE_QUALITY_MAX];
    alignas(16) hkpCollisionQualityInfo m_collisionQualityInfo[HK_MAX_COLLISION_QUALITIES];

    hkBool m_collisionAgentRegistered;
    hkBool m_agent3Registered;
    hkBool m_midphaseAgent3Registered;
    hkBool m_checkEnabled;
    hkArray<ShapeInheritance> m_shapeInheritance;

    struct DebugTable;
    DebugTable* m_debugAgent2Table;
    DebugTable* m_debugAgent2TablePred;
    DebugTable* m_debugAgent3Table;
    DebugTable* m_debugAgent3TablePred;

    hkReal m_expectedMaxLinearVelocity;
    hkReal m_expectedMinPsiDeltaTime;
};
