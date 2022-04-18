#pragma once

#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <cstddef>
#include <cstdint>
#include <type_traits>

using hkFloat32 = float;
using hkDouble64 = double;
using hkReal = hkFloat32;
#define HK_REAL_IS_FLOAT
#define HK_FLOAT_ALIGNMENT 16
#define HK_DOUBLE_ALIGNMENT 32
#define HK_REAL_ALIGNMENT HK_FLOAT_ALIGNMENT

using hkChar = char;
using hkInt8 = std::int8_t;
using hkInt16 = std::int16_t;
using hkInt32 = std::int32_t;
using hkInt64 = std::int64_t;

using hkUchar = unsigned char;
using hkUint8 = std::uint8_t;
using hkUint16 = std::uint16_t;
using hkUint32 = std::uint32_t;
using hkUint64 = std::uint64_t;
using hk_size_t = std::size_t;
using hkLong = long;
using hkUlong = unsigned long;

using hkObjectIndex = hkUint16;
constexpr hkObjectIndex HK_INVALID_OBJECT_INDEX = 0xffff;

using hkTime = hkReal;

using m128 = __attribute((vector_size(16))) float;
using m128u = __attribute((vector_size(16))) hkUint32;

class hkHalf {
public:
    hkHalf() {}

    explicit hkHalf(const float& f) {
        int t = ((const int*)&f)[0];
        m_value = hkInt16(t >> 16);
    }

    hkHalf(const hkHalf&) = default;

    hkHalf& operator=(const float& f) {
        int t = ((const int*)&f)[0];
        m_value = hkInt16(t >> 16);
        return *this;
    }

    hkHalf& operator=(const hkHalf& o) {
        m_value = o.m_value;
        return *this;
    }

    bool operator==(const hkHalf& o) const { return (m_value == o.m_value); }

    void store(float* f) const {
        hkUint32* i = (hkUint32*)f;
        i[0] = m_value << 16;
    }

    void setZero() { m_value = 0; }

    void setOne() { m_value = 0x3F80; }

    template <bool Round>
    void set(const float& r) {
        union {
            float f;
            int i;
        } u;
        if constexpr (Round)
            u.f = r * (1.0f + 1.0f / 256.f);
        else
            u.f = r;
        m_value = hkInt16(u.i >> 16);
    }

    operator float() const {
        union {
            int i;
            float f;
        } u;
        u.i = (m_value << 16);
        return u.f;
    }

    hkInt16 getInt16() const { return m_value; }

private:
    hkInt16 m_value;
};

using hkBool32 = hkUint32;
using hkBoolLL = hkUint64;

class hkBool {
public:
    HK_ALWAYS_INLINE hkBool() = default;
    // NOLINTNEXTLINE(google-explicit-constructor)
    HK_FORCE_INLINE constexpr hkBool(bool b) : m_bool(static_cast<char>(b)) {}

    HK_FORCE_INLINE constexpr explicit operator bool() const { return m_bool != 0; }
    // NOLINTNEXTLINE(google-explicit-constructor)
    HK_FORCE_INLINE constexpr operator hkBool32() const { return m_bool != 0; }

    HK_FORCE_INLINE constexpr hkBool& operator=(bool e) {
        m_bool = static_cast<char>(e);
        return *this;
    }

    HK_FORCE_INLINE constexpr hkBool operator==(bool e) const { return (m_bool != 0) == e; }
    HK_FORCE_INLINE constexpr hkBool operator!=(bool e) const { return (m_bool != 0) != e; }

private:
    char m_bool;
};

/// For storing an enum with a particular storage size when specifying the underlying type of the
/// enum is not an option.
template <typename Enum, typename Storage>
struct hkEnum {
    HK_ALWAYS_INLINE hkEnum() {}

    constexpr hkEnum(Enum value)  // NOLINT(google-explicit-constructor)
        : m_storage(static_cast<Storage>(value)) {}

    // NOLINTNEXTLINE(google-explicit-constructor)
    constexpr operator Enum() const { return static_cast<Enum>(m_storage); }

    constexpr hkEnum& operator=(Enum value) {
        m_storage = static_cast<Storage>(value);
        return *this;
    }

