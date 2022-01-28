#pragma once

class hkRotationf : public hkMatrix3f {
public:
    void set(hkQuaternionfParameter q);

    void setAxisAngle(hkVector4fParameter axis, hkFloat32 angle);
    void setAxisAngle(hkVector4fParameter axis, hkSimdFloat32Parameter angle);

    bool isOrthonormal(hkFloat32 epsilon = hkFloat32(1e-5f)) const;

    bool isOk() const;
    void renormalize();
};
