#pragma once

#include "agl/Utils/aglParameterList.h"

namespace sead {
class XmlDocument;
}

namespace agl::utl {

class IParameterIO : public IParameterList {
public:
    IParameterIO();
    IParameterIO(const sead::SafeString& name, u32 version);
    ~IParameterIO() override { ; }

    virtual bool save(const sead::SafeString& path, u32) const;
    virtual void applyResParameterArchive(ResParameterArchive arc);
    virtual void applyResParameterArchiveLerp(ResParameterArchive arc_a, ResParameterArchive arc_b,
                                              f32 t);

    void load(const sead::SafeString& path, bool);
    void loadText(const void* data, u32 size, bool);

    bool isCompleteArchive(ResParameterArchive archive, bool) const;

    void genMessageIO(sead::hostio::Context* context, u32);
    void listenPropertyEventIO(sead::hostio::Reflexible* reflexible,
                               sead::hostio::PropertyEvent* event);

protected:
    virtual void callbackInvalidVersion_(ResParameterArchive) {}

#ifdef SEAD_DEBUG
    virtual void writeHeader_(sead::XmlElement* element, sead::Heap* heap) const;
#endif
    void save_(const sead::SafeString& path, const sead::XmlDocument* document) const;

    sead::FixedSafeString<64> mType;
    u32 mVersion;
    void* _a8 = nullptr;
    sead::FixedSafeString<256> _b0 = sead::SafeString::cEmptyString;
    u32 mResFileSize = 0;
    u32 _1cc;
};

}  // namespace agl::utl