    constexpr bool operator==(Enum e) const { return m_storage == static_cast<Storage>(e); }
    constexpr bool operator!=(Enum e) const { return m_storage != static_cast<Storage>(e); }

    Storage m_storage;
};

template <typename, typename Storage>
class hkFlags {
public:
    HK_FORCE_INLINE hkFlags() {}
    HK_FORCE_INLINE constexpr explicit hkFlags(Storage s) : m_storage(s) {}

    HK_FORCE_INLINE constexpr void clear() { m_storage = 0; }
    HK_FORCE_INLINE constexpr void clear(Storage mask) { m_storage &= ~mask; }
    HK_FORCE_INLINE constexpr void setAll(Storage s) { m_storage = s; }

    HK_FORCE_INLINE constexpr void operator|=(Storage s) { m_storage |= s; }
    HK_FORCE_INLINE constexpr void operator^=(Storage s) { m_storage ^= s; }
    HK_FORCE_INLINE constexpr void operator&=(Storage s) { m_storage &= s; }

    HK_FORCE_INLINE constexpr void setWithMask(Storage s, Storage mask) {
        m_storage = (m_storage & ~mask) | (s & mask);
    }

    HK_FORCE_INLINE constexpr Storage get() const { return m_storage; }
    HK_FORCE_INLINE constexpr bool anyIsSet(Storage mask) const { return (m_storage & mask) != 0; }
    HK_FORCE_INLINE constexpr bool noneIsSet(Storage mask) const { return (m_storage & mask) == 0; }
    HK_FORCE_INLINE constexpr bool allAreSet(Storage mask) const {
        return (m_storage & mask) == mask;
    }

    HK_FORCE_INLINE constexpr bool operator==(const hkFlags& other) const {
        return other.m_storage == m_storage;
    }
    HK_FORCE_INLINE constexpr bool operator!=(const hkFlags& other) const {
        return other.m_storage != m_storage;
    }

private:
    Storage m_storage;
};

enum hkResultEnum {
    HK_SUCCESS = 0,
    HK_FAILURE = 1,
};

struct hkResult {
    HK_FORCE_INLINE hkResult() {}
    HK_FORCE_INLINE hkResult(hkResultEnum b) { m_enum = b; }

    HK_FORCE_INLINE hkResult& operator=(hkResultEnum e) {
        m_enum = e;
        return *this;
    }

    HK_FORCE_INLINE bool operator==(hkResultEnum e) const { return m_enum == e; }
    HK_FORCE_INLINE bool operator!=(hkResultEnum e) const { return m_enum != e; }

    HK_FORCE_INLINE bool isSuccess() const { return m_enum == HK_SUCCESS; }

    hkResultEnum m_enum;
};

inline bool operator==(hkResultEnum e, hkResult r) {
    return r.m_enum == e;
}
inline bool operator!=(hkResultEnum e, hkResult r) {
    return r.m_enum != e;
}

class hkFinishLoadedObjectFlag {
public:
    int m_finishing = 0;
};

#define hkSizeOf(A) int(sizeof(A))

HK_FORCE_INLINE hkLong hkGetByteOffset(const void* base, const void* pntr) {
    return hkLong(pntr) - hkLong(base);
}

template <typename T>
HK_ALWAYS_INLINE const T* hkAddByteOffsetConst(const T* base, hkLong offset) {
    return reinterpret_cast<const T*>(reinterpret_cast<hkUlong>(base) + offset);
}

template <typename T>
using hkAddConstPointer =
    std::conditional_t<std::is_pointer_v<T>,
                       std::add_pointer_t<std::add_const_t<std::remove_pointer_t<T>>>,
                       std::add_const_t<T>>;

template <typename T>
HK_ALWAYS_INLINE T hkSelectOther(hkAddConstPointer<T> a, T pairA, T pairB) {
    return reinterpret_cast<T>(hkUlong(a) ^ hkUlong(pairA) ^ hkUlong(pairB));
}

class hkClass;

struct hkVariant {
    void* m_object;
    const hkClass* m_class;
};

#define HK_DECLARE_REFLECTION() static const hkClass& staticClass();
