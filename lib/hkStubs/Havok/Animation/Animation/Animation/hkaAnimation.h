#pragma once

#include <Havok/Animation/Animation/Animation/hkaAnnotationTrack.h>
#include <Havok/Animation/Animation/Motion/hkaAnimatedReferenceFrame.h>
#include <Havok/Common/Base/hkBase.h>

class hkaSkeleton;

extern const class hkClass hkaAnimationClass;

class hkaAnimation : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaAnimation)
    HK_DECLARE_REFLECTION()

    inline hkaAnimation();

    explicit hkaAnimation(hkFinishLoadedObjectFlag flag)
        : hkReferencedObject(flag), m_extractedMotion(flag), m_annotationTracks(flag) {}

    enum AnimationType {
        HK_UNKNOWN_ANIMATION = 0,
        HK_INTERLEAVED_ANIMATION,
        HK_MIRRORED_ANIMATION,
        HK_SPLINE_COMPRESSED_ANIMATION,
        HK_QUANTIZED_COMPRESSED_ANIMATION,
        HK_PREDICTIVE_COMPRESSED_ANIMATION,
        HK_REFERENCE_POSE_ANIMATION,
    };

    HK_FORCE_INLINE hkaAnimation::AnimationType getType() const;

    virtual void sampleTracks(hkReal time, hkQsTransform* transformTracksOut,
                              hkReal* floatTracksOut) const = 0;

    virtual void samplePartialTracks(hkReal time, hkUint32 maxNumTransformTracks,
                                     hkQsTransform* transformTracksOut, hkUint32 maxNumFloatTracks,
                                     hkReal* floatTracksOut) const;

    inline void sampleSingleTransformTrack(hkReal time, hkInt16 track,
                                           hkQsTransform* transformOut) const;

    inline void sampleSingleFloatTrack(hkReal time, hkInt16 track, hkReal* out) const;

    virtual void sampleIndividualTransformTracks(hkReal time, const hkInt16* tracks,
                                                 hkUint32 numTracks,
                                                 hkQsTransform* transformOut) const = 0;

    virtual void sampleIndividualFloatTracks(hkReal time, const hkInt16* tracks, hkUint32 numTracks,
                                             hkReal* out) const = 0;

    virtual int getSizeInBytes() const = 0;

    virtual int getNumOriginalFrames() const = 0;

    // INTERNAL
    struct DataChunk {
        HK_DECLARE_CLASS_ALLOCATOR(DataChunk)

        const hkUint8* m_data;
        hkUint32 m_size;
    };

    virtual int getNumDataChunks(hkUint32 frame, hkReal delta) const;

    virtual void getDataChunks(hkUint32 frame, hkReal delta, DataChunk* dataChunks,
                               int m_numDataChunks) const;

    virtual int getMaxSizeOfCombinedDataChunks() const;

    virtual int getMaxDecompressionTempBytes() const;

    virtual void getExtractedMotionReferenceFrame(hkReal time, hkQsTransform& motionOut) const;

    virtual void getExtractedMotionDeltaReferenceFrame(hkReal time, hkReal nextTime, int loops,
                                                       hkQsTransform& deltaMotionOut,
                                                       hkReal cropStartAmount,
                                                       hkReal cropEndAmount) const;

    hkBool hasExtractedMotion() const;

    void setExtractedMotion(const hkaAnimatedReferenceFrame* extractedMotion);

    const hkaAnimatedReferenceFrame* getExtractedMotion() const;

    // TODO
    inline void getFrameAndDelta(hkReal time, hkUint32& frameOut, hkReal& deltaOut) const;

    struct TrackAnnotation {
        HK_DECLARE_CLASS_ALLOCATOR(TrackAnnotation)

        hkUint16 m_trackID;
        hkaAnnotationTrack::Annotation m_annotation;
    };

    virtual hkUint32 getNumAnnotations(hkReal startTime, hkReal deltaTime) const;

    virtual hkUint32 getAnnotations(hkReal startTime, hkReal deltaTime,
                                    TrackAnnotation* annotationsOut, hkUint32 maxAnnotations) const;

    hkUint32 getAnnotations(hkReal startTime, hkReal deltaTime,
                            TrackAnnotation* annotationsOut) const {
        return getAnnotations(startTime, deltaTime, annotationsOut, HK_INT32_MAX);
    }

    virtual bool requiresSkeleton() const;
    virtual const hkaSkeleton* getSkeleton() const;
    virtual void setSkeleton(const hkaSkeleton* skeleton);

protected:
    hkaAnimation(const hkaAnimation&);

    hkEnum<hkaAnimation::AnimationType, hkInt32> m_type;

public:
    hkReal m_duration;
    int m_numberOfTransformTracks;
    int m_numberOfFloatTracks;

protected:
    hkRefPtr<const hkaAnimatedReferenceFrame> m_extractedMotion;

public:
    hkArray<hkaAnnotationTrack> m_annotationTracks;
};

inline hkaAnimation::hkaAnimation() : m_type(HK_UNKNOWN_ANIMATION) {
    m_duration = 0;
    m_numberOfTransformTracks = 0;
    m_numberOfFloatTracks = 0;
    m_extractedMotion = nullptr;
}

inline hkaAnimation::AnimationType hkaAnimation::getType() const {
    return m_type;
}

inline void hkaAnimation::sampleSingleTransformTrack(hkReal time, hkInt16 track,
                                                     hkQsTransform* transformOut) const {
    sampleIndividualTransformTracks(time, &track, 1, transformOut);
}

inline void hkaAnimation::sampleSingleFloatTrack(hkReal time, hkInt16 track, hkReal* out) const {
    sampleIndividualFloatTracks(time, &track, 1, out);
}

inline hkBool hkaAnimation::hasExtractedMotion() const {
    return m_extractedMotion != nullptr;
}

inline void hkaAnimation::setExtractedMotion(const hkaAnimatedReferenceFrame* extractedMotion) {
    m_extractedMotion = extractedMotion;
}

inline const hkaAnimatedReferenceFrame* hkaAnimation::getExtractedMotion() const {
    return m_extractedMotion;
}

inline void hkaAnimation::getExtractedMotionReferenceFrame(hkReal time,
                                                           hkQsTransform& motionOut) const {
    m_extractedMotion->getReferenceFrame(time, motionOut);
}

inline void hkaAnimation::getExtractedMotionDeltaReferenceFrame(hkReal time, hkReal nextTime,
                                                                int loops,
                                                                hkQsTransform& deltaMotionOut,
                                                                hkReal cropStartAmount,
                                                                hkReal cropEndAmount) const {
    m_extractedMotion->getDeltaReferenceFrame(time, nextTime, loops, deltaMotionOut,
                                              cropStartAmount, cropEndAmount);
}
