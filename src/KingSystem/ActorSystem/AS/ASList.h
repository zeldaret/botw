#pragma once
#include "KingSystem/ActorSystem/actActor.h"
namespace ksys::as {
class ASList{
public:
void DelayStateChangeMaybe( f32 a2, f32 a3, const sead::SafeString& a4, int a5, int a6, bool a7);
bool GoLimpFromHeadShotMaybe(u32 a1, const sead::SafeString& SafeString, u32 a2) ;
};

} //namespace ksys::as
