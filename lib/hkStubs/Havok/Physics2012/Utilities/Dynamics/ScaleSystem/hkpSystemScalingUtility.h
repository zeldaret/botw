#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Utilities/Collide/ShapeUtils/ShapeScaling/hkpShapeScalingUtility.h>

class hkpPhysicsSystem;

class hkpSystemScalingUtility {
public:
    static void scaleSystemSimd(hkpPhysicsSystem* system, hkSimdRealParameter scale,
                                hkArray<hkpShapeScalingUtility::ShapePair>* doneShapes = nullptr);

    static void scaleSystem(hkpPhysicsSystem* system, hkReal scale,
                            hkArray<hkpShapeScalingUtility::ShapePair>* doneShapes = nullptr) {
        scaleSystemSimd(system, hkSimdReal(scale), doneShapes);
    }
};
