project(hkStubs CXX ASM)

add_library(hkStubs OBJECT
  Havok/Animation/Animation/Animation/hkaAnimation.h
  Havok/Animation/Animation/Animation/hkaAnimationBinding.h
  Havok/Animation/Animation/Animation/hkaAnnotationTrack.h
  Havok/Animation/Animation/Mapper/hkaSkeletonMapper.h
  Havok/Animation/Animation/Mapper/hkaSkeletonMapperData.h
  Havok/Animation/Animation/Motion/hkaAnimatedReferenceFrame.h
  Havok/Animation/Animation/Playback/Utilities/hkaSampleAndCombineUtils.h
  Havok/Animation/Animation/Rig/hkaBone.h
  Havok/Animation/Animation/Rig/hkaBoneAttachment.h
  Havok/Animation/Animation/Rig/hkaSkeleton.h
  Havok/Animation/Animation/Rig/hkaPose.h
  Havok/Animation/Physics2012Bridge/Controller/RigidBody/hkaKeyFrameHierarchyUtility.h
  Havok/Animation/Physics2012Bridge/Controller/RigidBody/hkaRagdollRigidBodyController.h
  Havok/Animation/Physics2012Bridge/Instance/hkaRagdollInstance.h

  Havok/Common/Base/hkBase.h

  Havok/Common/Base/Container/hkContainerAllocators.h
  Havok/Common/Base/Container/Array/hkArray.h
  Havok/Common/Base/Container/Array/hkArrayUtil.h
  Havok/Common/Base/Container/Array/hkSmallArray.h
  Havok/Common/Base/Container/String/hkString.h
  Havok/Common/Base/Container/String/hkStringPtr.h

  Havok/Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h

  Havok/Common/Base/Math/hkMath.h
  Havok/Common/Base/Math/Header/hkMathHeaderConstants.h
  Havok/Common/Base/Math/Matrix/hkMatrix3.h
  Havok/Common/Base/Math/Matrix/hkMatrix3f.h
  Havok/Common/Base/Math/Matrix/hkMatrix3f.inl
  Havok/Common/Base/Math/Matrix/hkMatrix4.h
  Havok/Common/Base/Math/Matrix/hkMatrix4f.h
  Havok/Common/Base/Math/Matrix/hkRotation.h
  Havok/Common/Base/Math/Matrix/hkRotationf.h
  Havok/Common/Base/Math/Matrix/hkTransform.h
  Havok/Common/Base/Math/Matrix/hkTransformf.h
  Havok/Common/Base/Math/QsTransform/hkQsTransform.h
  Havok/Common/Base/Math/QsTransform/hkQsTransformf.h
  Havok/Common/Base/Math/QsTransform/hkQsTransformf.inl
  Havok/Common/Base/Math/Quaternion/hkQuaternion.h
  Havok/Common/Base/Math/Quaternion/hkQuaternionf.h
  Havok/Common/Base/Math/Quaternion/hkQuaternionf.inl
  Havok/Common/Base/Math/SweptTransform/hkSweptTransform.h
  Havok/Common/Base/Math/SweptTransform/hkSweptTransformf.h
  Havok/Common/Base/Math/SweptTransform/hkSweptTransformfUtil.h
  Havok/Common/Base/Math/Vector/hkFourTransposedPoints.h
  Havok/Common/Base/Math/Vector/hkFourTransposedPointsf.h
  Havok/Common/Base/Math/Vector/hkSimdFloat32.h
  Havok/Common/Base/Math/Vector/hkSimdReal.h
  Havok/Common/Base/Math/Vector/hkVector4.h
  Havok/Common/Base/Math/Vector/hkVector4f.h
  Havok/Common/Base/Math/Vector/hkVector4f.inl
  Havok/Common/Base/Math/Vector/hkVector4Comparison.h
  Havok/Common/Base/Math/Vector/hkVector4fComparison.h
  Havok/Common/Base/Math/Vector/hkVector4fComparison.inl

  Havok/Common/Base/Memory/Allocator/hkMemoryAllocator.h
  Havok/Common/Base/Memory/Allocator/Lifo/hkLifoAllocator.h
  Havok/Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h
  Havok/Common/Base/Memory/Router/hkMemoryRouter.h
  Havok/Common/Base/Memory/Util/hkMemUtil.h

  Havok/Common/Base/Object/hkBaseObject.h
  Havok/Common/Base/Object/hkReferencedObject.cpp
  Havok/Common/Base/Object/hkReferencedObject.h

  Havok/Common/Base/Reflection/hkClass.h
  Havok/Common/Base/Reflection/hkClassEnum.h
  Havok/Common/Base/Reflection/hkClassMember.h
  Havok/Common/Base/Reflection/hkTypeInfo.h

  Havok/Common/Base/System/StackTracer/hkStackTracer.h

  Havok/Common/Base/Thread/Atomic/hkAtomicPrimitives.h
  Havok/Common/Base/Thread/Thread/hkThreadLocalData.h

  Havok/Common/Base/Types/hkBaseDefs.h
  Havok/Common/Base/Types/hkBaseTypes.h
  Havok/Common/Base/Types/hkRefPtr.h
  Havok/Common/Base/Types/hkRefVariant.h
  Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h
  Havok/Common/Base/Types/Geometry/Aabb/hkAabbUtil.h
  Havok/Common/Base/Types/Geometry/LocalFrame/hkLocalFrame.h
  Havok/Common/Base/Types/Geometry/Sphere/hkSphere.h
  Havok/Common/Base/Types/Physics/hkStepInfo.h
  Havok/Common/Base/Types/Physics/ContactPoint/hkContactPointMaterial.h
  Havok/Common/Base/Types/Physics/MotionState/hkMotionState.h
  Havok/Common/Base/Types/Properties/hkSimpleProperty.h

  Havok/Common/GeometryUtilities/Inertia/hkInertiaTensorComputer.h

  Havok/Common/Serialize/Resource/hkResource.h
  Havok/Common/Serialize/Util/hkNativePackfileUtils.h
  Havok/Common/Serialize/Util/hkRootLevelContainer.h

  Havok/Geometry/Collide/Shapes/hkcdShape.h
  Havok/Geometry/Internal/Types/hkcdVertex.h

  Havok/Physics/Constraint/Atom/hkpConstraintAtom.h
  Havok/Physics/Constraint/Data/hkpConstraintData.h
  Havok/Physics/Constraint/Data/hkpConstraintInfo.h
  Havok/Physics/ConstraintSolver/Accumulator/hkpVelocityAccumulator.h
  Havok/Physics/ConstraintSolver/Solve/hkpSolverInfo.h
  Havok/Physics/ConstraintSolver/Solve/hkpSolverResults.h

  Havok/Physics2012/Collide/Agent/hkpCollisionInput.h
  Havok/Physics2012/Collide/Agent/hkpCollisionQualityInfo.h
  Havok/Physics2012/Collide/Agent/hkpProcessCollisionInput.h
  Havok/Physics2012/Collide/Agent/Collidable/hkpCdBody.h
  Havok/Physics2012/Collide/Agent/Collidable/hkpCdPoint.h
  Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h
  Havok/Physics2012/Collide/Agent/Collidable/hkpCollidableQualityType.h
  Havok/Physics2012/Collide/Agent/ContactMgr/hkpContactMgr.h
  Havok/Physics2012/Collide/Agent/Query/hkpCdBodyPairCollector.h
  Havok/Physics2012/Collide/Agent/Query/hkpCdPointCollector.h
  Havok/Physics2012/Collide/Agent3/BvTree3/hkpBvTreeAgent3.h
  Havok/Physics2012/Collide/Agent3/Machine/Nn/hkpAgentNnTrack.h
  Havok/Physics2012/Collide/Agent3/Machine/Nn/hkpLinkedCollidable.h
  Havok/Physics2012/Collide/BroadPhase/hkpBroadPhaseHandle.h
  Havok/Physics2012/Collide/BroadPhase/hkpTypedBroadPhaseHandle.h
  Havok/Physics2012/Collide/Dispatch/hkpCollisionDispatcher.h
  Havok/Physics2012/Collide/Dispatch/BroadPhase/hkpBroadPhaseListener.h
  Havok/Physics2012/Collide/Dispatch/ContactMgr/hkpContactMgrFactory.h
  Havok/Physics2012/Collide/Filter/hkpCollidableCollidableFilter.h
  Havok/Physics2012/Collide/Filter/hkpCollisionFilter.cpp
  Havok/Physics2012/Collide/Filter/hkpCollisionFilter.h
  Havok/Physics2012/Collide/Filter/hkpConvexListFilter.h
  Havok/Physics2012/Collide/Filter/hkpRayCollidableFilter.h
  Havok/Physics2012/Collide/Filter/hkpShapeCollectionFilter.h
  Havok/Physics2012/Collide/Filter/Group/hkpGroupFilter.cpp
  Havok/Physics2012/Collide/Filter/Group/hkpGroupFilter.h
  Havok/Physics2012/Collide/Query/hkpRayHitCollector.h
  Havok/Physics2012/Collide/Query/CastUtil/hkpLinearCastInput.h
  Havok/Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h
  Havok/Physics2012/Collide/Query/CastUtil/hkpWorldRayCastOutput.h
  Havok/Physics2012/Collide/Query/Collector/PointCollector/hkpAllCdPointCollector.h
  Havok/Physics2012/Collide/Query/Collector/PointCollector/hkpClosestCdPointCollector.h
  Havok/Physics2012/Collide/Query/Collector/PointCollector/hkpRootCdPoint.h
  Havok/Physics2012/Collide/Shape/hkpShape.h
  Havok/Physics2012/Collide/Shape/hkpShapeBase.h
  Havok/Physics2012/Collide/Shape/hkpShapeBuffer.h
  Havok/Physics2012/Collide/Shape/hkpShapeContainer.h
  Havok/Physics2012/Collide/Shape/hkpShapeType.h
  Havok/Physics2012/Collide/Shape/Compound/Collection/hkpShapeCollection.h
  Havok/Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.h
  Havok/Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h
  Havok/Physics2012/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h
  Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h
  Havok/Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h
  Havok/Physics2012/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h
  Havok/Physics2012/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h
  Havok/Physics2012/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h
  Havok/Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h
  Havok/Physics2012/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h
  Havok/Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.h
  Havok/Physics2012/Collide/Shape/Convex/Triangle/hkpTriangleShape.h
  Havok/Physics2012/Collide/Shape/HeightField/hkpHeightFieldShape.h
  Havok/Physics2012/Collide/Shape/HeightField/hkpSphereRepShape.h
  Havok/Physics2012/Collide/Shape/HeightField/Plane/hkpPlaneShape.h
  Havok/Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldBaseCinfo.h
  Havok/Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h
  Havok/Physics2012/Collide/Shape/Query/hkpRayShapeCollectionFilter.h
  Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastCollectorOutput.h
  Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastInput.h
  Havok/Physics2012/Collide/Util/Welding/hkpWeldingUtility.h

  Havok/Physics2012/Dynamics/Action/hkpAction.h
  Havok/Physics2012/Dynamics/Collide/hkpDynamicsContactMgr.h
  Havok/Physics2012/Dynamics/Collide/hkpResponseModifier.h
  Havok/Physics2012/Dynamics/Collide/hkpSimpleConstraintContactMgr.h
  Havok/Physics2012/Dynamics/Collide/ContactListener/hkpCollisionEvent.h
  Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactListener.h
  Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactPointEvent.h
  Havok/Physics2012/Dynamics/Common/hkpMaterial.h
  Havok/Physics2012/Dynamics/Common/hkpProperty.h
  Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h
  Havok/Physics2012/Dynamics/Constraint/hkpConstraintOwner.h
  Havok/Physics2012/Dynamics/Constraint/Atom/hkpModifierConstraintAtom.h
  Havok/Physics2012/Dynamics/Constraint/Atom/hkpSimpleContactConstraintAtom.h
  Havok/Physics2012/Dynamics/Constraint/Atom/hkpSimpleContactConstraintAtomUtil.h
  Havok/Physics2012/Dynamics/Constraint/Contact/hkpContactPointProperties.h
  Havok/Physics2012/Dynamics/Constraint/Contact/hkpDynamicsCpidMgr.h
  Havok/Physics2012/Dynamics/Constraint/Contact/hkpSimpleContactConstraintData.h
  Havok/Physics2012/Dynamics/Entity/hkpEntity.h
  Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h
  Havok/Physics2012/Dynamics/Entity/hkpRigidBodyCinfo.h
  Havok/Physics2012/Dynamics/Inertia/hkpInertiaTensorComputer.h
  Havok/Physics2012/Dynamics/Motion/hkpMotion.h
  Havok/Physics2012/Dynamics/Motion/Rigid/hkpBoxMotion.h
  Havok/Physics2012/Dynamics/Motion/Rigid/hkpFixedRigidMotion.h
  Havok/Physics2012/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h
  Havok/Physics2012/Dynamics/Motion/Rigid/hkpSphereMotion.h
  Havok/Physics2012/Dynamics/Phantom/hkpAabbPhantom.h
  Havok/Physics2012/Dynamics/Phantom/hkpCachingShapePhantom.h
  Havok/Physics2012/Dynamics/Phantom/hkpPhantom.h
  Havok/Physics2012/Dynamics/Phantom/hkpPhantomBroadPhaseListener.h
  Havok/Physics2012/Dynamics/Phantom/hkpPhantomListener.h
  Havok/Physics2012/Dynamics/Phantom/hkpPhantomOverlapListener.h
  Havok/Physics2012/Dynamics/Phantom/hkpPhantomType.h
  Havok/Physics2012/Dynamics/Phantom/hkpShapePhantom.h
  Havok/Physics2012/Dynamics/Phantom/hkpSimpleShapePhantom.h
  Havok/Physics2012/Dynamics/World/hkpPhysicsSystem.h
  Havok/Physics2012/Dynamics/World/hkpSimulationIsland.h
  Havok/Physics2012/Dynamics/World/hkpWorld.h
  Havok/Physics2012/Dynamics/World/hkpWorldCinfo.cpp
  Havok/Physics2012/Dynamics/World/hkpWorldCinfo.h
  Havok/Physics2012/Dynamics/World/hkpWorldObject.h
  Havok/Physics2012/Dynamics/World/BroadPhaseBorder/hkpBroadPhaseBorder.h
  Havok/Physics2012/Dynamics/World/Listener/hkpIslandActivationListener.h
  Havok/Physics2012/Dynamics/World/Listener/hkpIslandPostCollideListener.h
  Havok/Physics2012/Dynamics/World/Listener/hkpIslandPostIntegrateListener.h
  Havok/Physics2012/Dynamics/World/Listener/hkpWorldDeletionListener.h
  Havok/Physics2012/Dynamics/World/Listener/hkpWorldPostCollideListener.h
  Havok/Physics2012/Dynamics/World/Listener/hkpWorldPostIntegrateListener.h
  Havok/Physics2012/Dynamics/World/Listener/hkpWorldPostSimulationListener.h
  Havok/Physics2012/Dynamics/World/Memory/hkpWorldMemoryAvailableWatchDog.h
  Havok/Physics2012/Dynamics/World/Memory/Default/hkpDefaultWorldMemoryWatchDog.h
  Havok/Physics2012/Dynamics/World/Simulation/hkpSimulation.h
  Havok/Physics2012/Dynamics/World/Util/hkpWorldConstraintUtil.h

  Havok/Physics2012/Internal/Collide/BvCompressedMesh/hkpBvCompressedMeshShape.h
  Havok/Physics2012/Internal/Collide/Mopp/Code/hkpMoppCode.h
  Havok/Physics2012/Internal/Collide/StaticCompound/hkpShapeKeyTable.h
  Havok/Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h
  Havok/Physics2012/Internal/Solver/Contact/hkpSimpleContactConstraintDataInfo.h

  Havok/Physics2012/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h
  Havok/Physics2012/Utilities/Collide/ShapeUtils/ShapeKeyPath/hkpShapeKeyPath.h
  Havok/Physics2012/Utilities/Collide/ShapeUtils/ShapeScaling/hkpShapeScalingUtility.h
  Havok/Physics2012/Utilities/Dynamics/ScaleSystem/hkpSystemScalingUtility.h
  Havok/Physics2012/Utilities/Serialize/hkpPhysicsData.h
)

target_compile_options(hkStubs PRIVATE -fno-exceptions)
target_compile_options(hkStubs PRIVATE -fno-strict-aliasing)
target_compile_options(hkStubs PRIVATE -Wno-invalid-offsetof)
target_include_directories(hkStubs PUBLIC ./)

if(NOT TARGET NintendoSDK)
  add_subdirectory(../NintendoSDK)
endif()
target_link_libraries(hkStubs PUBLIC NintendoSDK)
