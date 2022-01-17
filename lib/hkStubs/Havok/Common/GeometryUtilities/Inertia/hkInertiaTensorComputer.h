#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkGeometry;
struct hkStridedVertices;

struct hkMassProperties {
    HK_DECLARE_CLASS_ALLOCATOR(hkMassProperties)
    HK_DECLARE_REFLECTION()

    hkMassProperties() : m_volume(0), m_mass(0) {
        m_centerOfMass.setZero();
        m_inertiaTensor.setZero();
    }

    explicit hkMassProperties(hkFinishLoadedObjectFlag flag) {}

    void scaleToDensity(hkSimdRealParameter density);
    void scaleToMass(hkSimdRealParameter newMass);

    hkReal m_volume;
    hkReal m_mass;
    hkVector4 m_centerOfMass;
    hkMatrix3 m_inertiaTensor;
};

struct hkMassElement {
    HK_DECLARE_CLASS_ALLOCATOR(hkMassElement)

    HK_FORCE_INLINE hkMassElement() { m_transform.setIdentity(); }

    HK_FORCE_INLINE hkMassElement(const hkMassProperties& properties, const hkTransform& transform)
        : m_properties(properties), m_transform(transform) {}

    hkMassProperties m_properties;
    hkTransform m_transform;
};

class hkInertiaTensorComputer {
public:
    static hkResult computeSphereVolumeMassProperties(hkReal radius, hkReal mass,
                                                      hkMassProperties& result);

    static hkResult computeBoxVolumeMassProperties(hkVector4Parameter halfExtents, hkReal mass,
                                                   hkMassProperties& result);

    static hkResult computeBoxVolumeMassPropertiesDiagonalized(hkVector4Parameter halfExtents,
                                                               hkReal mass,
                                                               hkVector4& inertiaDiagonal,
                                                               hkReal& volume);

    static hkResult computeCapsuleVolumeMassProperties(hkVector4Parameter startAxis,
                                                       hkVector4Parameter endAxis, hkReal radius,
                                                       hkReal mass, hkMassProperties& result);

    static hkResult computeSphereSurfaceMassProperties(hkReal radius, hkReal mass,
                                                       hkReal surfaceThickness,
                                                       hkMassProperties& result);

    static hkResult computeBoxSurfaceMassProperties(hkVector4Parameter halfExtents, hkReal mass,
                                                    hkReal surfaceThickness,
                                                    hkMassProperties& result);

    static hkResult computeTriangleSurfaceMassProperties(hkVector4Parameter v0,
                                                         hkVector4Parameter v1,
                                                         hkVector4Parameter v2, hkReal mass,
                                                         hkReal surfaceThickness,
                                                         hkMassProperties& result);

    static hkResult computeCylinderVolumeMassProperties(hkVector4Parameter startAxis,
                                                        hkVector4Parameter endAxis, hkReal radius,
                                                        hkReal mass, hkMassProperties& result);

    static hkResult computeConvexHullMassProperties(const hkStridedVertices& vertices,
                                                    hkReal radius, hkMassProperties& result);

    using ConvexHullMassPropertiesFunction = hkResult (*)(const hkStridedVertices&, hkReal,
                                                          hkMassProperties&);

    static ConvexHullMassPropertiesFunction s_computeConvexHullMassPropertiesFunction;

    static hkResult computeVertexHullVolumeMassProperties(const hkReal* vertexIn, int striding,
                                                          int numVertices, hkReal mass,
                                                          hkMassProperties& result);

    static hkResult computeVertexCloudMassProperties(const hkReal* vertexIn, int striding,
                                                     int numVertices, hkReal mass,
                                                     hkMassProperties& result);

    static hkResult computeGeometrySurfaceMassProperties(const hkGeometry* geom,
                                                         hkReal surfaceThickness,
                                                         hkBool distributeUniformly, hkReal mass,
                                                         hkMassProperties& result);

    static void computeGeometryVolumeMassProperties(const hkGeometry* geom, hkReal mass,
                                                    hkMassProperties& result);

    static hkResult computeGeometryVolumeMassPropertiesChecked(const hkGeometry* geom, hkReal mass,
                                                               hkMassProperties& result);

    static hkResult combineMassProperties(const hkArray<hkMassElement>& elements,
                                          hkMassProperties& result);

    static void simplifyInertiaTensorToOrientedParticle(hkMatrix3& inertia);

    static void convertInertiaTensorToPrincipleAxis(hkMatrix3& inertia,
                                                    hkRotation& principleAxisOut);

    static void shiftInertiaToCom(hkVector4Parameter shift, hkSimdRealParameter mass,
                                  hkMatrix3& inertia);

    static void shiftInertiaFromCom(hkVector4Parameter shift, hkSimdRealParameter mass,
                                    hkMatrix3& inertia);
};
