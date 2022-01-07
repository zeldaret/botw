#pragma once

#include <Havok/Common/Base/Container/String/hkString.h>
#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>

class hkStringPtr {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkStringPtr)

    enum StringFlags {
        OWNED_FLAG = 0x1,
    };

    hkStringPtr();
    hkStringPtr(const char* string);  // NOLINT(google-explicit-constructor)
    hkStringPtr(const char* string, int len);
    hkStringPtr(const hkStringPtr& strRef);
    explicit hkStringPtr(hkFinishLoadedObjectFlag f);

    ~hkStringPtr();

    inline const char* cString() const;
    inline operator const char*() const;  // NOLINT(google-explicit-constructor)

    hkStringPtr& operator=(const char* s);
    hkStringPtr& operator=(const hkStringPtr& s);

    int getLength() const;

    inline char operator[](int idx) const;

    void printf(const char* fmt, ...);
    void set(const char* s, int len = -1);
    void setPointerAligned(const char* s);

    inline hkBool32 operator==(const char* s) const;
    inline hkBool32 operator!=(const char* s) const;
    inline hkBool32 startsWith(const char* s) const;
    inline hkBool32 endsWith(const char* s) const;
    inline int compareTo(const char* rhs) const;

private:
    const char* m_stringAndFlag;
};

inline const char* hkStringPtr::cString() const {
    return reinterpret_cast<const char*>(uintptr_t(m_stringAndFlag) & ~OWNED_FLAG);
}

inline hkStringPtr::operator const char*() const {
    return cString();
}

inline char hkStringPtr::operator[](int idx) const {
    return cString()[idx];
}

inline hkBool32 hkStringPtr::operator==(const char* s) const {
    return compareTo(s) == 0;
}

inline hkBool32 hkStringPtr::operator!=(const char* s) const {
    return compareTo(s) != 0;
}

inline hkBool32 hkStringPtr::startsWith(const char* s) const {
    return hkString::beginsWith(cString(), s);
}

inline hkBool32 hkStringPtr::endsWith(const char* s) const {
    return hkString::endsWith(cString(), s);
}

inline int hkStringPtr::compareTo(const char* rhs) const {
    const char* lhs = cString();
    if (lhs && rhs)
        return hkString::strCmp(lhs, rhs);
    if (lhs != nullptr)
        return 1;
    if (rhs != nullptr)
        return -1;
    return 0;
}
