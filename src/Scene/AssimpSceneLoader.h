#ifndef AssimpSceneLoader_H
#define AssimpSceneLoader_H

#include <string>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "common/Singleton.h"
#include "Mesh/Mesh.h"
#include "Material/ShaderProgram.h"

using std::string;

class AssimpSceneLoader : public Singleton<AssimpSceneLoader>
{
public:
    vector<Mesh*> meshes;
    const aiScene* assimpScene;
    vector<ShaderProgram*> materials;

    AssimpSceneLoader();
    void load(string file);
    Mesh * initMesh(aiMesh * assMesh);
    void initNode(aiNode * parent);
};

#endif // AssimpSceneLoader_H
