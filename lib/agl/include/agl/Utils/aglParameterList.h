#pragma once

#include <hostio/seadHostIOReflexible.h>
#include <prim/seadSafeString.h>
#include "agl/Utils/aglResParameter.h"

namespace sead {
class XmlElement;
}

namespace agl::utl {

class IParameterObj;
class ParameterBase;

class IParameterList {
public:
    IParameterList();
    virtual ~IParameterList() { ; }

    void addList(IParameterList* child, const sead::SafeString& name);
    void addObj(IParameterObj* child, const sead::SafeString& name);
    void clearList();
    void clearObj();
    void removeList(IParameterList* child);
    void removeObj(IParameterObj* child);

    IParameterObj* getChildObjHead() const { return mpChildObjHead; }
    IParameterObj* getChildObjTail() const { return mpChildObjTail; }
    IParameterList* getChildListHead() const { return mpChildListHead; }
    IParameterList* getChildListTail() const { return mpChildListTail; }
    IParameterList* getNext() const { return mNext; }
    IParameterList* getParent() const { return mParent; }

    sead::SafeString getName() const;
    u32 getNameHash() const { return mNameHash; }

    void applyResParameterList(ResParameterList list);
    void applyResParameterList(ResParameterList list1, ResParameterList list2, f32 t);

    bool isComplete(ResParameterList res, bool) const;

    const char* getTagName();
    void createAttribute(sead::XmlElement* element, sead::Heap* heap) const;
    void writeToXML(sead::XmlElement* element, sead::Heap* heap);
    bool readFromXML(const sead::XmlElement& element, bool x);

    bool verify() const;
    bool verifyList() const;
    bool verifyObj() const;
    bool verifyList(IParameterList* p_check, IParameterList* other) const;
    bool verifyObj(IParameterObj* obj1, IParameterObj* obj2) const;

    void sortByHash();

#ifdef SEAD_DEBUG
    void genMessageParameter(sead::hostio::Context* context);
    void listenPropertyEventParameter(sead::hostio::Reflexible* reflexible,
                                      const sead::hostio::PropertyEvent* event);
#endif

protected:
    virtual bool preWrite_() const { return true; }
    virtual void postWrite_() const {}
    virtual bool preRead_() { return true; }
    virtual void postRead_() {}
    virtual bool isApply_(ResParameterList list) const {
        return list.getParameterListNameHash() == mNameHash;
    }
    virtual void callbackNotAppliable_(IParameterObj*, ParameterBase*, ResParameterObj) {}
    virtual void callbackNotInterpolatable_(IParameterObj*, ParameterBase*, ResParameterObj,
                                            ResParameterObj, ResParameter, ResParameter, f32) {}

    void setParameterListName_(const sead::SafeString& name);
    void applyResParameterList_(bool interpolate, ResParameterList l1, ResParameterList l2, f32 t);
    ResParameterObj searchResParameterObj_(ResParameterList res, const IParameterObj& obj) const;
    IParameterObj* searchChildParameterObj_(ResParameterObj res, IParameterObj* obj) const;
    void applyResParameterObjB_(bool interpolate, ResParameterList res, f32 t);
    ResParameterList searchResParameterList_(ResParameterList res,
                                             const IParameterList& list) const;
    IParameterList* searchChildParameterList_(ResParameterList res) const;
    void applyResParameterListB_(bool interpolate, ResParameterList res, f32 t);

    IParameterObj* mpChildObjHead = nullptr;
    IParameterObj* mpChildObjTail = nullptr;
    IParameterList* mpChildListHead = nullptr;
    IParameterList* mpChildListTail = nullptr;
    u32 mNameHash;
    IParameterList* mNext = nullptr;
    IParameterList* mParent = nullptr;
    const char* mName;
};

class ParameterList : public IParameterList {
public:
    using IParameterList::IParameterList;
    ~ParameterList() override { ; }
};

}  // namespace agl::utl
