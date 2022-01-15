project(hkStubs CXX ASM)

add_library(hkStubs OBJECT
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
  Havok/Common/Base/Math/Matrix/hkRotation.h
  Havok/Common/Base/Math/Matrix/hkRotationf.h
  Havok/Common/Base/Math/Matrix/hkTransform.h
  Havok/Common/Base/Math/Matrix/hkTransformf.h
  Havok/Common/Base/Math/Quaternion/hkQuaternion.h
  Havok/Common/Base/Math/Quaternion/hkQuaternionf.h
  Havok/Common/Base/Math/SweptTransform/hkSweptTransform.h
  Havok/Common/Base/Math/SweptTransform/hkSweptTransformf.h
  Havok/Common/Base/Math/Vector/hkSimdFloat32.h
  Havok/Common/Base/Math/Vector/hkSimdReal.h
  Havok/Common/Base/Math/Vector/hkVector4.h
  Havok/Common/Base/Math/Vector/hkVector4f.h
  Havok/Common/Base/Math/Vector/hkVector4f.inl
  Havok/Common/Base/Math/Vector/hkVector4Comparison.h
  Havok/Common/Base/Math/Vector/hkVector4fComparison.h

  Havok/Common/Base/Memory/Allocator/hkMemoryAllocator.h
  Havok/Common/Base/Memory/Allocator/Lifo/hkLifoAllocator.h
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
  Havok/Common/Base/Types/Physics/MotionState/hkMotionState.h
  Havok/Common/Base/Types/Properties/hkSimpleProperty.h

  Havok/Common/Serialize/Resource/hkResource.h
  Havok/Common/Serialize/Util/hkNativePackfileUtils.h
  Havok/Common/Serialize/Util/hkRootLevelContainer.h

  Havok/Geometry/Collide/Shapes/hkcdShape.h

  Havok/Physics2012/Collide/Agent/hkpCollisionInput.h
  Havok/Physics2012/Collide/Agent/hkpCollisionQualityInfo.h
  Havok/Physics2012/Collide/Agent/Collidable/hkpCdBody.h
  Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h
  Havok/Physics2012/Collide/Agent/Collidable/hkpCollidableQualityType.h
  Havok/Physics2012/Collide/Agent3/BvTree3/hkpBvTreeAgent3.h
  Havok/Physics2012/Collide/Agent3/Machine/Nn/hkpLinkedCollidable.h
  Havok/Physics2012/Collide/BroadPhase/hkpBroadPhaseHandle.h
  Havok/Physics2012/Collide/BroadPhase/hkpTypedBroadPhaseHandle.h
  Havok/Physics2012/Collide/Dispatch/hkpCollisionDispatcher.h
  Havok/Physics2012/Collide/Filter/hkpCollidableCollidableFilter.h
  Havok/Physics2012/Collide/Filter/hkpCollisionFilter.cpp
  Havok/Physics2012/Collide/Filter/hkpCollisionFilter.h
  Havok/Physics2012/Collide/Filter/hkpConvexListFilter.h
  Havok/Physics2012/Collide/Filter/hkpRayCollidableFilter.h
  Havok/Physics2012/Collide/Filter/hkpShapeCollectionFilter.h
  Havok/Physics2012/Collide/Filter/Group/hkpGroupFilter.cpp
  Havok/Physics2012/Collide/Filter/Group/hkpGroupFilter.h
  Havok/Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h
  Havok/Physics2012/Collide/Shape/hkpShape.h
  Havok/Physics2012/Collide/Shape/hkpShapeBase.h
  Havok/Physics2012/Collide/Shape/hkpShapeType.h
  Havok/Physics2012/Collide/Shape/hkpShapeContainer.h
  Havok/Physics2012/Collide/Shape/Compound/Collection/hkpShapeCollection.h
  Havok/Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h
  Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h
  Havok/Physics2012/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h
  Havok/Physics2012/Collide/Shape/HeightField/hkpSphereRepShape.h
  Havok/Physics2012/Collide/Shape/Query/hkpRayShapeCollectionFilter.h
  Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastInput.h
  Havok/Physics2012/Collide/Util/Welding/hkpWeldingUtility.h

  Havok/Physics2012/Dynamics/Collide/hkpResponseModifier.h
  Havok/Physics2012/Dynamics/Common/hkpMaterial.h
  Havok/Physics2012/Dynamics/Common/hkpProperty.h
  Havok/Physics2012/Dynamics/Entity/hkpEntity.h
  Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h
  Havok/Physics2012/Dynamics/Entity/hkpRigidBodyCinfo.h
  Havok/Physics2012/Dynamics/Motion/hkpMotion.h
  Havok/Physics2012/Dynamics/Motion/Rigid/hkpBoxMotion.h
  Havok/Physics2012/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h
  Havok/Physics2012/Dynamics/World/hkpPhysicsSystem.h
  Havok/Physics2012/Dynamics/World/hkpWorld.cpp
  Havok/Physics2012/Dynamics/World/hkpWorld.h
  Havok/Physics2012/Dynamics/World/hkpWorldCinfo.cpp
  Havok/Physics2012/Dynamics/World/hkpWorldCinfo.h
  Havok/Physics2012/Dynamics/World/hkpWorldObject.h
  Havok/Physics2012/Dynamics/World/Memory/hkpWorldMemoryAvailableWatchDog.h
  Havok/Physics2012/Dynamics/World/Memory/Default/hkpDefaultWorldMemoryWatchDog.h

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
