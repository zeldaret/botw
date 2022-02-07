#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpShape;

class hkpShapeScalingUtility {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapeScalingUtility)

    struct ShapePair {
        HK_DECLARE_CLASS_ALLOCATOR(ShapePair)

        hkpShape* originalShape;
        hkpShape* newShape;
    };

    static hkpShape* scaleShapeSimd(hkpShape* shape, hkSimdRealParameter scale,
                                    hkArray<ShapePair>* doneShapes = nullptr);

    static hkpShape* scaleShape(hkpShape* shape, hkReal scale,
                                hkArray<ShapePair>* doneShapes = nullptr) {
        return scaleShapeSimd(shape, hkSimdReal(scale), doneShapes);
    }
};
