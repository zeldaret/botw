#include "agl/Utils/aglParameterIO.h"
#include <basis/seadRawPrint.h>

namespace agl::utl {

IParameterIO::IParameterIO() {
    _1cc = 1;
    mType = "xml";
    mVersion = 0;
    setParameterListName_("param_root");
}

IParameterIO::IParameterIO(const sead::SafeString& name, u32 version) {
    _1cc = 0;
    mType = name;
    mVersion = version;
    setParameterListName_("param_root");
}

void IParameterIO::applyResParameterArchive(ResParameterArchive arc) {
    SEAD_ASSERT(arc.isValid());
    mResFileSize = arc.mPtr->file_size;

    if (mVersion != arc.mPtr->pio_version)
        callbackInvalidVersion_(arc);

    applyResParameterList(arc.getRootList());
}

void IParameterIO::applyResParameterArchiveLerp(ResParameterArchive arc_a,
                                                ResParameterArchive arc_b, f32 t) {
    SEAD_ASSERT(arc_a.isValid());
    SEAD_ASSERT(arc_b.isValid());

    if (mVersion != arc_a.mPtr->pio_version)
        callbackInvalidVersion_(arc_a);

    if (mVersion != arc_b.mPtr->pio_version)
        callbackInvalidVersion_(arc_b);

    applyResParameterList(arc_a.getRootList(), arc_b.getRootList(), t);
}

bool IParameterIO::isCompleteArchive(ResParameterArchive archive, bool x) const {
    return isComplete(archive.getRootList(), x);
}

}  // namespace agl::utl
