#pragma once

namespace ksys {

struct MesTransceiverId;
struct MessageType;

class MessageAck {
public:
    MessageAck(bool dest_valid, bool success, const MesTransceiverId& destination,
               const MessageType& type, void* user_data);
    virtual ~MessageAck();

    virtual bool isDestinationValid() const;
    virtual bool isSuccess() const;
    virtual const MesTransceiverId& getDestination() const;
    virtual const MessageType& getType() const;
    virtual void* getUserData() const;

private:
    bool mDestValid{};
    bool mSuccess{};
    const MesTransceiverId& mDestination;
    const MessageType& mType;
    void* mUserData{};
};

}  // namespace ksys
