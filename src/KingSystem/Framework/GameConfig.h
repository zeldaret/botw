class GameConfig {
public:
    static GameConfig* getInstance() { return sInstancePtr; }

    char mPadding[0x419];
    bool mField419;

private:
    static GameConfig* sInstancePtr;
};
