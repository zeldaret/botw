#pragma once

#include "hostio/seadHostIOEventListener.h"
#include "prim/seadBitFlag.h"
#include "prim/seadSafeString.h"

namespace sead
{
class Heap;

namespace hostio
{
class Context;
class GenEvent;

class Reflexible : public NodeEventListener
{
public:
    enum class NodeClassType
    {
        /// sead::hostio::Reflexible
        Reflexible = 0,
        /// sead::hostio::Node
        Node = 1,
        /// Other classes
        Other = 2,
    };

    virtual NodeClassType getNodeClassType() const { return NodeClassType::Reflexible; }

    enum class AllocFlg
    {
        Name = 1u << 0u,
        Meta = 1u << 1u,
    };

#ifdef SEAD_DEBUG
    Reflexible();
    Reflexible(Heap* heap, IDisposer::HeapNullOption heap_null_option);
    ~Reflexible() override { disposeHostIOImpl_(); }

    void listenNodeEvent([[maybe_unused]] const NodeEvent* event) override {}
    virtual void genMessage([[maybe_unused]] Context* context) {}
    virtual SafeString getMetaFilename() { return SafeString::cEmptyString; }
    virtual void genObjectInfo(const GenEvent* event, u32);
    virtual Reflexible* searchNode([[maybe_unused]] const SafeString& name) { return nullptr; }
    virtual void calcURL(BufferedSafeString* url) const { url->copy(""); }
    virtual void calcNodeURL(const Reflexible* reflexible, BufferedSafeString* url)
    {
        return reflexible->calcURL(url);
    }

    void callGenMessage(Context*, u32);
    void correctChildNodeInfo(Context*);
    void baseListen(const PropertyEvent* event);
    void applyEventDataToMemory(const PropertyEvent* event);

    SafeString getNodeName() const { return mName; }
    void setNodeName(const SafeString& name);
    void setNodeNameCopyString(const SafeString& name, Heap* heap);

    SafeString getNodeMeta() const { return mMeta; }
    void setNodeMeta(const SafeString& meta);
    void setNodeMetaCopyString(const SafeString& meta, Heap* heap);

protected:
    void disposeHostIO() override
    {
        disposeHostIOImpl_();
        NodeEventListener::disposeHostIO();
    }
    virtual void genChildNode(Context* context);
    virtual bool isHaveChild() const { return false; }

private:
    using ApplyEventDataToMemoryCallback = bool (*)(const PropertyEvent* event);

    void safeDelete_(AllocFlg flag);
    const char* createStringBuffer_(AllocFlg flag, const SafeString& name, Heap* heap);
    void disposeHostIOImpl_();

    const char* mName;
    const char* mMeta;
    bool mIsGenerated = false;
    BitFlag8 mAllocFlg;
    static ApplyEventDataToMemoryCallback sApplyEventDataToMemoryCallback;
#endif
};
}  // namespace hostio
}  // namespace sead
