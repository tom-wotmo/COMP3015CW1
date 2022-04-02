#include "scenebasic_uniform.h"
#include "helper/texture.h"


#include <iostream>
#include <sstream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>

#include "helper/glutils.h"

using glm::vec3;
using glm::mat4;
GLuint sofaTex;

SceneBasic_Uniform::SceneBasic_Uniform() : rotation(0.0f)
{
    //loading in our models
    catMesh = ObjMesh::load("cat.obj", true);
    sofaMesh = ObjMesh::load("sofa.obj", true);
    tableMesh = ObjMesh::load("table.obj", true);
   
}

void SceneBasic_Uniform::initScene()
{
    compile();
    glEnable(GL_DEPTH_TEST);

    //view and projection
    view = glm::lookAt(vec3(0.5f, 0.75f, 0.75f), vec3(0.0f, 0.0f, 0.0f),vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);

    //initialise the model matrix
    model = mat4(1.0f);
    projection = mat4(1.0f);
    vec3 lightpos = vec3(0.0f, 1.0f, 1.0f);

    //setting the lights
    prog.setUniform("Lights.La", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Lights.L", 0.8f, 0.5f, 0.1f);
    prog.setUniform("Lights.Position", lightpos);

    sofaTex = Texture::loadTexture("sofa_D.png");


    
    //binding the texture to our binding0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sofaTex);
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("basic_uniform.vert");
		prog.compileShader("basic_uniform.frag");
		prog.link();
		prog.use();

	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    

    //controlling the rotating around the model
    rotation = t;

}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv); //set the uniform for the model view matrix
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); //we set the uniform for normal matrix
    prog.setUniform("MVP", projection * mv); //we set the model view matrix by multiplying the mv with the projection matrix
}

void SceneBasic_Uniform::render()
{
    view = glm::lookAt(vec3(10.0f, 5.0f, 4.15f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 2.0f, 0.0f));
    view = glm::rotate(view, glm::radians(30.0f * rotation), vec3(0.0f, 1.0f, 0.0f));

    //load the fog
    prog.setUniform("Fog.MaxDist", 60.0f);
    prog.setUniform("Fog.MinDist", 1.0f);
    prog.setUniform("Fog.Colour", vec3(1.0f,1.0f,1.0f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //render the cat
    prog.setUniform("Material.Kd", 0.2f, 0.2f, 0.2f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 1.0f);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 10.0f, 0.0f));
    model = glm::scale(model, vec3(0.005f, 0.005f, 0.005f));
    model = glm::translate(model, vec3(10.0f, -0.02f, 10.0f));
    setMatrices();
    catMesh->render();

    //render the sofa
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 1.0f);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, vec3(0.05f, 0.05f, 0.05f));
    model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));
    setMatrices();
    sofaMesh->render();

    //render the table
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 1.0f);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(-90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, vec3(7.5f,7.5f,7.5f));
    model = glm::translate(model, vec3(-1.5f, 0.0f, 0.0f));
    setMatrices();
    tableMesh->render();
   
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

