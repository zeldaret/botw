#pragma once

#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>

class hkStringPtr {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkStringPtr)

    enum StringFlags {
        OWNED_FLAG = 0x1,
    };

    hkStringPtr();
    explicit hkStringPtr(hkFinishLoadedObjectFlag f);

    inline const char* cString() const;
    inline operator const char*() const;

    hkStringPtr& operator=(const char* s);

private:
    const char* m_stringAndFlag;
};

inline const char* hkStringPtr::cString() const {
    return reinterpret_cast<const char*>(uintptr_t(m_stringAndFlag) & ~OWNED_FLAG);
}

inline hkStringPtr::operator const char*() const {
    return cString();
}
