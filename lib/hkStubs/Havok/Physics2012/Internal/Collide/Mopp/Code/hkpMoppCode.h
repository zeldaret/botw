#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpMoppCode : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpMoppCode)
    HK_DECLARE_REFLECTION()

    enum {
        MIN_PROPERTY_VALUE = 0,
        MAX_PROPERTY_VALUE = 0xffffffff,
    };

    enum {
        MAX_PRIMITIVE_PROPERTIES = 1,
    };

    enum BuildType {
        BUILT_WITH_CHUNK_SUBDIVISION,
        BUILT_WITHOUT_CHUNK_SUBDIVISION,
        BUILD_NOT_SET,
    };

    struct CodeInfo {
        HK_DECLARE_CLASS_ALLOCATOR(CodeInfo)
        HK_DECLARE_REFLECTION()

        inline hkReal getScale() const;
        inline void setScale(hkReal inVal);

        hkVector4 m_offset;
    };

    hkpMoppCode() {
        m_info.m_offset.setZero();
        m_buildType = BUILD_NOT_SET;
    }

    explicit hkpMoppCode(hkFinishLoadedObjectFlag f) : hkReferencedObject(f), m_data(f) {}

    inline hkpMoppCode(const CodeInfo& info, const hkUint8* moppData, int moppBytes,
                       BuildType buildType);

    ~hkpMoppCode() override = default;

    inline hkInt32 getCodeSize() const;

    inline void initialize(const CodeInfo& info, const hkUint8* moppData, int moppBytes,
                           BuildType buildType = BUILD_NOT_SET);

    CodeInfo m_info;
    hkArray<hkUint8> m_data;
    hkEnum<BuildType, hkInt8> m_buildType;
};

inline hkpMoppCode::hkpMoppCode(const CodeInfo& info, const hkUint8* moppData, int moppBytes,
                                BuildType buildType)
    : m_info(info), m_data(const_cast<hkUint8*>(moppData), moppBytes, moppBytes) {
    m_buildType = buildType;
}

inline hkInt32 hkpMoppCode::getCodeSize() const {
    return m_data.getSize();
}

inline hkReal hkpMoppCode::CodeInfo::getScale() const {
    return m_offset(3);
}

inline void hkpMoppCode::CodeInfo::setScale(hkReal inVal) {
    m_offset(3) = inVal;
}
