#pragma once

#include <prim/seadSafeString.h>

namespace ksys::ui {

int getPorchNum(const sead::SafeString& name);
void initRupeeCounter();
bool isRupeeCounterActive();

}  // namespace ksys::ui
