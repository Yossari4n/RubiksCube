#ifndef TextRenderer_h
#define TextRenderer_h

#include "IComponent.h"
#include "../../GUI/IWidget.h"

#include "../Object.h"
#include "../../scenes/IScene.h"
#include "../message_system/MessageIn.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#pragma warning(pop)

#include <istream>
#include <string>
#include <map>

class TextRenderer : public IComponent, public IWidget {
public:
    TextRenderer(const std::string& text = "");

    void Initialize() override;
    void Destroy() override;

private:
    std::string m_Text;
};

#endif