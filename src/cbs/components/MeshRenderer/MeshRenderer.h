#ifndef Model_h
#define Model_h

#pragma warning(disable: 26495)

#include "Mesh.h"
#include "../IComponent.h"
#include "../../../rendering/IDrawable.h"

#pragma warning(push, 0)
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb/stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include <string>
#include <vector>

class MeshRenderer : public IComponent, public IDrawable {
public:
    MeshRenderer(std::string path, ShaderProgram::Type type);
    ~MeshRenderer();
    
    void Initialize() override;
    void Destroy() override;
    
    void Draw(const ShaderProgram &shader) const override;
    
    const std::vector<Mesh>& Meshes() const { return m_Meshes; }
    
    const std::vector<Texture>& TexturesLoaded() const { return m_TexturesLoaded; }
    
    const std::string& Directory() const { return m_Directory; }
    
private:
    std::vector<Mesh> m_Meshes;
    std::vector<Texture> m_TexturesLoaded;
    std::string m_Directory;
    
    void LoadModel(std::string path);
    void ProcessNode(aiNode *node, const aiScene *scene);
    void ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory);
};

#pragma warning(default: 26495)
#endif
