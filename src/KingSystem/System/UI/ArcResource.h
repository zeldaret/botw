#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/System/UI/ArcResourceMgr.h"

namespace ksys::ui {

class ArcResourceMgr;

class ArcResource : public sead::IDisposer {
private:
    void* _20;
    void* _28;
    ArcResourceMgr* mArcResourceMgr;
    sead::FixedSafeString<0x40> mName;
    u8* mData;
    void* mResource;
};

}
