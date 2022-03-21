#pragma once

#include <hostio/seadHostIOReflexible.h>
#include <prim/seadSafeString.h>
#include "agl/Utils/aglResParameter.h"

namespace sead {
class XmlElement;
}

namespace agl::utl {

class IParameterList;
class ParameterBase;

class IParameterObj {
public:
    IParameterObj();
    virtual ~IParameterObj() { ; }

    void pushBackListNode(ParameterBase* p_node);
    void sortByHash();

    sead::SafeString getName() const;
    u32 getNameHash() const { return mNameHash; }

    ParameterBase* getParamListHead() const { return mParamListHead; }
    ParameterBase* getParamListTail() const { return mParamListTail; }
    u32 getParamListSize() const { return mParamListSize; }
    IParameterObj* getNext() const { return mNext; }

    void writeToXML(sead::XmlElement* element, sead::Heap* heap);
    bool readFromXML(const sead::XmlElement& element, bool x);
    void createAttribute(sead::XmlElement* element, sead::Heap* heap) const;
    static const char* getTagName();

    void applyResParameterObj(ResParameterObj obj1, ResParameterObj obj2, f32 t,
                              IParameterList* list);

    void applyResParameterObj(ResParameterObj obj, IParameterList* list = nullptr) {
        applyResParameterObj_(false, obj, {}, 0.0, list);
    }

    bool isComplete(ResParameterObj obj, bool) const;
    bool verify() const;
    bool verify(ParameterBase* p_check, ParameterBase* other) const;

    void copy(ParameterBase* first, ParameterBase* last, const ParameterBase* src_first,
              const ParameterBase* src_last);
    void copy(const IParameterObj& obj);
    void copyLerp(ParameterBase* first, ParameterBase* last, const ParameterBase* src1_first,
                  const ParameterBase* src1_last, const ParameterBase* src2_first,
                  const ParameterBase* src2_last, f32 t);
    void copyLerp(const IParameterObj& obj1, const IParameterObj& obj2, f32 t);

#ifdef SEAD_DEBUG
    void genMessageParameter(sead::hostio::Context* context);
    void listenPropertyEventParameter(sead::hostio::Reflexible* reflexible,
                                      const sead::hostio::PropertyEvent* event);
#endif

protected:
    friend class IParameterList;

    virtual bool preWrite_() const { return true; }
    virtual void postWrite_() const {}
    virtual bool preRead_() { return true; }
    virtual void postRead_() {}
    virtual bool preCopy_() { return true; }
    virtual void postCopy_() {}
    virtual bool isApply_(ResParameterObj obj) const {
        return obj.getParameterObjNameHash() == mNameHash;
    }

    void applyResParameterObj_(bool interpolate, ResParameterObj obj1, ResParameterObj obj2, f32 t,
                               IParameterList* list);
    ParameterBase* searchParameter_(u32 hash);
    ParameterBase* searchParameter_(u32 hash) const;

    void copy_(ParameterBase* first, ParameterBase* last, const ParameterBase* src_first,
               const ParameterBase* src_last);
    void copyLerp_(ParameterBase* first, ParameterBase* last, const ParameterBase* src1_first,
                   const ParameterBase* src1_last, const ParameterBase* src2_first,
                   const ParameterBase* src2_last, f32 t);

    ParameterBase* mParamListHead = nullptr;
    ParameterBase* mParamListTail = nullptr;
    u32 mParamListSize = 0;
    u32 mNameHash = 0;
    IParameterObj* mNext = nullptr;
    const char* mName = nullptr;
};

class ParameterObj : public IParameterObj {
public:
    using IParameterObj::IParameterObj;
    ~ParameterObj() override { ; }
};

}  // namespace agl::utl
