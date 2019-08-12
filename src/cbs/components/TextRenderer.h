#ifndef TextRenderer_h
#define TextRenderer_h

#include "IComponent.h"

#include "../Object.h"

class TextRenderer : public IComponent {
public:
    TextRenderer(const std::string& text = "");

    void Initialize() override;
    void Destroy() override;

private:
};

#endif