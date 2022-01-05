#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkClassEnum;
class hkCustomAttributes;

class hkClassMember {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkClassMember)
    HK_DECLARE_REFLECTION()

    enum Type {
        TYPE_VOID = 0,
        TYPE_BOOL,
        TYPE_CHAR,
        TYPE_INT8,
        TYPE_UINT8,
        TYPE_INT16,
        TYPE_UINT16,
        TYPE_INT32,
        TYPE_UINT32,
        TYPE_INT64,
        TYPE_UINT64,
        TYPE_REAL,
        TYPE_VECTOR4,
        TYPE_QUATERNION,
        TYPE_MATRIX3,
        TYPE_ROTATION,
        TYPE_QSTRANSFORM,
        TYPE_MATRIX4,
        TYPE_TRANSFORM,
        TYPE_ZERO,
        TYPE_POINTER,
        TYPE_FUNCTIONPOINTER,
        /// hkArray<T>
        TYPE_ARRAY,
        /// hkInplaceArray<T,N> or hkInplaceArrayAligned16<T,N>
        TYPE_INPLACEARRAY,
        /// hkEnum<ENUM,STORAGE>
        TYPE_ENUM,
        TYPE_STRUCT,
        TYPE_SIMPLEARRAY,
        TYPE_HOMOGENEOUSARRAY,
        TYPE_VARIANT,
        TYPE_CSTRING,
        TYPE_ULONG,
        TYPE_FLAGS,
        TYPE_HALF,
        /// hkStringPtr
        TYPE_STRINGPTR,
        /// hkRelArray
        TYPE_RELARRAY,
        TYPE_MAX
    };

    enum FlagValues {
        FLAGS_NONE = 0,
        ALIGN_8 = 1 << 7,
        ALIGN_16 = 1 << 8,
        NOT_OWNED = 1 << 9,
        SERIALIZE_IGNORED = 1 << 10,
        ALIGN_32 = 1 << 11,
#ifdef HK_REAL_IS_DOUBLE
        ALIGN_REAL = ALIGN_32,
#else
        ALIGN_REAL = ALIGN_16,
#endif
    };
    using Flags = hkFlags<FlagValues, hkUint16>;

    enum DeprecatedFlagValues {
        DEPRECATED_SIZE_8 = 8,
        DEPRECATED_ENUM_8 = 8,
        DEPRECATED_SIZE_16 = 16,
        DEPRECATED_ENUM_16 = 16,
        DEPRECATED_SIZE_32 = 32,
        DEPRECATED_ENUM_32 = 32,
    };

    enum {
        HK_CLASS_ZERO_DEFAULT = -2,
    };

    constexpr hkClassMember(const char* name, const hkClass* class_, const hkClassEnum* enum_,
                            const hkEnum<Type, hkUint8>& type, const hkEnum<Type, hkUint8>& subtype,
                            hkInt16 cArraySize, hkUint16 flags, hkUint16 offset,
                            const hkCustomAttributes* attributes)
        : m_name(name), m_class(class_), m_enum(enum_), m_type(type), m_subtype(subtype),
          m_cArraySize(cArraySize), m_flags(flags), m_offset(offset), m_attributes(attributes) {}

    inline const char* getName() const;

    inline hkClassMember::Type getType() const;
    inline void setType(hkClassMember::Type type);

    inline hkClassMember::Type getSubType() const;
    inline void setSubType(hkClassMember::Type subtype);

    hkClassMember::Type getArrayType() const;

    int getSizeInBytes() const;
    int getAlignment() const;
    hkBool isNotOwner() const;
    int getTypeName(char* buf, int bufLen) const;
    int getArrayMemberSize() const;

    inline hkBool hasClass() const;
    const hkClass& getStructClass() const;
    const hkClass* getClass() const;
    inline hkBool hasEnumClass() const;
    const hkClassEnum& getEnumClass() const;

    int getCstyleArraySize() const;

    const hkClassEnum& getEnumType() const;
    int getEnumValue(const void* memberAddress) const;
    void setEnumValue(void* memberAddress, int value) const;

    inline int getOffset() const;
    inline void setOffset(int offset);

    inline const Flags& getFlags() const;
    inline Flags& getFlags();

    const hkVariant* getAttribute(const char* id) const;

    static hkClassMember::Type getTypeOf(const char* name);
    static hkClassMember::Type getSubtypeOf(const char* name);

    struct TypeProperties {
        HK_DECLARE_CLASS_ALLOCATOR(hkClassMember::TypeProperties)

        hkEnum<hkClassMember::Type, hkUint8> m_type;
        const char* m_name;
        short m_size;
        short m_align;
    };
    static const TypeProperties& getClassMemberTypeProperties(Type type);

private:
    const char* m_name;
    const hkClass* m_class;
    const hkClassEnum* m_enum;
    hkEnum<Type, hkUint8> m_type;
    hkEnum<Type, hkUint8> m_subtype;
    hkInt16 m_cArraySize;
    Flags m_flags;
    hkUint16 m_offset;
    const hkCustomAttributes* m_attributes;
};

inline const char* hkClassMember::getName() const {
    return m_name;
}

inline hkClassMember::Type hkClassMember::getType() const {
    return static_cast<Type>(m_type);
}

inline void hkClassMember::setType(hkClassMember::Type type) {
    m_type = type;
}

inline hkClassMember::Type hkClassMember::getSubType() const {
    return static_cast<Type>(m_subtype);
}

inline void hkClassMember::setSubType(hkClassMember::Type subtype) {
    m_subtype = subtype;
}

inline int hkClassMember::getOffset() const {
    return m_offset;
}

inline void hkClassMember::setOffset(int offset) {
    m_offset = static_cast<hkUint16>(offset);
}

inline const hkClassMember::Flags& hkClassMember::getFlags() const {
    return m_flags;
}

inline hkClassMember::Flags& hkClassMember::getFlags() {
    return m_flags;
}

inline hkBool hkClassMember::hasClass() const {
    return m_class != nullptr;
}

inline hkBool hkClassMember::hasEnumClass() const {
    return m_enum != nullptr;
}
