#pragma once

#include <Havok/Physics/Dynamics/World/hkpWorldEntity.h>

class hkpMotion {
public:
    virtual ~hkpMotion();
    hkUchar _0[0xc0];

    /* 0xc8 */ hkHalf m_motionState__m_timeFactor;
    /*       */ hkUchar _cc[0x128 - 0xcc];
    /* 0x128 */ void* _128;
};

struct hkpMaxSizeMotion : hkpMotion {
    hkUchar fill[0x140 - sizeof(hkpMotion)];
};  // 0x140

class hkpEntity : public hkpWorldEntity {
public:
    virtual ~hkpEntity();

    /*       */ hkUchar _133[0x150 - 0x133];
    /* 0x150 */ hkpMaxSizeMotion m_motion;
};
