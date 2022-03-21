/**
 * @file plugin.h
 * @brief Plugin interface for NEX.
 */

#pragma once

#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class PluginObject : public nn::nex::RootObject {};

class Plugin : public nn::nex::RootObject {
public:
    Plugin();

    virtual ~Plugin();

    // there's a bunch of pure virtual methods but nothing ever inherits this class...
    virtual bool Initalize();
    virtual void ThreadAttach();
    virtual void ThreadDetach();
    virtual void Destroy();

    void SetLibrary(void*);

    void* mLibrary;  // _8s

    static nn::nex::Plugin* s_pInstance;
};
};  // namespace nex
};  // namespace nn