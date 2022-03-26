#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkaAnnotationTrack {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaAnnotationTrack)
    HK_DECLARE_REFLECTION()

    hkaAnnotationTrack();
    hkaAnnotationTrack(const hkaAnnotationTrack&);
    explicit hkaAnnotationTrack(hkFinishLoadedObjectFlag flag)
        : m_trackName(flag), m_annotations(flag) {}

    struct Annotation {
        HK_DECLARE_CLASS_ALLOCATOR(Annotation)
        HK_DECLARE_REFLECTION()

        Annotation() : m_time(0) {}
        explicit Annotation(hkFinishLoadedObjectFlag flag) : m_text(flag) {}

        hkReal m_time;
        hkStringPtr m_text;
    };

    hkStringPtr m_trackName;
    hkArray<Annotation> m_annotations;
};
