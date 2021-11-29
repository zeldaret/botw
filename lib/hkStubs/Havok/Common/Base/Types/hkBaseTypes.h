#pragma once

typedef float hkFloat32;
typedef double hkDouble64;
typedef hkFloat32 hkReal;

typedef signed char hkChar;
typedef signed char hkInt8;
typedef signed short hkInt16;
typedef signed int hkInt32;

typedef unsigned char hkUchar;
typedef unsigned char hkUint8;
typedef unsigned short hkUint16;
typedef unsigned int hkUint32;

typedef unsigned long long hkUint64;

typedef __attribute((vector_size(16))) float __m128;

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
