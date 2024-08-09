#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {
namespace res {
class Handle;
}
namespace ui {

class ArcResourceMgr;

class ArcResource : public sead::IDisposer {
public:
    ArcResource() = default;

    void init(ArcResourceMgr* mgr, const sead::SafeString& name, u8* data, res::Handle* handle);
private:
    void* _20;
    void* _28;
    ArcResourceMgr* mArcResourceMgr;
    sead::FixedSafeString<0x40> mName;
    u8* mData;
    void* mFile;
    res::Handle* mHandle;
};
KSYS_CHECK_SIZE_NX150(ArcResource, 0xA8);

}
}
