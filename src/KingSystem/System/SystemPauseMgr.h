#pragma once

#include "KingSystem/Utils/Types.h"

namespace ksys {

class SystemPauseMgr {
public:
    SystemPauseMgr();
    virtual ~SystemPauseMgr();

    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual bool m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual bool m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();

    bool get8() const { return _8; }

private:
    bool _8 = true;
};
KSYS_CHECK_SIZE_NX150(SystemPauseMgr, 0x10);

}  // namespace ksys
