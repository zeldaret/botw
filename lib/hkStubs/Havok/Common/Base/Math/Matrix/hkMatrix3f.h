#pragma once

class hkMatrix3f {
public:
    hkMatrix3f() {}  // NOLINT(modernize-use-equals-default)

    HK_FORCE_INLINE hkMatrix3f(const hkMatrix3f& other);
    HK_FORCE_INLINE hkMatrix3f& operator=(const hkMatrix3f& other);

    HK_FORCE_INLINE hkFloat32& operator()(int row, int col);
    HK_FORCE_INLINE const hkFloat32& operator()(int row, int col) const;
    template <int Row, int Col>
    HK_FORCE_INLINE hkSimdFloat32 get() const;
    template <int Row, int Col>
    HK_FORCE_INLINE void set(hkSimdFloat32Parameter s);

    HK_FORCE_INLINE hkVector4f& getColumn(int i);
    HK_FORCE_INLINE const hkVector4f& getColumn(int i) const;
    template <int I>
    HK_FORCE_INLINE const hkVector4f& getColumn() const;

    HK_FORCE_INLINE void getRows(hkVector4f& r0, hkVector4f& r1, hkVector4f& r2) const;

    HK_FORCE_INLINE void setZero();
    HK_FORCE_INLINE void setIdentity();

    void setMul(const hkMatrix3f& a, const hkMatrix3f& b);
    HK_FORCE_INLINE void _setMul(const hkMatrix3f& a, const hkMatrix3f& b);
    void mul(const hkMatrix3f& a);

    hkVector4f m_col0;
    hkVector4f m_col1;
    hkVector4f m_col2;
};
