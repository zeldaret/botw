/**
 * @file ddl.h
 * @brief DDL Declaration Implementation.
 */

#pragma once

#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class DDLDeclarations : public nn::nex::RootObject {
public:
    DDLDeclarations(bool);

    virtual ~DDLDeclarations();

    virtual void Init() = 0;

    void RegisterIfRequired();
    void Unregister();
    static void UnregisterAll();
    void LoadAll();
    void Load();
    void UnloadAll();
    void Unload();
    void ResetDOClassIDs();

    u32 mNumDecsLoaded;  // _8
    u8 DDLDeclarations_xC;
    u8 _D;  // padding
    u8 _E;  // ^^
    u8 _F;  // ^^
    u64 _10;
    bool _18;

    static nn::nex::DDLDeclarations* s_pFirstDDLDecl;
};
};  // namespace nex
};  // namespace nn