#pragma once

#include <Havok/Common/Base/System/StackTracer/hkStackTracer.h>
#include <Havok/Common/Base/hkBase.h>

class hkCriticalSection;

class hkMultiThreadCheck {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkMultiThreadCheck)
    HK_DECLARE_REFLECTION()

    enum AccessType {
        HK_ACCESS_IGNORE = 0,
        HK_ACCESS_RO = 1,
        HK_ACCESS_RW = 2,
    };

    enum ReadMode {
        THIS_OBJECT_ONLY,
        RECURSIVE,
    };

    enum : hkUint32 {
        MARKED_RO = 0xffffffe1,  // and all children
        MARKED_RO_SELF_ONLY = 0xffffffc1,
        UNMARKED = 0xfffffff1
    };

    HK_FORCE_INLINE hkMultiThreadCheck();

    HK_FORCE_INLINE void init();

    HK_FORCE_INLINE void markForRead(ReadMode mode = RECURSIVE) {}
    HK_FORCE_INLINE void markForWrite() {}
    HK_FORCE_INLINE bool isMarkedForWrite() { return true; }
    HK_FORCE_INLINE bool isMarkedForReadRecursive() { return true; }
    HK_FORCE_INLINE void unmarkForRead() {}
    HK_FORCE_INLINE void unmarkForWrite() {}

    hkUint32 m_threadId;
    static hkStackTracer s_stackTracer;
    static hkStackTracer::CallTree* s_stackTree;
    int m_stackTraceId;
    hkUint16 m_markCount;
    static hkCriticalSection* m_criticalSection;
    static void globalCriticalSectionLock();
    static void globalCriticalSectionUnlock();

protected:
    hkUint16 m_markBitStack;
};

inline hkMultiThreadCheck::hkMultiThreadCheck() : m_threadId(UNMARKED), m_markCount(0x8000) {}

inline void hkMultiThreadCheck::init() {
    m_threadId = UNMARKED;
    m_markCount = 0x8000;
}
