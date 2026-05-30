#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

// The virtual destructor definition ensures that the vtable is correctly instantiated
// by the compiler, avoiding undefined virtual table linker errors.
FxMgr::~FxMgr() = default;

// Stub definition for activating the slow motion audio effects.
// This is currently left empty as the sound module is not fully recompiled,
// but the symbol is vital for binary-matching and branch displacement calculation.
void FxMgr::setSlowTime(bool is_4) {}

// Stub definition for shutting down the active slow motion audio filters.
// Just like setSlowTime, this matches the original signature and allows the game ELF to compile.
void FxMgr::endSlowTime() {}

}  // namespace ksys::snd