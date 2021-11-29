#pragma once

class hkVector4 {
public:
    hkVector4() {}
    hkVector4(hkReal x, hkReal y, hkReal z, hkReal w = 0) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
        v[3] = w;
    }
    m128 v;

    void sub_7100FABE80(const hkVector4&, const hkVector4&);
};
