#pragma once

#include <Havok/Physics2012/Collide/Shape/hkpShape.h>

class hkpWorldEntity : public hkReferencedObject {
public:
    virtual ~hkpWorldEntity() {}

    void setUserData(void* data) { m_userData = data; }

    void setName(const char* name) { m_name = name; }

    /*       */ hkUchar _8[0x18 - 0x8];
    /* 0x018 */ void* m_userData;
    /*       */ hkUchar _20[0x88 - 0x20];
    /* 0x088 */ hkReal _88;
    /*       */ hkUchar _8c[0xb0 - 0x8c];
    /* 0x0b0 */ hkStringPtr m_name;
    /*       */ hkUchar _b8[0x132 - 0xb8];
    /* 0x132 */ hkUchar _132;
};
