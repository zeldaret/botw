#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkSimplePropertyValue {
    HK_DECLARE_CLASS_ALLOCATOR(hkSimplePropertyValue)
    HK_DECLARE_REFLECTION()

    hkUint64 m_data;

    inline hkSimplePropertyValue() = default;
    inline hkSimplePropertyValue(int i);       // NOLINT(google-explicit-constructor)
    inline hkSimplePropertyValue(hkUint32 i);  // NOLINT(google-explicit-constructor)
    inline hkSimplePropertyValue(hkUint64 i);  // NOLINT(google-explicit-constructor)
    inline hkSimplePropertyValue(hkReal r);    // NOLINT(google-explicit-constructor)
    inline hkSimplePropertyValue(void* p);     // NOLINT(google-explicit-constructor)

    inline void setInt(int i);
    inline void setUint64(hkUint64 i);
    inline void setReal(hkReal r);
    inline void setPtr(void* p);

    inline int getInt() const;
    inline hkUint64 getUint64() const;
    inline hkReal getReal() const;
    inline void* getPtr() const;
};

class hkSimpleProperty {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkSimpleProperty)
    HK_DECLARE_REFLECTION()

    inline hkSimpleProperty();
    inline hkSimpleProperty(hkUint32 key, hkSimplePropertyValue value);
    explicit hkSimpleProperty(hkFinishLoadedObjectFlag flag) {}

    static void mapStringToKey(const char* string, hkUint32& keyOut);

    hkUint32 m_key;
    hkUint32 m_alignmentPadding;
    hkSimplePropertyValue m_value;
};

inline void hkSimplePropertyValue::setInt(const int i) {
    m_data = i;
}

inline void hkSimplePropertyValue::setUint64(hkUint64 i) {
    m_data = i;
}

inline void hkSimplePropertyValue::setReal(const hkReal r) {
    union {
        hkReal r;
#if defined(HK_REAL_IS_DOUBLE)
        hkUint64 u;
#else
        hkUint32 u;
#endif
    } u;
    u.r = r;
    m_data = u.u;
}

inline void hkSimplePropertyValue::setPtr(void* p) {
    m_data = reinterpret_cast<hkUlong>(p);
}

inline hkSimplePropertyValue::hkSimplePropertyValue(const int i) {
    setInt(i);
}

inline hkSimplePropertyValue::hkSimplePropertyValue(const hkUint32 i) {
    setInt(static_cast<int>(i));
}

inline hkSimplePropertyValue::hkSimplePropertyValue(const hkUint64 i) {
    setUint64(i);
}

inline hkSimplePropertyValue::hkSimplePropertyValue(const hkReal r) {
    setReal(r);
}

inline hkSimplePropertyValue::hkSimplePropertyValue(void* p) {
    setPtr(p);
}

inline int hkSimplePropertyValue::getInt() const {
    return static_cast<int>(m_data);
}

inline hkUint64 hkSimplePropertyValue::getUint64() const {
    return m_data;
}

inline hkReal hkSimplePropertyValue::getReal() const {
    union {
        hkReal r;
#if defined(HK_REAL_IS_DOUBLE)
        hkUint64 u;
#else
        hkUint32 u;
#endif
    } u;
    u.u = m_data;
    return u.r;
}

inline void* hkSimplePropertyValue::getPtr() const {
    return reinterpret_cast<void*>(static_cast<hkUlong>(m_data));
}

inline hkSimpleProperty::hkSimpleProperty() = default;

inline hkSimpleProperty::hkSimpleProperty(hkUint32 key, hkSimplePropertyValue value)
    : m_key(key), m_value(value) {}
