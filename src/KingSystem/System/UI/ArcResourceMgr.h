#pragma once

#include <container/seadTList.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::ui {

class ArcResourceMgr {
public:
    ArcResourceMgr() = default;
    virtual ~ArcResourceMgr();

private:
    // TODO: fields
    /* sead::TList */
    char list[0x10];
    int _18 = 0;
    int _1c = 0x20;
};
KSYS_CHECK_SIZE_NX150(ArcResourceMgr, 0x20);

}  // namespace ksys::ui
