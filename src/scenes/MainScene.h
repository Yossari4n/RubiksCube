#ifndef MainScene_h
#define MainScene_h

#include "IScene.h"

class MainScene : public IScene {
public:
    void CreateScene() override;

private:
    float DateToHours(unsigned int days, unsigned int hours, unsigned int minutes, unsigned int seconds) const {
        return 24.0f * days + hours + minutes / 60.0f + seconds / 360.0f;
    }
};

#endif
