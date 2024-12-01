#pragma once
#include <stb_image.h>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <Mesh.h>

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
class Model
{
public:
    // model data 
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;
public:
    /*  函数   */
    Model(string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }
    void Draw(Shader shader);
private:
    /*  函数   */
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);//递归
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);//将一个aiMesh对象转化为我们自己的网格对象，访问网格的相关属性并将它们储存到我们自己的对象中
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

