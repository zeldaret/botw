project(hkStubs CXX ASM)

add_library(hkStubs OBJECT
  Havok/Common/Base/Container/String/hkStringPtr.h
  Havok/Common/Base/Types/hkBaseTypes.h
  Havok/Common/Base/hkBase.h
  Havok/Common/Base/Math/hkMath.h
  Havok/Common/Base/Math/Vector/hkVector4.h
  Havok/Common/Base/Object/hkBaseObject.h
  Havok/Common/Base/Object/hkReferencedObject.h
  Havok/Physics/Collide/Shape/hkpShape.h
  Havok/Physics/Collide/Shape/Convex/hkpConvexShape.h
  Havok/Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h
  Havok/Physics/Collide/Shape/HeightField/hkpSphereRepShape.h
  Havok/Physics/Dynamics/Entity/hkpEntity.h
  Havok/Physics/Dynamics/Entity/hkpRigidBody.h
  Havok/Physics/Dynamics/World/hkpWorld.h
  Havok/Physics/Dynamics/World/hkpWorld.cpp
  Havok/Physics/Dynamics/World/hkpWorldEntity.h
)

target_compile_options(hkStubs PRIVATE -fno-exceptions)
target_compile_options(hkStubs PRIVATE -fno-strict-aliasing)
target_compile_options(hkStubs PRIVATE -Wno-invalid-offsetof)
target_include_directories(hkStubs PUBLIC ./)
