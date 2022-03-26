#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkaAnimatedReferenceFrame : public hkReferencedObject {
public:
    enum hkaReferenceFrameTypeEnum {
        REFERENCE_FRAME_UNKNOWN,
        REFERENCE_FRAME_DEFAULT,
        REFERENCE_FRAME_PARAMETRIC
    };

    HK_DECLARE_CLASS_ALLOCATOR(hkaAnimatedReferenceFrame)
    HK_DECLARE_REFLECTION()

    inline explicit hkaAnimatedReferenceFrame(hkaReferenceFrameTypeEnum frameType)
        : m_frameType(frameType) {}

    inline hkaAnimatedReferenceFrame(hkFinishLoadedObjectFlag flag,
                                     hkaReferenceFrameTypeEnum frameType)
        : hkReferencedObject(flag), m_frameType(frameType) {}

    virtual void getReferenceFrame(hkReal time, hkQsTransform& motionOut) const = 0;

    virtual void getDeltaReferenceFrame(hkReal time, hkReal nextTime, int loops,
                                        hkQsTransform& deltaMotionOut, hkReal cropStartAmount,
                                        hkReal cropEndAmount) const = 0;

    virtual hkReal getDuration() const = 0;

    hkEnum<hkaReferenceFrameTypeEnum, hkInt8> m_frameType;
};
