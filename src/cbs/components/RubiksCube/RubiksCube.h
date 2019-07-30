#ifndef RubiksCube_h
#define RubiksCube_h

#include "../IComponent.h"
#include "../../Object.h"
#include "../../message_system/PropertyOut.h"
#include "../Transform.h"
#include "Cubie.h"

#include <vector>

class RubiksCube : public IComponent {
public:
    RubiksCube() = default;

    void Initialize() override;

    PropertyIn<Transform&> m_FrontFace{ this };

private:
    std::vector<Cubie> m_Cubies;
};

#endif