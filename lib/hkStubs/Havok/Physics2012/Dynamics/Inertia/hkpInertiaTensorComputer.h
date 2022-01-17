#pragma once

#include <Havok/Common/GeometryUtilities/Inertia/hkInertiaTensorComputer.h>

class hkcdShape;
class hkpConstraintInstance;
class hkpRigidBody;
class hkpRigidBodyCinfo;
class hkpShape;

class hkpInertiaTensorComputer : public hkInertiaTensorComputer {
public:
    static void computeShapeVolumeMassProperties(const hkcdShape* shape, hkReal mass,
                                                 hkMassProperties& result);

    static void setShapeVolumeMassProperties(const hkpShape* shape, hkReal mass,
                                             hkpRigidBodyCinfo& bodyInfo);

    static void setMassProperties(const hkMassProperties& props, hkpRigidBodyCinfo& bodyInfo);

    static void setAndScaleToDensity(const hkMassProperties& props, hkSimdRealParameter density,
                                     hkpRigidBodyCinfo& bodyInfo);

    static void setAndScaleToMass(const hkMassProperties& props, hkSimdRealParameter mass,
                                  hkpRigidBodyCinfo& bodyInfo);

    static void clipInertia(hkReal maxInertiaRatio, hkpRigidBodyCinfo& bodyInfo);

    static void optimizeInertiasOfConstraintTree(hkpConstraintInstance* const* constraints,
                                                 int numConstraints, hkpRigidBody* rootBody,
                                                 hkReal inertiaFactorHint = 1.5f);
};
