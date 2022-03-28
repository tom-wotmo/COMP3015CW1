#include "scenebasic_uniform.h"

#include <iostream>
#include <sstream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>
#include "helper/teapot.h"
#include "helper/torus.h"
#include "helper/glutils.h"

using glm::vec3;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() : plane(10.0f,10.0f,100,100) 
{
    mesh = ObjMesh::load("../Project_Template/media/cat.obj", true);
}

void SceneBasic_Uniform::initScene()
{
    compile();
    glEnable(GL_DEPTH_TEST);


    view = glm::lookAt(vec3(0.5f, 0.75f, 0.75f), vec3(0.0f, 0.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);

    prog.setUniform("Spot.L", vec3(0.9f));
    prog.setUniform("Spot.LA", vec3(0.5f));
    prog.setUniform("Spot.Exponent", 50.0f);
    prog.setUniform("Spot.Cutoff", glm::radians(15.0f));

    float x, z;
    for (int i = 0; i < 3; i++)
    {
        std::stringstream name;
        name << "lights[" << i << "].Position";
        x = 2.0f * cosf((glm::two_pi<float>() / 3) * i);
        z = 2.0f * sinf((glm::two_pi<float>() / 3) * i);
        prog.setUniform(name.str().c_str(), view * glm::vec4(x, 1.2f, z +
            1.0f, 1.0f));
    }

    prog.setUniform("lights[0].L", vec3(0.0f, 0.0f, 0.8f));
    prog.setUniform("lights[1].L", vec3(0.0f, 0.8f, 0.0f));
    prog.setUniform("lights[2].L", vec3(0.8f, 0.0f, 0.0f));

    //setting ambient lights
    prog.setUniform("lights[0].LA", vec3(0.0f, 0.0f, 0.8f));
    prog.setUniform("lights[1].LA", vec3(0.0f, 0.0f, 0.8f));
    prog.setUniform("lights[2].LA", vec3(0.0f, 0.0f, 0.8f));


    //initialise the model matrix
    model = mat4(1.0f);

    //enable this group for torus rendering, make sure you comment the teapot group
    model = glm::rotate(model, glm::radians(35.0f), vec3(1.0f, 0.0f, 0.0f)); //rotate model on x axis
    model = glm::rotate(model, glm::radians(15.0f), vec3(0.0f, 1.0f, 0.0f));  //rotate model on y axis
    view = glm::lookAt(vec3(0.0f, 0.0f, -10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)); //sets the view - read in the documentation about glm::lookAt. if still have questions,come an dtalk to me

    //enable this group for teapot rendering, make sure you comment the torus group
    //model = glm::translate(model, vec3(0.0, -1.0, 0.0));
    //model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    //view = glm::lookAt(vec3(2.0f, 4.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    projection = mat4(1.0f);

    //make sure you use the correct name, check your vertex shader
    prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f); //seting the Kd uniform
    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);     //setting the Ld uniform
    prog.setUniform("Light.Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
	//update your angle here
}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model; //we create a model view matrix

    prog.setUniform("ModelViewMatrix", mv); //set the uniform for the model view matrix

    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); //we set the uniform for normal matrix

    prog.setUniform("MVP", projection * mv); //we set the model view matrix by multiplying the mv with the projection matrix
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 180.0f);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    setMatrices();
    mesh->render();
    prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 180.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));
    setMatrices();
    plane.render();
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}
