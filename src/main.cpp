/*  by Alun Evans 2016 LaSalle (aevanss@salleurl.edu) */

/* PRACTICA 3 GRAFICOS 3D */
/* AUTORES:
Pol Piñol Castuera (pol.pinol)
Inés Graells Sanz (ines.graells)
*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>


//include OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imageloader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

//include some custom code files
#include "glfunctions.h" //include all OpenGL stuff
#include "Shader.h" // class to compile shaders

#include <string>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

using namespace std;
using namespace glm;

string basepath = "assets/";
string inputfile = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials;

string inputfile2 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes2;
vector< tinyobj::material_t > materials2;

string inputfile3 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes3;
vector< tinyobj::material_t > materials3;

string inputfile4 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes4;
vector< tinyobj::material_t > materials4;

string inputfile5 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes5;
vector< tinyobj::material_t > materials5;

string inputfile6 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes6;
vector< tinyobj::material_t > materials6;

string inputfile7 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes7;
vector< tinyobj::material_t > materials7;

string inputfile8 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes8;
vector< tinyobj::material_t > materials8;

string inputfile9 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes9;
vector< tinyobj::material_t > materials9;

string inputfile10 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes10;
vector< tinyobj::material_t > materials10;

string inputfile11 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes11;
vector< tinyobj::material_t > materials11;


//global variables to help us do things
int g_ViewportWidth = 1000; int g_ViewportHeight = 1000; // Default window size, in pixels
double mouse_x, mouse_y; //variables storing mouse position
const vec3 g_backgroundColor(0.2f, 0.2f, 0.2f); // background colour - a GLM 3-component vector

GLuint g_simpleShader = 0; //shader identifier
GLuint g_simpleShader_sky = 0; //shader identifier
GLuint g_simpleShader_sun = 0; //shader identifier
GLuint g_simpleShader_planet = 0;


GLuint g_Vao = 0; //vao
GLuint g_NumTriangles = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_sun = 0; //vao
GLuint g_NumTriangles_sun = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_sky = 0; //vao
GLuint g_NumTriangles_sky = 0; // Number of triangles we are painting.

GLuint g_Vao_mercury = 0; //vao
GLuint g_NumTriangles_mercury = 0; // Number of triangles we are painting.

GLuint g_Vao_venus = 0; //vao
GLuint g_NumTriangles_venus = 0; // Number of triangles we are painting.

GLuint g_Vao_mars = 0; //vao
GLuint g_NumTriangles_mars = 0; // Number of triangles we are painting.

GLuint g_Vao_moon = 0; //vao
GLuint g_NumTriangles_moon = 0; // Number of triangles we are painting.

GLuint g_Vao_jupiter = 0; //vao
GLuint g_NumTriangles_jupiter = 0; // Number of triangles we are painting.

GLuint g_Vao_neptune = 0; //vao
GLuint g_NumTriangles_neptune = 0; // Number of triangles we are painting.

GLuint g_Vao_saturn = 0; //vao
GLuint g_NumTriangles_saturn = 0; // Number of triangles we are painting.

GLuint g_Vao_uranus = 0; //vao
GLuint g_NumTriangles_uranus = 0; // Number of triangles we are painting.

vec3 center = vec3(0.0f, 0.0f, 0.0f); // camera globals
vec3 eye = vec3(1.0f, 3.0f, 5.0f);
vec3 up = vec3(0.0f, 1.0f, 0.0f); // orientation of the camera

//STEP 6: add a global variable for the texture ID
// variable global
GLuint texture_id;
GLuint texture_id_earth_normal;
GLuint texture_id_earth_spec;
GLuint texture_id_earth_night;
GLuint texture_id2;
GLuint texture_id3;
GLuint texture_id_mercury;

GLuint texture_id_venus;
GLuint texture_id_mars;
GLuint texture_id_jupiter;
GLuint texture_id_moon;
GLuint texture_id_neptune;
GLuint texture_id_saturn;
GLuint texture_id_uranus;


vec3 g_light_dir(100, 100, 100);
vec3 g_light_dir2(100, 100, 100);
vec3 g_light_dir3(100, 100, 100);
vec3 g_light_dir4(100, 100, 100);
vec3 g_light_dir5(100, 100, 100);
vec3 g_light_dir6(100, 100, 100);
vec3 g_light_dir7(100, 100, 100);
vec3 g_light_dir8(100, 100, 100);
vec3 g_light_dir9(100, 100, 100);
vec3 g_light_dir10(100, 100, 100);
vec3 g_light_dir11(100, 100, 100);



float x = 0.0f;
float y = 0.0f;
float z = -2.0f;


int aux = 0;
double auxX = 0.0f;
double auxY = 0.0f;



// ------------------------------------------------------------------------------------------
// This function manually creates a square geometry (defined in the array vertices[])
// ------------------------------------------------------------------------------------------
void load()
{
	//**********************
	// LA TERRA
	//**********************
    
	string err;
	//load the OBJ file to shapes
    bool  ret = tinyobj::LoadObj(shapes, materials, err, inputfile.c_str(), basepath.c_str());
	

	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors(shapes[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}
	else
	//print out number of meshes described in file
	    std::cout << "Loaded "<< inputfile << " with shapes: " << shapes.size() << std::endl;

	//load the shader
	Shader simpleShader("src/shader.vert", "src/shader.frag");
	g_simpleShader = simpleShader.program;

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes[0].mesh.positions[0]), shapes[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes[0].mesh.indices[0]), shapes[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes[0].mesh.texcoords[0]), shapes[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);
	gl_createAndBindAttribute(&(shapes[0].mesh.normals[0]), shapes[0].mesh.normals.size() * sizeof(float), g_simpleShader, "a_normal", 3);



	gl_unbindVAO();

	g_NumTriangles = shapes[0].mesh.indices.size() / 3;


	//STEP 7: create the texture object
	//TEXTURA TERRA
	Image* image = loadBMP("assets/earth.bmp");
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,    //target
		0,                //level = 0 base, no mipmap
		GL_RGB,           //how the data will bee stored
		image->width,     //width of the image
		image->height,    //height of the image
		0,                //border
		GL_RGB,           //format of origianl data
		GL_UNSIGNED_BYTE, //type of data
		image->pixels);


	// TEXTURA RELIEVE
	Image* image_normal = loadBMP("assets/earthnormal.bmp");
	glGenTextures(1, &texture_id_earth_normal);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_normal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, // target
		0, // level = 0 base, no mipmap
		GL_RGB, // how the data will be stored
		image_normal->width, // width of the image
		image_normal->height, // height of the image
		0, //border
		GL_RGB, // format of original data
		GL_UNSIGNED_BYTE, // type of data
		image_normal->pixels); // pointer to the start of data


	Image* image_spec = loadBMP("assets/earthspec.bmp");
	glGenTextures(1, &texture_id_earth_spec);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_spec);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, // target
		0, // level = 0 base, no mipma
		GL_RGB, // how the data will be stored
		image_spec->width, // width of the image
		image_spec->height, // height of the image
		0, //border
		GL_RGB, // format of original data
		GL_UNSIGNED_BYTE, // type of data
		image_spec->pixels); // pointer to the start of data


	Image* image_night = loadBMP("assets/earthnight.bmp");
	glGenTextures(1, &texture_id_earth_night);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_night);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, // target
		0, // level = 0 base, no mipmap
		GL_RGB, // how the data will be stored
		image_night->width, // width of the image
		image_night->height, // height of the image
		0, //border
		GL_RGB, // format of original data
		GL_UNSIGNED_BYTE, // type of data
		image_night->pixels); // pointer to the start of data





	////////////////////////////////////////
	// MERCURI
	///////////////////////////////////////

	string err4;
	//load the OBJ file to shapes
	bool  ret4 = tinyobj::LoadObj(shapes4, materials4, err4, inputfile4.c_str(), basepath.c_str());


	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors4(shapes4[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err4.empty()) { // `err` may contain warning message.
		std::cerr << err4 << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile4 << " with shapes: " << shapes4.size() << std::endl;

	//load the shader
	Shader simpleShader_planet("src/shader_planet.vert", "src/shader_planet.frag");
	g_simpleShader_planet = simpleShader_planet.program;

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao_mercury = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes4[0].mesh.positions[0]), shapes4[0].mesh.positions.size() * sizeof(float), g_simpleShader_planet, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes4[0].mesh.indices[0]), shapes4[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes4[0].mesh.texcoords[0]), shapes4[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_planet, "a_uv", 2);
	gl_createAndBindAttribute(&(shapes4[0].mesh.normals[0]), shapes4[0].mesh.normals.size() * sizeof(float), g_simpleShader_planet, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_mercury = shapes4[0].mesh.indices.size() / 3;

	Image* image_mercury = loadBMP("assets/mercury.bmp");
	glGenTextures(1, &texture_id_mercury);
	glBindTexture(GL_TEXTURE_2D, texture_id_mercury);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,    //target
		0,                //level = 0 base, no mipmap
		GL_RGB,           //how the data will bee stored
		image_mercury->width,     //width of the image
		image_mercury->height,    //height of the image
		0,                //border
		GL_RGB,           //format of origianl data
		GL_UNSIGNED_BYTE, //type of data
		image_mercury->pixels);



	////////////////////////////////////////
	// MARS
	///////////////////////////////////////

	string err5;
	//load the OBJ file to shapes
	bool  ret5 = tinyobj::LoadObj(shapes5, materials5, err5, inputfile5.c_str(), basepath.c_str());


	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors5(shapes5[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err5.empty()) { // `err` may contain warning message.
		std::cerr << err5 << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile5 << " with shapes: " << shapes5.size() << std::endl;

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao_mars = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes5[0].mesh.positions[0]), shapes5[0].mesh.positions.size() * sizeof(float), g_simpleShader_planet, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes5[0].mesh.indices[0]), shapes5[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes5[0].mesh.texcoords[0]), shapes5[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_planet, "a_uv", 2);
	gl_createAndBindAttribute(&(shapes5[0].mesh.normals[0]), shapes5[0].mesh.normals.size() * sizeof(float), g_simpleShader_planet, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_mars = shapes5[0].mesh.indices.size() / 3;

	Image* image_mars = loadBMP("assets/mars.bmp");
	glGenTextures(1, &texture_id_mars);
	glBindTexture(GL_TEXTURE_2D, texture_id_mars);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,    //target
		0,                //level = 0 base, no mipmap
		GL_RGB,           //how the data will bee stored
		image_mars->width,     //width of the image
		image_mars->height,    //height of the image
		0,                //border
		GL_RGB,           //format of origianl data
		GL_UNSIGNED_BYTE, //type of data
		image_mars->pixels);



	////////////////////////////////////////
	// MOON
	///////////////////////////////////////

	string err6;
	//load the OBJ file to shapes
	bool  ret6 = tinyobj::LoadObj(shapes6, materials6, err6, inputfile6.c_str(), basepath.c_str());


	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors6(shapes6[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err6.empty()) { // `err` may contain warning message.
		std::cerr << err6 << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile6 << " with shapes: " << shapes6.size() << std::endl;

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao_moon = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes6[0].mesh.positions[0]), shapes6[0].mesh.positions.size() * sizeof(float), g_simpleShader_planet, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes6[0].mesh.indices[0]), shapes6[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes6[0].mesh.texcoords[0]), shapes6[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_planet, "a_uv", 2);
	gl_createAndBindAttribute(&(shapes6[0].mesh.normals[0]), shapes6[0].mesh.normals.size() * sizeof(float), g_simpleShader_planet, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_moon = shapes6[0].mesh.indices.size() / 3;

	//STEP 7: create the texture object
	//TEXTURA TERRA
	Image* image_moon = loadBMP("assets/moon.bmp");
	glGenTextures(1, &texture_id_moon);
	glBindTexture(GL_TEXTURE_2D, texture_id_moon);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,    //target
		0,                //level = 0 base, no mipmap
		GL_RGB,           //how the data will bee stored
		image_moon->width,     //width of the image
		image_moon->height,    //height of the image
		0,                //border
		GL_RGB,           //format of origianl data
		GL_UNSIGNED_BYTE, //type of data
		image_moon->pixels);



	////////////////////////////////////////
	// JUPITER
	///////////////////////////////////////

	string err7;
	//load the OBJ file to shapes
	bool  ret7 = tinyobj::LoadObj(shapes7, materials7, err7, inputfile7.c_str(), basepath.c_str());


	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors7(shapes7[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err7.empty()) { // `err` may contain warning message.
		std::cerr << err7 << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile7 << " with shapes: " << shapes7.size() << std::endl;


	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao_jupiter = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes7[0].mesh.positions[0]), shapes7[0].mesh.positions.size() * sizeof(float), g_simpleShader_planet, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes7[0].mesh.indices[0]), shapes7[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes7[0].mesh.texcoords[0]), shapes7[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_planet, "a_uv", 2);
	gl_createAndBindAttribute(&(shapes7[0].mesh.normals[0]), shapes7[0].mesh.normals.size() * sizeof(float), g_simpleShader_planet, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_jupiter = shapes7[0].mesh.indices.size() / 3;

	Image* image_jupiter = loadBMP("assets/jupiter.bmp");
	glGenTextures(1, &texture_id_jupiter);
	glBindTexture(GL_TEXTURE_2D, texture_id_jupiter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,    //target
		0,                //level = 0 base, no mipmap
		GL_RGB,           //how the data will bee stored
		image_jupiter->width,     //width of the image
		image_jupiter->height,    //height of the image
		0,                //border
		GL_RGB,           //format of origianl data
		GL_UNSIGNED_BYTE, //type of data
		image_jupiter->pixels);




	////////////////////////////////////////
	// neptune
	///////////////////////////////////////

	string err8;
	//load the OBJ file to shapes
	bool  ret8 = tinyobj::LoadObj(shapes8, materials8, err8, inputfile8.c_str(), basepath.c_str());


	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors8(shapes8[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err8.empty()) { // `err` may contain warning message.
		std::cerr << err8 << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile8 << " with shapes: " << shapes8.size() << std::endl;

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao_neptune = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes8[0].mesh.positions[0]), shapes8[0].mesh.positions.size() * sizeof(float), g_simpleShader_planet, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes8[0].mesh.indices[0]), shapes8[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes8[0].mesh.texcoords[0]), shapes8[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_planet, "a_uv", 2);
	gl_createAndBindAttribute(&(shapes8[0].mesh.normals[0]), shapes8[0].mesh.normals.size() * sizeof(float), g_simpleShader_planet, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_neptune = shapes8[0].mesh.indices.size() / 3;

	Image* image_neptune = loadBMP("assets/neptune.bmp");
	glGenTextures(1, &texture_id_neptune);
	glBindTexture(GL_TEXTURE_2D, texture_id_neptune);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,    //target
		0,                //level = 0 base, no mipmap
		GL_RGB,           //how the data will bee stored
		image_neptune->width,     //width of the image
		image_neptune->height,    //height of the image
		0,                //border
		GL_RGB,           //format of origianl data
		GL_UNSIGNED_BYTE, //type of data
		image_neptune->pixels);



	////////////////////////////////////////
	// saturn
	///////////////////////////////////////

	string err9;
	//load the OBJ file to shapes
	bool  ret9 = tinyobj::LoadObj(shapes9, materials9, err9, inputfile9.c_str(), basepath.c_str());


	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors9(shapes9[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err9.empty()) { // `err` may contain warning message.
		std::cerr << err9 << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile9 << " with shapes: " << shapes9.size() << std::endl;

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao_saturn = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes9[0].mesh.positions[0]), shapes9[0].mesh.positions.size() * sizeof(float), g_simpleShader_planet, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes9[0].mesh.indices[0]), shapes9[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes9[0].mesh.texcoords[0]), shapes9[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_planet, "a_uv", 2);
	gl_createAndBindAttribute(&(shapes9[0].mesh.normals[0]), shapes9[0].mesh.normals.size() * sizeof(float), g_simpleShader_planet, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_saturn = shapes9[0].mesh.indices.size() / 3;

	Image* image_saturn = loadBMP("assets/saturn.bmp");
	glGenTextures(1, &texture_id_saturn);
	glBindTexture(GL_TEXTURE_2D, texture_id_saturn);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,    //target
		0,                //level = 0 base, no mipmap
		GL_RGB,           //how the data will bee stored
		image_saturn->width,     //width of the image
		image_saturn->height,    //height of the image
		0,                //border
		GL_RGB,           //format of origianl data
		GL_UNSIGNED_BYTE, //type of data
		image_saturn->pixels);



	////////////////////////////////////////
	// uranus
	///////////////////////////////////////

	string err10;
	//load the OBJ file to shapes
	bool ret10 = tinyobj::LoadObj(shapes10, materials10, err10, inputfile10.c_str(), basepath.c_str());


	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors10(shapes10[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err10.empty()) { // `err` may contain warning message.
		std::cerr << err10 << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile10 << " with shapes: " << shapes10.size() << std::endl;

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao_uranus = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes10[0].mesh.positions[0]), shapes10[0].mesh.positions.size() * sizeof(float), g_simpleShader_planet, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes10[0].mesh.indices[0]), shapes10[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes10[0].mesh.texcoords[0]), shapes10[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_planet, "a_uv", 2);
	gl_createAndBindAttribute(&(shapes10[0].mesh.normals[0]), shapes10[0].mesh.normals.size() * sizeof(float), g_simpleShader_planet, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_uranus = shapes10[0].mesh.indices.size() / 3;

	Image* image_uranus = loadBMP("assets/uranus.bmp");
	glGenTextures(1, &texture_id_uranus);
	glBindTexture(GL_TEXTURE_2D, texture_id_uranus);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,    //target
		0,                //level = 0 base, no mipmap
		GL_RGB,           //how the data will bee stored
		image_uranus->width,     //width of the image
		image_uranus->height,    //height of the image
		0,                //border
		GL_RGB,           //format of origianl data
		GL_UNSIGNED_BYTE, //type of data
		image_uranus->pixels);



	////////////////////////////////////////
	// venus
	///////////////////////////////////////

	string err11;
	//load the OBJ file to shapes
	bool  ret11 = tinyobj::LoadObj(shapes11, materials11, err11, inputfile11.c_str(), basepath.c_str());


	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors11(shapes11[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err11.empty()) { // `err` may contain warning message.
		std::cerr << err11 << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile11 << " with shapes: " << shapes11.size() << std::endl;

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao_venus = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes11[0].mesh.positions[0]), shapes11[0].mesh.positions.size() * sizeof(float), g_simpleShader_planet, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes11[0].mesh.indices[0]), shapes11[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes11[0].mesh.texcoords[0]), shapes11[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_planet, "a_uv", 2);
	gl_createAndBindAttribute(&(shapes11[0].mesh.normals[0]), shapes11[0].mesh.normals.size() * sizeof(float), g_simpleShader_planet, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_venus = shapes11[0].mesh.indices.size() / 3;

	Image* image_venus = loadBMP("assets/venus.bmp");
	glGenTextures(1, &texture_id_venus);
	glBindTexture(GL_TEXTURE_2D, texture_id_venus);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,    //target
		0,                //level = 0 base, no mipmap
		GL_RGB,           //how the data will bee stored
		image_venus->width,     //width of the image
		image_venus->height,    //height of the image
		0,                //border
		GL_RGB,           //format of origianl data
		GL_UNSIGNED_BYTE, //type of data
		image_venus->pixels);






	//**********************
	// FONDO
	//**********************

	string err2;
	//load the OBJ file to shapes
	bool  ret2 = tinyobj::LoadObj(shapes2, materials2, err2, inputfile2.c_str(), basepath.c_str());


	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors2(shapes2[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err2.empty()) { // `err` may contain warning message.
		std::cerr << err2 << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile2 << " with shapes: " << shapes2.size() << std::endl;


	//**********************
	// CODE TO LOAD EVERYTHING INTO MEMORY
	//**********************

	//load the shader
	Shader simpleShader_sky("src/shader_sky.vert", "src/shader_sky.frag");
	g_simpleShader_sky = simpleShader_sky.program;


	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao_sky = gl_createAndBindVAO();
	gl_createAndBindAttribute(&(shapes2[0].mesh.positions[0]), shapes2[0].mesh.positions.size() * sizeof(float), g_simpleShader_sky, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes2[0].mesh.indices[0]), shapes2[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes2[0].mesh.texcoords[0]), shapes2[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sky, "a_uv", 2);
	gl_unbindVAO();

	g_NumTriangles_sky = shapes2[0].mesh.indices.size() / 3;

	//TEXTURA
	Image* image2 = loadBMP("assets/milkyway.bmp");
	glGenTextures(1, &texture_id2);
	glBindTexture(GL_TEXTURE_2D, texture_id2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2->width, image2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->pixels);





	//**********************
	// SOL
	//**********************

	string err3;
	//load the OBJ file to shapes
	bool  ret3 = tinyobj::LoadObj(shapes3, materials3, err3, inputfile3.c_str(), basepath.c_str());


	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors3(shapes3[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err3.empty()) { // `err` may contain warning message.
		std::cerr << err3 << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile3 << " with shapes: " << shapes3.size() << std::endl;


	//**********************
	// CODE TO LOAD EVERYTHING INTO MEMORY
	//**********************

	//load the shader
	Shader simpleShader_sun("src/shader_sun.vert", "src/shader_sun.frag");
	g_simpleShader_sun = simpleShader_sun.program;

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao_sun = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes3[0].mesh.positions[0]), shapes3[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);
	gl_createIndexBuffer(&(shapes3[0].mesh.indices[0]), shapes3[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes3[0].mesh.texcoords[0]), shapes3[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);
	gl_createAndBindAttribute(&(shapes3[0].mesh.normals[0]), shapes3[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);



	gl_unbindVAO();

	g_NumTriangles_sun = shapes3[0].mesh.indices.size() / 3;


	Image* image3 = loadBMP("assets/sun.bmp");
	glGenTextures(1, &texture_id3);
	glBindTexture(GL_TEXTURE_2D, texture_id3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,    //target
		0,                //level = 0 base, no mipmap
		GL_RGB,           //how the data will bee stored
		image3->width,     //width of the image
		image3->height,    //height of the image
		0,                //border
		GL_RGB,           //format of origianl data
		GL_UNSIGNED_BYTE, //type of data
		image3->pixels);



	
}

// ------------------------------------------------------------------------------------------
// This function actually draws to screen and called non-stop, in a loop
// ------------------------------------------------------------------------------------------
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glUseProgram(g_simpleShader_sky);


	GLuint u_model = glGetUniformLocation(g_simpleShader_sky, "u_model");
	GLuint u_view = glGetUniformLocation(g_simpleShader_sky, "u_view");
	GLuint u_projection = glGetUniformLocation(g_simpleShader_sky, "u_projection");
	//set MVP
	mat4 model_matrix = translate(mat4(1.0f), eye);
	mat4 view_matrix = lookAt(eye, center, vec3(0, 1, 0));
	mat4 projection_matrix = glm::perspective(120.0f,	(float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);
	//send all values to shader
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));




	GLuint u_texture2 = glGetUniformLocation(g_simpleShader_sky, "u_texture");
	glUniform1i(u_texture2, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id2);

	gl_bindVAO(g_Vao_sky);
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_sky, GL_UNSIGNED_INT, 0);

	glUseProgram(0);






	///////////////////////////////////////////////////////
	// EL SOL
	///////////////////////////////////////////////////////
	

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glUseProgram(g_simpleShader_sun);
	gl_bindVAO(g_Vao_sun);


	//Posicio
	GLuint model_loc = glGetUniformLocation(g_simpleShader_sun, "u_model");
	mat4 model = translate(mat4(1.0f), vec3(-12.0f, 0.0f, 2.0f));	// x y z	
	mat4 model3 = scale(mat4(1.0f), vec3(6.0f, 6.0f,6.0f));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model * model3));

	//create preojection matrix and pass to shader
	projection_matrix = perspective(
		90.0f,	//Field of view
		1.0f,	//Aspect ratio
		0.1f,	//near plane (distance from camera)
		50.0f	//Far plane (distance from camera)
	);
	GLuint projection_loc = glGetUniformLocation(g_simpleShader_sun, "u_projection");
	glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	mat4 view = lookAt(eye, center, vec3(0, 1, 0));
	
	GLuint view_loc = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));


	//find the sample uniform in the shader
	GLuint u_texture3 = glGetUniformLocation(g_simpleShader_sun, "u_texture");


	glUniform1i(u_texture3, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id3);
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_sun, GL_UNSIGNED_INT, 0);
	

	glUseProgram(0);


	/////////////////////////////////////////////////////////////
	// LA TERRA
	////////////////////////////////////////////////////////////

	// STEP 4: add depth test
	glEnable(GL_DEPTH_TEST),
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	g_light_dir3 = vec3(-5, 8, 0);


	// activate shader
	glUseProgram(g_simpleShader);


	// STEP 9: Bind the texture unit

	//bind the geometry
	gl_bindVAO(g_Vao);

	//ESCALAR I MOURE
	GLuint model_loc2 = glGetUniformLocation(g_simpleShader, "u_model");

	mat4 model5 = translate(mat4(1.0f), vec3(x-0.25, y+0.05, z)); // x y z
	mat4 model6 = rotate(mat4(1.0f), 45.0f, vec3(0.0f,0.0f, 1.0f)); // x y z
	mat4 model7 = scale(mat4(1.0f), vec3(0.1f,0.1f, 0.1f)); // x y z

	glUniformMatrix4fv(model_loc2, 1, GL_FALSE, glm::value_ptr(model5*model6*model7));


	//create projection matrix and pass to shader
	mat4 projection_matrix2 = perspective(
		90.0f, // Field of view
		1.0f, // Aspect ratio
		0.1f, // near plane (distance from camera)
		50.0f // Far plane (distance from camera)
	);
	GLuint projection_loc2 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc2, 1, GL_FALSE, glm::value_ptr(projection_matrix2));


	// create view matrix and pass to shader in draw()
	mat4 view_matrix2 = glm::lookAt(
		eye,
		center + eye,
		up
	);
	GLuint view_loc2 = glGetUniformLocation(g_simpleShader, "u_view");
	glUniformMatrix4fv(view_loc2, 1, GL_FALSE, glm::value_ptr(view_matrix2));









	//find the sample uniform in the shader
	GLuint u_texture = glGetUniformLocation(g_simpleShader, "u_texture");

	GLuint light_loc5 = glGetUniformLocation(g_simpleShader, "u_light_dir");
	glUniform3f(light_loc5, g_light_dir3.x, g_light_dir3.y, g_light_dir3.z);

	GLuint cam_pos_loc5 = glGetUniformLocation(g_simpleShader, "u_cam_pos");

	// this is the camera position, if you a view matrix this is the position of eye
	glUniform3f(cam_pos_loc5, eye.x, eye.y , eye.z);
	GLuint ambient_loc5 = glGetUniformLocation(g_simpleShader, "u_ambient");
	glUniform3f(ambient_loc5, 0.0, 0.0, 0.2);
	GLuint diffuse_loc5 = glGetUniformLocation(g_simpleShader, "u_diffuse");
	glUniform3f(diffuse_loc5, 1.0, 1.0, 1.0); // blue light
	GLuint specular_loc5 = glGetUniformLocation(g_simpleShader, "u_specular");
	glUniform3f(specular_loc5, 1.0, 1.0, 1.0);
	GLuint shininess_loc5 = glGetUniformLocation(g_simpleShader, "u_shininess");
	glUniform1f(shininess_loc5, 80.0);



	// bind the sampler to the texture unit 0
	glUniform1i(u_texture, 0);
	// activate texture unit 0 and bin the texture object
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);


	GLuint u_texture_normal = glGetUniformLocation(g_simpleShader, "u_texture_normal");
	glUniform1i(u_texture_normal, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_normal);


	GLuint u_texture_spec = glGetUniformLocation(g_simpleShader, "u_texture_spec");
	glUniform1i(u_texture_spec, 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_spec);


	GLuint u_texture_night = glGetUniformLocation(g_simpleShader, "u_texture_night");
	glUniform1i(u_texture_night, 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_night);



	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);


	glUseProgram(0);







	/////////////////////////////////////////////////////////////
	// MERCURI
	////////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST),
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	g_light_dir4 = vec3(-5, 8, 7);


	// activate shader
	glUseProgram(g_simpleShader_planet);


	// STEP 9: Bind the texture unit

	//bind the geometry
	gl_bindVAO(g_Vao_mercury);

	//ESCALAR I MOURE
	GLuint model_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_model");

	mat4 model8 = translate(mat4(1.0f), vec3(x - 1.7, y+0.02, z-1)); // x y z
	mat4 model9 = rotate(mat4(1.0f), 45.0f, vec3(0.0f, 0.0f, 1.0f)); // x y z
	mat4 model10 = scale(mat4(1.0f), vec3(0.05f, 0.05f, 0.05f)); // x y z

	glUniformMatrix4fv(model_loc6, 1, GL_FALSE, glm::value_ptr(model8* model9* model10));


	//create projection matrix and pass to shader
	mat4 projection_matrix6 = perspective(
		90.0f, // Field of view
		1.0f, // Aspect ratio
		0.1f, // near plane (distance from camera)
		50.0f // Far plane (distance from camera)
	);
	GLuint projection_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_projection");
	glUniformMatrix4fv(projection_loc6, 1, GL_FALSE, glm::value_ptr(projection_matrix6));


	// create view matrix and pass to shader in draw()
	mat4 view_matrix6 = glm::lookAt(
		eye,
		center + eye,
		up
	);
	GLuint view_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_view");
	glUniformMatrix4fv(view_loc6, 1, GL_FALSE, glm::value_ptr(view_matrix6));





	//find the sample uniform in the shader
	GLuint u_texture6 = glGetUniformLocation(g_simpleShader_planet, "u_texture");

	GLuint light_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_light_dir");
	glUniform3f(light_loc6, g_light_dir4.x, g_light_dir4.y, g_light_dir4.z);

	GLuint cam_pos_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_cam_pos");

	// this is the camera position, if you a view matrix this is the position of eye
	glUniform3f(cam_pos_loc6, eye.x, eye.y, eye.z);
	GLuint ambient_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_ambient");
	glUniform3f(ambient_loc6, 0.0, 0.0, 0.2);
	GLuint diffuse_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_diffuse");
	glUniform3f(diffuse_loc6, 1.0, 1.0, 1.0); // blue light
	GLuint specular_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_specular");
	glUniform3f(specular_loc6, 1.0, 1.0, 1.0);
	GLuint shininess_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_shininess");
	glUniform1f(shininess_loc6, 80.0);


	// bind the sampler to the texture unit 0
	glUniform1i(u_texture6, 0);
	// activate texture unit 0 and bin the texture object
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_mercury);


	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_mercury, GL_UNSIGNED_INT, 0);

	glUseProgram(0);





	/////////////////////////////////////////////////////////////
	// venus
	////////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST),
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	g_light_dir5 = vec3(-5, 3.5, 1);

	// activate shader
	glUseProgram(g_simpleShader_planet);

	//bind the geometry
	gl_bindVAO(g_Vao_venus);

	//ESCALAR I MOURE
	model_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_model");

	model8 = translate(mat4(1.0f), vec3(x - 0.75, y-0.02, z)); // x y z
	model9 = rotate(mat4(1.0f), 45.0f, vec3(0.0f, 0.0f, 1.0f)); // x y z
	model10 = scale(mat4(1.0f), vec3(0.08f, 0.08f, 0.08f)); // x y z

	glUniformMatrix4fv(model_loc6, 1, GL_FALSE, glm::value_ptr(model8* model9* model10));


	//create projection matrix and pass to shader
	projection_matrix6 = perspective(
		90.0f, // Field of view
		1.0f, // Aspect ratio
		0.1f, // near plane (distance from camera)
		50.0f // Far plane (distance from camera)
	);
	projection_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_projection");
	glUniformMatrix4fv(projection_loc6, 1, GL_FALSE, glm::value_ptr(projection_matrix6));


	// create view matrix and pass to shader in draw()
	view_matrix6 = glm::lookAt(
		eye,
		center + eye,
		up
	);
	view_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_view");
	glUniformMatrix4fv(view_loc6, 1, GL_FALSE, glm::value_ptr(view_matrix6));

	//find the sample uniform in the shader
	u_texture6 = glGetUniformLocation(g_simpleShader_planet, "u_texture");

	light_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_light_dir");
	glUniform3f(light_loc6, g_light_dir5.x, g_light_dir5.y, g_light_dir5.z);

	cam_pos_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_cam_pos");

	// this is the camera position, if you a view matrix this is the position of eye
	glUniform3f(cam_pos_loc6, eye.x, eye.y, eye.z);
	ambient_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_ambient");
	glUniform3f(ambient_loc6, 0.0, 0.0, 0.2);
	diffuse_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_diffuse");
	glUniform3f(diffuse_loc6, 1.0, 1.0, 1.0); // blue light
	specular_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_specular");
	glUniform3f(specular_loc6, 1.0, 1.0, 1.0);
	shininess_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_shininess");
	glUniform1f(shininess_loc6, 80.0);

	// bind the sampler to the texture unit 0
	glUniform1i(u_texture6, 0);
	// activate texture unit 0 and bin the texture object
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_venus);

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_venus, GL_UNSIGNED_INT, 0);

	glUseProgram(0);



	/////////////////////////////////////////////////////////////
	// moon
	////////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST),
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	g_light_dir6 = vec3(-10, 10, 6);

	// activate shader
	glUseProgram(g_simpleShader_planet);

	//bind the geometry
	gl_bindVAO(g_Vao_venus);

	//ESCALAR I MOURE
	model_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_model");

	model8 = translate(mat4(1.0f), vec3(x - 0.15, y + 0.07, z+0.2)); // x y z
	model9 = rotate(mat4(1.0f), 45.0f, vec3(0.0f, 0.0f, 1.0f)); // x y z
	model10 = scale(mat4(1.0f), vec3(0.02f, 0.02f, 0.02f)); // x y z

	glUniformMatrix4fv(model_loc6, 1, GL_FALSE, glm::value_ptr(model8* model9* model10));


	//create projection matrix and pass to shader
	projection_matrix6 = perspective(
		90.0f, // Field of view
		1.0f, // Aspect ratio
		0.1f, // near plane (distance from camera)
		50.0f // Far plane (distance from camera)
	);
	projection_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_projection");
	glUniformMatrix4fv(projection_loc6, 1, GL_FALSE, glm::value_ptr(projection_matrix6));


	// create view matrix and pass to shader in draw()
	view_matrix6 = glm::lookAt(
		eye,
		center + eye,
		up
	);
	view_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_view");
	glUniformMatrix4fv(view_loc6, 1, GL_FALSE, glm::value_ptr(view_matrix6));

	//find the sample uniform in the shader
	u_texture6 = glGetUniformLocation(g_simpleShader_planet, "u_texture");

	light_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_light_dir");
	glUniform3f(light_loc6, g_light_dir6.x, g_light_dir6.y, g_light_dir6.z);

	cam_pos_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_cam_pos");

	// this is the camera position, if you a view matrix this is the position of eye
	glUniform3f(cam_pos_loc6, eye.x, eye.y, eye.z);
	ambient_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_ambient");
	glUniform3f(ambient_loc6, 0.0, 0.0, 0.2);
	diffuse_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_diffuse");
	glUniform3f(diffuse_loc6, 1.0, 1.0, 1.0); // blue light
	specular_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_specular");
	glUniform3f(specular_loc6, 1.0, 1.0, 1.0);
	shininess_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_shininess");
	glUniform1f(shininess_loc6, 80.0);

	// bind the sampler to the texture unit 0
	glUniform1i(u_texture6, 0);
	// activate texture unit 0 and bin the texture object
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_moon);

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_moon, GL_UNSIGNED_INT, 0);

	glUseProgram(0);







	/////////////////////////////////////////////////////////////
	// jupiter
	////////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST),
		glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	g_light_dir7 = vec3(-40, 40, 2);

	// activate shader
	glUseProgram(g_simpleShader_planet);

	//bind the geometry
	gl_bindVAO(g_Vao_venus);

	//ESCALAR I MOURE
	model_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_model");

	model8 = translate(mat4(1.0f), vec3(x + 1, y, z-1)); // x y z
	model9 = rotate(mat4(1.0f), 45.0f, vec3(0.0f, 0.0f, 1.0f)); // x y z
	model10 = scale(mat4(1.0f), vec3(0.2f, 0.2f, 0.2f)); // x y z

	glUniformMatrix4fv(model_loc6, 1, GL_FALSE, glm::value_ptr(model8* model9* model10));


	//create projection matrix and pass to shader
	projection_matrix6 = perspective(
		90.0f, // Field of view
		1.0f, // Aspect ratio
		0.1f, // near plane (distance from camera)
		50.0f // Far plane (distance from camera)
	);
	projection_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_projection");
	glUniformMatrix4fv(projection_loc6, 1, GL_FALSE, glm::value_ptr(projection_matrix6));


	// create view matrix and pass to shader in draw()
	view_matrix6 = glm::lookAt(
		eye,
		center + eye,
		up
	);
	view_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_view");
	glUniformMatrix4fv(view_loc6, 1, GL_FALSE, glm::value_ptr(view_matrix6));

	//find the sample uniform in the shader
	u_texture6 = glGetUniformLocation(g_simpleShader_planet, "u_texture");

	light_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_light_dir");
	glUniform3f(light_loc6, g_light_dir7.x, g_light_dir7.y, g_light_dir7.z);

	cam_pos_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_cam_pos");

	// this is the camera position, if you a view matrix this is the position of eye
	glUniform3f(cam_pos_loc6, eye.x, eye.y, eye.z);
	ambient_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_ambient");
	glUniform3f(ambient_loc6, 0.0, 0.0, 0.2);
	diffuse_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_diffuse");
	glUniform3f(diffuse_loc6, 1.0, 1.0, 1.0); // blue light
	specular_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_specular");
	glUniform3f(specular_loc6, 1.0, 1.0, 1.0);
	shininess_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_shininess");
	glUniform1f(shininess_loc6, 80.0);

	// bind the sampler to the texture unit 0
	glUniform1i(u_texture6, 0);
	// activate texture unit 0 and bin the texture object
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_jupiter);

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_jupiter, GL_UNSIGNED_INT, 0);

	glUseProgram(0);



	////////////////////////////////////////////////////////////
	// mars
	////////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST),
		glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	g_light_dir8 = vec3(-40, 40, 2);

	// activate shader
	glUseProgram(g_simpleShader_planet);

	//bind the geometry
	gl_bindVAO(g_Vao_venus);

	//ESCALAR I MOURE
	model_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_model");

	model8 = translate(mat4(1.0f), vec3(x + 0.2, y - 0.05, z)); // x y z
	model9 = rotate(mat4(1.0f), 45.0f, vec3(0.0f, 0.0f, 1.0f)); // x y z
	model10 = scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f)); // x y z

	glUniformMatrix4fv(model_loc6, 1, GL_FALSE, glm::value_ptr(model8* model9* model10));


	//create projection matrix and pass to shader
	projection_matrix6 = perspective(
		90.0f, // Field of view
		1.0f, // Aspect ratio
		0.1f, // near plane (distance from camera)
		50.0f // Far plane (distance from camera)
	);
	projection_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_projection");
	glUniformMatrix4fv(projection_loc6, 1, GL_FALSE, glm::value_ptr(projection_matrix6));


	// create view matrix and pass to shader in draw()
	view_matrix6 = glm::lookAt(
		eye,
		center + eye,
		up
	);
	view_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_view");
	glUniformMatrix4fv(view_loc6, 1, GL_FALSE, glm::value_ptr(view_matrix6));

	//find the sample uniform in the shader
	u_texture6 = glGetUniformLocation(g_simpleShader_planet, "u_texture");

	light_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_light_dir");
	glUniform3f(light_loc6, g_light_dir8.x, g_light_dir8.y, g_light_dir8.z);

	cam_pos_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_cam_pos");

	// this is the camera position, if you a view matrix this is the position of eye
	glUniform3f(cam_pos_loc6, eye.x, eye.y, eye.z);
	ambient_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_ambient");
	glUniform3f(ambient_loc6, 0.0, 0.0, 0.2);
	diffuse_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_diffuse");
	glUniform3f(diffuse_loc6, 1.0, 1.0, 1.0); // blue light
	specular_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_specular");
	glUniform3f(specular_loc6, 1.0, 1.0, 1.0);
	shininess_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_shininess");
	glUniform1f(shininess_loc6, 80.0);

	// bind the sampler to the texture unit 0
	glUniform1i(u_texture6, 0);
	// activate texture unit 0 and bin the texture object
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_mars);

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_mars, GL_UNSIGNED_INT, 0);

	glUseProgram(0);





	/////////////////////////////////////////////////////////////
	// neptune
	////////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST),
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	g_light_dir9 = vec3(-10, 10, -10);

	// activate shader
	glUseProgram(g_simpleShader_planet);

	//bind the geometry
	gl_bindVAO(g_Vao_venus);

	//ESCALAR I MOURE
	model_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_model");

	model8 = translate(mat4(1.0f), vec3(x + 1.8, y+0.04, z)); // x y z
	model9 = rotate(mat4(1.0f), 45.0f, vec3(0.0f, 0.0f, 1.0f)); // x y z
	model10 = scale(mat4(1.0f), vec3(0.07f, 0.07f, 0.07f)); // x y z

	glUniformMatrix4fv(model_loc6, 1, GL_FALSE, glm::value_ptr(model8* model9* model10));


	//create projection matrix and pass to shader
	projection_matrix6 = perspective(
		90.0f, // Field of view
		1.0f, // Aspect ratio
		0.1f, // near plane (distance from camera)
		50.0f // Far plane (distance from camera)
	);
	projection_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_projection");
	glUniformMatrix4fv(projection_loc6, 1, GL_FALSE, glm::value_ptr(projection_matrix6));


	// create view matrix and pass to shader in draw()
	view_matrix6 = glm::lookAt(
		eye,
		center + eye,
		up
	);
	view_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_view");
	glUniformMatrix4fv(view_loc6, 1, GL_FALSE, glm::value_ptr(view_matrix6));

	//find the sample uniform in the shader
	u_texture6 = glGetUniformLocation(g_simpleShader_planet, "u_texture");

	light_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_light_dir");
	glUniform3f(light_loc6, g_light_dir9.x, g_light_dir9.y, g_light_dir9.z);

	cam_pos_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_cam_pos");

	// this is the camera position, if you a view matrix this is the position of eye
	glUniform3f(cam_pos_loc6, eye.x, eye.y, eye.z);
	ambient_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_ambient");
	glUniform3f(ambient_loc6, 0.0, 0.0, 0.2);
	diffuse_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_diffuse");
	glUniform3f(diffuse_loc6, 1.0, 1.0, 1.0); // blue light
	specular_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_specular");
	glUniform3f(specular_loc6, 1.0, 1.0, 1.0);
	shininess_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_shininess");
	glUniform1f(shininess_loc6, 80.0);

	// bind the sampler to the texture unit 0
	glUniform1i(u_texture6, 0);
	// activate texture unit 0 and bin the texture object
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_neptune);

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_neptune, GL_UNSIGNED_INT, 0);

	glUseProgram(0);





	/////////////////////////////////////////////////////////////
	// saturn
	////////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST),
		glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	g_light_dir10 = vec3(-10, 10, -10);

	// activate shader
	glUseProgram(g_simpleShader_planet);

	//bind the geometry
	gl_bindVAO(g_Vao_venus);

	//ESCALAR I MOURE
	model_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_model");

	model8 = translate(mat4(1.0f), vec3(x + 1.1, y+0.01, z)); // x y z
	model9 = rotate(mat4(1.0f), 45.0f, vec3(0.0f, 0.0f, 1.0f)); // x y z
	model10 = scale(mat4(1.0f), vec3(0.06f, 0.06f, 0.06f)); // x y z

	glUniformMatrix4fv(model_loc6, 1, GL_FALSE, glm::value_ptr(model8* model9* model10));


	//create projection matrix and pass to shader
	projection_matrix6 = perspective(
		90.0f, // Field of view
		1.0f, // Aspect ratio
		0.1f, // near plane (distance from camera)
		50.0f // Far plane (distance from camera)
	);
	projection_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_projection");
	glUniformMatrix4fv(projection_loc6, 1, GL_FALSE, glm::value_ptr(projection_matrix6));


	// create view matrix and pass to shader in draw()
	view_matrix6 = glm::lookAt(
		eye,
		center + eye,
		up
	);
	view_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_view");
	glUniformMatrix4fv(view_loc6, 1, GL_FALSE, glm::value_ptr(view_matrix6));

	//find the sample uniform in the shader
	u_texture6 = glGetUniformLocation(g_simpleShader_planet, "u_texture");

	light_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_light_dir");
	glUniform3f(light_loc6, g_light_dir10.x, g_light_dir10.y, g_light_dir10.z);

	cam_pos_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_cam_pos");

	// this is the camera position, if you a view matrix this is the position of eye
	glUniform3f(cam_pos_loc6, eye.x, eye.y, eye.z);
	ambient_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_ambient");
	glUniform3f(ambient_loc6, 0.0, 0.0, 0.2);
	diffuse_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_diffuse");
	glUniform3f(diffuse_loc6, 1.0, 1.0, 1.0); // blue light
	specular_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_specular");
	glUniform3f(specular_loc6, 1.0, 1.0, 1.0);
	shininess_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_shininess");
	glUniform1f(shininess_loc6, 80.0);

	// bind the sampler to the texture unit 0
	glUniform1i(u_texture6, 0);
	// activate texture unit 0 and bin the texture object
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_saturn);

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_saturn, GL_UNSIGNED_INT, 0);

	glUseProgram(0);




	/////////////////////////////////////////////////////////////
	// uranus
	////////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST),
		glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	g_light_dir11 = vec3(-10, 10, -10);

	// activate shader
	glUseProgram(g_simpleShader_planet);

	//bind the geometry
	gl_bindVAO(g_Vao_venus);

	//ESCALAR I MOURE
	model_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_model");

	model8 = translate(mat4(1.0f), vec3(x + 1.45, y-0.05, z)); // x y z
	model9 = rotate(mat4(1.0f), 45.0f, vec3(0.0f, 0.0f, 1.0f)); // x y z
	model10 = scale(mat4(1.0f), vec3(0.05f, 0.05f, 0.05f)); // x y z

	glUniformMatrix4fv(model_loc6, 1, GL_FALSE, glm::value_ptr(model8* model9* model10));


	//create projection matrix and pass to shader
	projection_matrix6 = perspective(
		90.0f, // Field of view
		1.0f, // Aspect ratio
		0.1f, // near plane (distance from camera)
		50.0f // Far plane (distance from camera)
	);
	projection_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_projection");
	glUniformMatrix4fv(projection_loc6, 1, GL_FALSE, glm::value_ptr(projection_matrix6));


	// create view matrix and pass to shader in draw()
	view_matrix6 = glm::lookAt(
		eye,
		center + eye,
		up
	);
	view_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_view");
	glUniformMatrix4fv(view_loc6, 1, GL_FALSE, glm::value_ptr(view_matrix6));

	//find the sample uniform in the shader
	u_texture6 = glGetUniformLocation(g_simpleShader_planet, "u_texture");

	light_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_light_dir");
	glUniform3f(light_loc6, g_light_dir11.x, g_light_dir11.y, g_light_dir11.z);

	cam_pos_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_cam_pos");

	// this is the camera position, if you a view matrix this is the position of eye
	glUniform3f(cam_pos_loc6, eye.x, eye.y, eye.z);
	ambient_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_ambient");
	glUniform3f(ambient_loc6, 0.0, 0.0, 0.2);
	diffuse_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_diffuse");
	glUniform3f(diffuse_loc6, 1.0, 1.0, 1.0); // blue light
	specular_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_specular");
	glUniform3f(specular_loc6, 1.0, 1.0, 1.0);
	shininess_loc6 = glGetUniformLocation(g_simpleShader_planet, "u_shininess");
	glUniform1f(shininess_loc6, 80.0);

	// bind the sampler to the texture unit 0
	glUniform1i(u_texture6, 0);
	// activate texture unit 0 and bin the texture object
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_uranus);

	// Draw to screen
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_uranus, GL_UNSIGNED_INT, 0);

	glUseProgram(0);










	



}


// ------------------------------------------------------------------------------------------
// This function is called every time you click the mouse
// ------------------------------------------------------------------------------------------
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        cout << "Left mouse down at" << mouse_x << ", " << mouse_y << endl;
    }
}


// ------------------------------------------------------------------------------------------
// This function is called every time you press a screen
// ------------------------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//quit
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	//reload
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		load();


	const float cameraSpeed = 0.05f; // adjust accordingly
	/*
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		x = x + 0.1f;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		x = x - 0.1f;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		z = z + 0.1f;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		z = z - 0.1f;
	}*/


	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		eye -= glm::normalize(glm::cross(center, up)) * cameraSpeed;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		eye += glm::normalize(glm::cross(center, up)) * cameraSpeed;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		eye += cameraSpeed * center;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		eye -= cameraSpeed * center;
	}


}

// ------------------------------------------------------------------------------------------
// This function is called every time you click the mouse
// ------------------------------------------------------------------------------------------
void onMouseMove(GLFWwindow* window, double x, double y) {
	cout << "Mouse at" << x << ", " << y << endl;
	if (aux == 1) {
		if (x > auxX) {
			center.x = center.x + 0.1f;
		}

		if (x < auxX) {
			center.x = center.x - 0.1f;
		}

		if (y > auxY) {
			center.y = center.y - 0.1f;
		}

		if (y < auxY) {
			center.y = center.y + 0.1f;
		}

		auxX = x;
		auxY = y;
	}
}

int main(void)
{
	//setup window and boring stuff, defined in glfunctions.cpp
	GLFWwindow* window;
	if (!glfwInit())return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(g_ViewportWidth, g_ViewportHeight, "Hello OpenGL!", NULL, NULL);
	if (!window) { glfwTerminate();    return -1; }
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	//input callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	//load all the resources
	load();

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		draw();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();

		//mouse position must be tracked constantly (callbacks do not give accurate delta)
		glfwGetCursorPos(window, &mouse_x, &mouse_y);
	}

	//terminate glfw and exit
	glfwTerminate();
	return 0;
}


