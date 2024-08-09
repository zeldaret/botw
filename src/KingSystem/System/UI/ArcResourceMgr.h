#pragma once

#include <container/seadTList.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class ExpHeap;
}

namespace ksys::ui {

class ArcResourceMgr {
public:
    ArcResourceMgr() = default;
    virtual ~ArcResourceMgr();

    virtual void loadArchive(sead::ExpHeap* heap, const sead::SafeString& path);

private:
    // TODO: fields
    /* sead::TList */
    char list[0x10];
    int _18 = 0;
    int _1c = 0x20;
};
KSYS_CHECK_SIZE_NX150(ArcResourceMgr, 0x20);

}  // namespace ksys::ui
