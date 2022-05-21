#ifndef Model_h
#define Model_h

#pragma warning(disable: 26495)

#include "Mesh.h"
#include "../Component.h"
#include "../../Object.h"
#include "../../message_system/PropertyIn.h"
#include "../../../scenes/Scene.h"
#include "../../../rendering/Drawable.h"

#pragma warning(push, 0)
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include <iostream>
#include <string>
#include <vector>

class MeshRenderer : public Component, public Drawable {
public:
    MeshRenderer(const std::string& path, ShaderProgram::Type type);

    void MakeConnectors(MessageManager& message_manager) override;
    void Initialize() override;
    void Destroy() override;

    void Draw(const ShaderProgram &shader) const override;

    const std::vector<Mesh>& Meshes() const { return m_Meshes; }

    const std::vector<Texture>& TexturesLoaded() const { return m_TexturesLoaded; }

    const std::string& Directory() const { return m_Directory; }

    PropertyIn<glm::mat4> ModelIn;

private:
    std::vector<Mesh> m_Meshes;
    std::vector<Texture> m_TexturesLoaded;
    std::string m_Directory;

    void LoadModel(const std::string& path);
    void ProcessNode(aiNode *node, const aiScene *scene);
    void ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory);
};

#pragma warning(default: 26495)
#endif
