/**
 * @file ro.h
 * @brief Dynamic module API.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace ro {

namespace rtld {
struct ModuleObject;  // TODO find this object and implement it. Original `#include` name:
                      // ModuleObject.hpp, full path name: nn::ro::rtld::ModuleObject
}

class Module {
public:
    rtld::ModuleObject* ModuleObject;
    u32 State;
    void* NroPtr;
    void* BssPtr;
    void* _x20;
    void* SourceBuffer;
    char Name[256]; /* Created by retype action */
    u8 _x130;
    u8 _x131;
    bool isLoaded;  // bool
};

struct ModuleId {
    u8 build_id[0x20];
};

struct NroHeader {
    u32 entrypoint_insn;
    u32 mod_offset;
    u8 _x8[0x8];
    u32 magic;
    u8 _x14[0x4];
    u32 size;
    u8 reserved_1C[0x4];
    u32 text_offset;
    u32 text_size;
    u32 ro_offset;
    u32 ro_size;
    u32 rw_offset;
    u32 rw_size;
    u32 bss_size;
    u8 _x3C[0x4];
    ModuleId module_id;
    u8 _x60[0x20];
};
static_assert(sizeof(NroHeader) == 0x80, "NroHeader definition!");

struct ProgramId {
    u64 value;

    inline explicit operator u64() const { return this->value; }
};

struct NrrHeader {
    u32 magic;
    u8 _x4[0xC];
    u64 program_id_mask;
    u64 program_id_pattern;
    u8 _x20[0x10];
    u8 modulus[0x100];
    u8 fixed_key_signature[0x100];
    u8 nrr_signature[0x100];
    ProgramId program_id;
    u32 size;
    u8 type; /* 7.0.0+ */
    u8 _x33D[3];
    u32 hashes_offset;
    u32 num_hashes;
    u8 _x348[8];
};
static_assert(sizeof(NrrHeader) == 0x350, "NrrHeader definition!");

struct RegistrationInfo {
    enum State {
        State_Unregistered,
        State_Registered,
    };
    State state;
    NrrHeader* nrrPtr;
    u64 _x10;
    u64 _x18;
};

enum BindFlag {
    BindFlag_Now = BIT(0),
    BindFlag_Lazy = BIT(1),
};

Result Initialize();

Result LookupSymbol(uintptr_t* pOutAddress, const char* name);

Result LookupModuleSymbol(uintptr_t* pOutAddress, const Module* pModule, const char* name);
Result LoadModule(Module* pOutModule, const void* pImage, void* buffer, size_t bufferSize,
                  int flag);
// Result LoadModule(Module *pOutModule, const void *pImage, void *buffer, size_t bufferSize,int
// flag, bool isNotReferenced);
Result UnloadModule(Module*);
Result GetBufferSize(size_t*, const void*);

Result RegisterModuleInfo(RegistrationInfo*, void const*);
Result RegisterModuleInfo(RegistrationInfo*, void const*, u32);
Result UnregisterModuleInfo(RegistrationInfo*, void const*);
};  // namespace ro

};  // namespace nn