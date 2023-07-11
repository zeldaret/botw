#pragma once
#include "KingSystem/ActorSystem/actActor.h"
namespace ksys::as {
class ASList{
public:
void StartAnimationMaybe( f32 a2, f32 a3, const sead::SafeString& animation_ASDefine, int buffer_size, int string_length, bool a7);
bool GoLimpFromHeadShotMaybe(u32 a1, const sead::SafeString& SafeString, u32 a2) ;
};

} //namespace ksys::as
