#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"

#include "helper/objmesh.h"

class SceneBasic_Uniform : public Scene
{
private:
  
    GLuint vaoHandle;
    GLSLProgram prog;
  
     
    std::unique_ptr<ObjMesh> catMesh;
    std::unique_ptr<ObjMesh> sofaMesh;
    std::unique_ptr<ObjMesh> tableMesh;
    

    float angle;
    float rotation;
    void setMatrices();
    void compile();
    void GUIview();

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
