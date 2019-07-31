#ifndef RubiksCube_h
#define RubiksCube_h

#include "Cubie.h"

#include "../IComponent.h"
#include "../../Object.h"
#include "../../../scenes/IScene.h"
#include "../../message_system/PropertyOut.h"

#include <vector>
#include <array>

class RubiksCube : public IComponent {
public:
    RubiksCube();

    void Initialize() override;
    void Destroy() override;

private:
    std::vector<Cubie> m_Cubies;
};

#endif
