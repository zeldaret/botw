#pragma once

#include <prim/seadSafeString.h>

namespace ksys::ui {

int getPorchNum(const sead::SafeString& name);
int getItemValue(const sead::SafeString& name);
void initRupeeCounter();
bool isRupeeCounterActive();
void applyScreenFade(float progress);

}  // namespace ksys::ui
