/*
 *  Copyright (c) 2020 The Starlight Project
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#pragma once

#include <basis/seadTypes.h>

namespace sead
{
class Color4f
{
public:
    Color4f() = default;
    Color4f(f32 r, f32 g, f32 b, f32 a) : r(r), g(g), b(b), a(a) {}

    static Color4f lerp(const Color4f& color1, const Color4f& color2, f32 t);

    void setLerp(const Color4f& color1, const Color4f& color2, f32 t);
    // This should actually be called setGammaCorrection...
    void setGammaCollection(const Color4f& value, f32 gamma);
    void adjustOverflow();

    Color4f& operator+=(const Color4f& rhs);
    Color4f& operator-=(const Color4f& rhs);
    Color4f& operator*=(const Color4f& rhs);
    Color4f& operator/=(const Color4f& rhs);
    Color4f& operator+=(f32 x);
    Color4f& operator-=(f32 x);
    Color4f& operator*=(f32 x);
    Color4f& operator/=(f32 x);

    friend Color4f operator+(const Color4f& lhs, const Color4f& rhs);
    friend Color4f operator-(const Color4f& lhs, const Color4f& rhs);
    friend Color4f operator*(const Color4f& lhs, const Color4f& rhs);
    friend Color4f operator/(const Color4f& lhs, const Color4f& rhs);
    friend Color4f operator+(const Color4f& lhs, f32 x);
    friend Color4f operator-(const Color4f& lhs, f32 x);
    friend Color4f operator*(const Color4f& lhs, f32 x);
    friend Color4f operator/(const Color4f& lhs, f32 x);
    friend bool operator==(const Color4f& lhs, const Color4f& rhs);

    f32 r = cElementMin;
    f32 g = cElementMin;
    f32 b = cElementMin;
    f32 a = cElementMax;

    static const f32 cElementMax;
    static const f32 cElementMin;

    static const Color4f cBlack;
    static const Color4f cGray;
    static const Color4f cWhite;
    static const Color4f cRed;
    static const Color4f cGreen;
    static const Color4f cBlue;
    static const Color4f cYellow;
    static const Color4f cMagenta;
    static const Color4f cCyan;
};

class Color4u8
{
public:
    Color4u8() = default;
    Color4u8(u8 r, u8 g, u8 b, u8 a) : a(a), b(b), g(g), r(r) {}

    static Color4u8 lerp(const Color4u8& color1, const Color4u8& color2, f32 t);

    void setf(f32 r, f32 g, f32 b, f32 a);
    void setLerp(const Color4u8& color1, const Color4u8& color2, f32 t);
    // This should actually be called setGammaCorrection...
    void setGammaCollection(const Color4u8& value, f32 gamma);

    Color4u8& operator+=(const Color4u8& rhs);
    Color4u8& operator-=(const Color4u8& rhs);
    Color4u8& operator*=(const Color4u8& rhs);
    Color4u8& operator/=(const Color4u8& rhs);
    Color4u8& operator|=(const Color4u8& rhs);
    Color4u8& operator&=(const Color4u8& rhs);
    Color4u8& operator+=(u8 x);
    Color4u8& operator-=(u8 x);
    Color4u8& operator*=(f32 x);
    Color4u8& operator/=(f32 x);
    Color4u8& operator|=(u8 x);
    Color4u8& operator&=(u8 x);

    friend Color4u8 operator+(const Color4u8& lhs, const Color4u8& rhs);
    friend Color4u8 operator-(const Color4u8& lhs, const Color4u8& rhs);
    friend Color4u8 operator*(const Color4u8& lhs, const Color4u8& rhs);
    friend Color4u8 operator/(const Color4u8& lhs, const Color4u8& rhs);
    friend Color4u8 operator+(const Color4u8& lhs, u8 x);
    friend Color4u8 operator-(const Color4u8& lhs, u8 x);
    friend Color4u8 operator*(const Color4u8& lhs, f32 x);
    friend Color4u8 operator/(const Color4u8& lhs, f32 x);
    friend Color4u8 operator&(const Color4u8& lhs, u8 x);
    friend Color4u8 operator|(const Color4u8& lhs, u8 x);
    friend bool operator==(const Color4u8& lhs, const Color4u8& rhs);

    u8 a;
    u8 b;
    u8 g;
    u8 r;

    static const u8 cElementMax;
    static const u8 cElementMin;

    static const Color4u8 cBlack;
    static const Color4u8 cGray;
    static const Color4u8 cWhite;
    static const Color4u8 cRed;
    static const Color4u8 cGreen;
    static const Color4u8 cBlue;
    static const Color4u8 cYellow;
    static const Color4u8 cMagenta;
    static const Color4u8 cCyan;

private:
    template <typename Callable>
    Color4u8& apply_(Callable fn)
    {
        fn(&Color4u8::r);
        fn(&Color4u8::g);
        fn(&Color4u8::b);
        fn(&Color4u8::a);
        return *this;
    }
};
}  // namespace sead
