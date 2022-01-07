#pragma once

#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

#define HK_UFLOAT8_MAX_VALUE 256
#define hkUFloat8_eps 0.01f
#define hkUFloat8_maxValue 1000000.0f

class hkUFloat8 {
public:
    enum {
        MAX_VALUE = HK_UFLOAT8_MAX_VALUE,

        // Constants used in compressing / decompressing the values table
        ENCODED_EXPONENT_BITS = 5,
        ENCODED_MANTISSA_BITS = (16 - ENCODED_EXPONENT_BITS),
        ENCODED_EXPONENT_BIAS = 119,
        ENCODED_EXPONENT_MASK = (1 << ENCODED_EXPONENT_BITS) - 1,
        ENCODED_MANTISSA_MASK = (1 << ENCODED_MANTISSA_BITS) - 1,

        FLOAT_MANTISSA_BITS = 23,
        FLOAT_MANTISSA_MASK = (1 << FLOAT_MANTISSA_BITS) - 1,

        ENCODE_MANTISSA_SHIFT = (FLOAT_MANTISSA_BITS - ENCODED_MANTISSA_BITS),
        DECODE_EXPONENT_BIAS =
            (ENCODED_EXPONENT_BIAS << (FLOAT_MANTISSA_BITS - ENCODE_MANTISSA_SHIFT)),
    };

    HK_FORCE_INLINE hkUFloat8() {}
    HK_FORCE_INLINE hkUFloat8(float f) { *this = f; }   // NOLINT(google-explicit-constructor)
    HK_FORCE_INLINE hkUFloat8(double d) { *this = d; }  // NOLINT(google-explicit-constructor)

    hkUFloat8& operator=(const double& dv);
    hkUFloat8& operator=(const float& fv);

    HK_FORCE_INLINE bool isZero() const { return m_value == 0; }
    HK_FORCE_INLINE void setZero() { m_value = 0; }

    HK_FORCE_INLINE bool isMax() const { return m_value == 255; }
    HK_FORCE_INLINE void setMax() { m_value = 255; }

    HK_FORCE_INLINE hkBool operator==(const hkUFloat8& other) const {
        return m_value == other.m_value;
    }

    HK_FORCE_INLINE void setArithmeticMean(const hkUFloat8& a, const hkUFloat8& b) {
        m_value = hkUint8((int(a.m_value) + int(b.m_value)) >> 1);
    }

    // NOLINTNEXTLINE(google-explicit-constructor)
    HK_FORCE_INLINE operator float() const { return decodeFloat(getEncodedFloat(m_value)); }

    static HK_FORCE_INLINE float decodeFloat(const hkUint16 i) {
        const int intExpo = (i + hkUFloat8::DECODE_EXPONENT_BIAS)
                            << hkUFloat8::ENCODE_MANTISSA_SHIFT;
        union {
            const float* f;
            const int* i;
        } f2i;
        f2i.i = &intExpo;
        return i ? *f2i.f : 0.0f;
    }

    hkUint8 m_value;

protected:
    static hkUint16 getEncodedFloat(hkUint8 index);
};
