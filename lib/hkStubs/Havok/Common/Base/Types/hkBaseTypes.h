#pragma once

using hkFloat32 = float;
using hkDouble64 = double;
using hkReal = hkFloat32;

using hkChar = signed char;
using hkInt8 = signed char;
using hkInt16 = signed short;
using hkInt32 = signed int;

using hkUchar = unsigned char;
using hkUint8 = unsigned char;
using hkUint16 = unsigned short;
using hkUint32 = unsigned int;

using hkUint64 = unsigned long long;
using m128 = __attribute((vector_size(16))) float;

class hkHalf {
public:
    hkHalf() {}

    explicit hkHalf(const float& f) {
        int t = ((const int*)&f)[0];
        m_value = hkInt16(t >> 16);
    }

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

/// For storing an enum with a particular storage size when specifying the underlying type of the
/// enum is not an option.
template <typename Enum, typename Storage>
struct hkEnum {
    HK_ALWAYS_INLINE hkEnum() {}

    hkEnum(Enum value) { *this = value; }  // NOLINT(google-explicit-constructor)

    // NOLINTNEXTLINE(google-explicit-constructor)
    operator Enum() const { return static_cast<Enum>(m_storage); }

    hkEnum& operator=(Enum value) {
        m_storage = static_cast<Storage>(value);
        return *this;
    }

    bool operator==(Enum e) const { return m_storage == static_cast<Storage>(e); }
    bool operator!=(Enum e) const { return m_storage != static_cast<Storage>(e); }

    Storage m_storage;
};

template <typename, typename Storage>
class hkFlags {
public:
    HK_FORCE_INLINE hkFlags() {}
    HK_FORCE_INLINE explicit hkFlags(Storage s) : m_storage(s) {}

    HK_FORCE_INLINE void clear() { m_storage = 0; }
    HK_FORCE_INLINE void clear(Storage mask) { m_storage &= ~mask; }
    HK_FORCE_INLINE void setAll(Storage s) { m_storage = s; }

    HK_FORCE_INLINE void operator|=(Storage s) { m_storage |= s; }
    HK_FORCE_INLINE void operator^=(Storage s) { m_storage ^= s; }
    HK_FORCE_INLINE void operator&=(Storage s) { m_storage &= s; }

    HK_FORCE_INLINE void setWithMask(Storage s, Storage mask) {
        m_storage = (m_storage & ~mask) | (s & mask);
    }

    HK_FORCE_INLINE Storage get() const { return m_storage; }
    HK_FORCE_INLINE bool anyIsSet(Storage mask) const { return (m_storage & mask) != 0; }
    HK_FORCE_INLINE bool noneIsSet(Storage mask) const { return (m_storage & mask) == 0; }
    HK_FORCE_INLINE bool allAreSet(Storage mask) const { return (m_storage & mask) == mask; }

    HK_FORCE_INLINE bool operator==(const hkFlags& other) const {
        return other.m_storage == m_storage;
    }
    HK_FORCE_INLINE bool operator!=(const hkFlags& other) const {
        return other.m_storage != m_storage;
    }

private:
    Storage m_storage;
};