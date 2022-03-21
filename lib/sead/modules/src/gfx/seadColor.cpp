#include <algorithm>
#include <cmath>

#include <gfx/seadColor.h>
#include <math/seadMathCalcCommon.h>

namespace sead
{
const Color4f Color4f::cBlack(0.0f, 0.0f, 0.0f, 1.0f);
const Color4f Color4f::cGray(0.5f, 0.5f, 0.5f, 1.0f);
const Color4f Color4f::cWhite(1.0f, 1.0f, 1.0f, 1.0f);
const Color4f Color4f::cRed(1.0f, 0.0f, 0.0f, 1.0f);
const Color4f Color4f::cGreen(0.0f, 1.0f, 0.0f, 1.0f);
const Color4f Color4f::cBlue(0.0f, 0.0f, 1.0f, 1.0f);
const Color4f Color4f::cYellow(1.0f, 1.0f, 0.0f, 1.0f);
const Color4f Color4f::cMagenta(1.0f, 0.0f, 1.0f, 1.0f);
const Color4f Color4f::cCyan(0.0f, 1.0f, 1.0f, 1.0f);
const f32 Color4f::cElementMax = 1.0f;
const f32 Color4f::cElementMin = 0.0f;

Color4f Color4f::lerp(const Color4f& color1, const Color4f& color2, f32 t)
{
    t = sead::Mathf::clamp(t, cElementMin, cElementMax);
    const f32 a = sead::lerp(color1.a, color2.a, t);
    const f32 r = sead::lerp(color1.r, color2.r, t);
    const f32 g = sead::lerp(color1.g, color2.g, t);
    const f32 b = sead::lerp(color1.b, color2.b, t);
    return {r, g, b, a};
}

void Color4f::setLerp(const Color4f& color1, const Color4f& color2, f32 t)
{
    t = sead::Mathf::clamp(t, cElementMin, cElementMax);
    a = sead::lerp(color1.a, color2.a, t);
    r = sead::lerp(color1.r, color2.r, t);
    g = sead::lerp(color1.g, color2.g, t);
    b = sead::lerp(color1.b, color2.b, t);
}

void Color4f::setGammaCollection(const Color4f& value, f32 gamma)
{
    a = value.a;
    r = std::pow(value.r, gamma);
    g = std::pow(value.g, gamma);
    b = std::pow(value.b, gamma);
}

void Color4f::adjustOverflow()
{
    r = sead::Mathf::clamp(r, cElementMin, cElementMax);
    g = sead::Mathf::clamp(g, cElementMin, cElementMax);
    b = sead::Mathf::clamp(b, cElementMin, cElementMax);
    a = sead::Mathf::clamp(a, cElementMin, cElementMax);
}

#define SEAD_COLOR4F_OPERATORS(OP, OP2)                                                            \
    Color4f& Color4f::operator OP(const Color4f& rhs)                                              \
    {                                                                                              \
        r OP rhs.r;                                                                                \
        g OP rhs.g;                                                                                \
        b OP rhs.b;                                                                                \
        a OP rhs.a;                                                                                \
        return *this;                                                                              \
    }                                                                                              \
    Color4f& Color4f::operator OP(f32 x)                                                           \
    {                                                                                              \
        r OP x;                                                                                    \
        g OP x;                                                                                    \
        b OP x;                                                                                    \
        a OP x;                                                                                    \
        return *this;                                                                              \
    }                                                                                              \
    Color4f operator OP2(const Color4f& lhs, const Color4f& rhs)                                   \
    {                                                                                              \
        Color4f result = lhs;                                                                      \
        result OP rhs;                                                                             \
        return result;                                                                             \
    }                                                                                              \
    Color4f operator OP2(const Color4f& lhs, f32 x)                                                \
    {                                                                                              \
        Color4f result = lhs;                                                                      \
        result OP x;                                                                               \
        return result;                                                                             \
    }

SEAD_COLOR4F_OPERATORS(+=, +)
SEAD_COLOR4F_OPERATORS(-=, -)
SEAD_COLOR4F_OPERATORS(*=, *)
SEAD_COLOR4F_OPERATORS(/=, /)

bool operator==(const Color4f& lhs, const Color4f& rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

const Color4u8 Color4u8::cBlack(0, 0, 0, 255);
const Color4u8 Color4u8::cGray(128, 128, 128, 255);
const Color4u8 Color4u8::cWhite(255, 255, 255, 255);
const Color4u8 Color4u8::cRed(255, 0, 0, 255);
const Color4u8 Color4u8::cGreen(0, 255, 0, 255);
const Color4u8 Color4u8::cBlue(0, 0, 255, 255);
const Color4u8 Color4u8::cYellow(255, 255, 0, 255);
const Color4u8 Color4u8::cMagenta(255, 0, 255, 255);
const Color4u8 Color4u8::cCyan(0, 255, 255, 255);
const u8 Color4u8::cElementMax = 255;
const u8 Color4u8::cElementMin = 0;

// NON_MATCHING: but semantically equivalent (setLerp is matching after all)
Color4u8 Color4u8::lerp(const Color4u8& color1, const Color4u8& color2, f32 t)
{
    Color4u8 result = color1;
    result.setLerp(color1, color2, t);
    return result;
}

void Color4u8::setf(f32 fr, f32 fg, f32 fb, f32 fa)
{
    r = sead::Mathf::clamp(fr, 0.0f, 1.0f) * 255.0f;
    g = sead::Mathf::clamp(fg, 0.0f, 1.0f) * 255.0f;
    b = sead::Mathf::clamp(fb, 0.0f, 1.0f) * 255.0f;
    a = sead::Mathf::clamp(fa, 0.0f, 1.0f) * 255.0f;
}

void Color4u8::setLerp(const Color4u8& color1, const Color4u8& color2, f32 t)
{
    t = sead::Mathf::clamp(t, 0.0f, 1.0f);
    a = sead::lerp(color1.a, color2.a, t);
    r = sead::lerp(color1.r, color2.r, t);
    g = sead::lerp(color1.g, color2.g, t);
    b = sead::lerp(color1.b, color2.b, t);
}

void Color4u8::setGammaCollection(const Color4u8& value, f32 gamma)
{
    a = value.a;
    r = sead::Mathf::clamp(std::pow(f32(value.r) / 255.0f, gamma), 0.0f, 1.0f) * 255.0f;
    g = sead::Mathf::clamp(std::pow(f32(value.g) / 255.0f, gamma), 0.0f, 1.0f) * 255.0f;
    b = sead::Mathf::clamp(std::pow(f32(value.b) / 255.0f, gamma), 0.0f, 1.0f) * 255.0f;
}

#define SEAD_Color4u8_OPERATORS(OP, OP2)                                                           \
    Color4u8 operator OP2(const Color4u8& lhs, const Color4u8& rhs)                                \
    {                                                                                              \
        Color4u8 result = lhs;                                                                     \
        result OP rhs;                                                                             \
        return result;                                                                             \
    }                                                                                              \
    Color4u8 operator OP2(const Color4u8& lhs, u8 x)                                               \
    {                                                                                              \
        Color4u8 result = lhs;                                                                     \
        result OP x;                                                                               \
        return result;                                                                             \
    }

SEAD_Color4u8_OPERATORS(+=, +);
SEAD_Color4u8_OPERATORS(-=, -);
SEAD_Color4u8_OPERATORS(*=, *);
SEAD_Color4u8_OPERATORS(/=, /);
SEAD_Color4u8_OPERATORS(|=, |);
SEAD_Color4u8_OPERATORS(&=, &);

Color4u8& Color4u8::operator+=(const Color4u8& rhs)
{
    return apply_([&](auto m) { this->*m = std::min<u32>(0xFF, u32(this->*m) + rhs.*m); });
}

Color4u8& Color4u8::operator-=(const Color4u8& rhs)
{
    return apply_([&](auto m) { this->*m = this->*m >= rhs.*m ? this->*m - rhs.*m : 0; });
}

Color4u8& Color4u8::operator*=(const Color4u8& rhs)
{
    return apply_([&](auto m) { this->*m = this->*m * rhs.*m / 0xFF; });
}

Color4u8& Color4u8::operator/=(const Color4u8& rhs)
{
    return apply_([&](auto m) {
        if (rhs.*m)
            this->*m = std::min<u32>(0xFF, 255 * u32(this->*m) / u32(rhs.*m));
        else
            this->*m = 255;
    });
}

Color4u8& Color4u8::operator|=(const Color4u8& rhs)
{
    return apply_([&](auto m) { this->*m = this->*m | rhs.*m; });
}

Color4u8& Color4u8::operator&=(const Color4u8& rhs)
{
    return apply_([&](auto m) { this->*m = this->*m & rhs.*m; });
}

bool operator==(const Color4u8& lhs, const Color4u8& rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

Color4u8& Color4u8::operator+=(u8 x)
{
    return apply_([&](auto m) { this->*m = std::min<u32>(0xFF, x + u32(this->*m)); });
}

Color4u8& Color4u8::operator-=(u8 x)
{
    return apply_([&](auto m) { this->*m = this->*m >= x ? this->*m - x : 0; });
}

// NON_MATCHING: regalloc, one harmless reordering
Color4u8& Color4u8::operator*=(float x)
{
    return apply_([&](auto m) { this->*m = std::max(0.0f, this->*m * x); });
}

Color4u8& Color4u8::operator/=(float x)
{
    return apply_([&](auto m) {
        if (x == 0.0f)
        {
            this->*m = 255;
            return;
        }
        const float q = float(this->*m) / x;
        if (q < 0.0f)
            this->*m = 0;
        else if (q > 255.0f)
            this->*m = 255;
        else
            this->*m = q;
    });
}

Color4u8& Color4u8::operator|=(u8 x)
{
    return apply_([&](auto m) { this->*m = this->*m | x; });
}

Color4u8& Color4u8::operator&=(u8 x)
{
    return apply_([&](auto m) { this->*m = this->*m & x; });
}

// NON_MATCHING: see Color4u8::operator*(f32)
Color4u8 operator*(const Color4u8& lhs, f32 x)
{
    Color4u8 result = lhs;
    result *= x;
    return result;
}

// NON_MATCHING: equivalent but affected by the same issue as Color4u8::lerp
Color4u8 operator/(const Color4u8& lhs, f32 x)
{
    Color4u8 result = lhs;
    result /= x;
    return result;
}
}  // namespace sead
