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
