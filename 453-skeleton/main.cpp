/*
 *Assignment 1: Points, Lines, & Triangles - Fractal Generator
 *@author Manisha Gupta
 *@version 1.0
 *
 *Course: CPSC 453 L01 F2020
 *Instructor: Faramarz Famil Samavati
 * 
 * Utilized skeleton/boilerplate code provided on D2L for CPSC 453
 */

#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Geometry.h"
#include "GLDebug.h"
#include "Log.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Window.h"

typedef glm::vec3 vert;

struct State {
	int depth = 0;
	int scene = 0;
	bool operator == (State const& other) const{
		return depth == other.depth && scene == other.scene;
	}
};


class MyCallbacks : public CallbackInterface {

public:
	MyCallbacks(ShaderProgram& shader) : shader(shader) {}

	virtual void keyCallback(int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			if (key == GLFW_KEY_R) {
				shader.recompile();
			}
			if (key == GLFW_KEY_1) {
				state.scene = 1;
			}
			if (key == GLFW_KEY_2) {
				state.scene = 2;
			}
			if (key == GLFW_KEY_3) {
				state.scene = 3;
			}
			if (key == GLFW_KEY_4) {
				state.scene = 4;
			}
			if (key == GLFW_KEY_LEFT) {
				if (state.depth > 0) {
					state.depth--;
				}
			}
			if (key == GLFW_KEY_RIGHT) {
				if (state.depth < 6) {
					state.depth++;
				}
			}

		}
		 
	}

	State getState() {
		return state;
	}

private:
	ShaderProgram& shader;
	State state;
};

class SierpinskiTriangle {
public:
	SierpinskiTriangle() {}

	void createFractal(CPU_Geometry &cpuGeom, int depth) {
		// initial triangle vertices
		vert a = vert(-0.5f, -0.5f, 0.f);
		cpuGeom.verts.push_back(a);
		vert b = vert(0.5f, -0.5f, 0.f);
		cpuGeom.verts.push_back(b);
		vert c = vert(0.f, 0.5f, 0.f);
		cpuGeom.verts.push_back(c);

		s_triangles(a, b, c, depth, cpuGeom);
	}

private:
	void s_triangles(vert a, vert b, vert c, int depth, CPU_Geometry &cpuGeom) {
		if (depth > 0) {
			vert d = (a + b) * 0.5f;
			cpuGeom.verts.push_back(d);
			vert e = (b + c) * 0.5f;
			cpuGeom.verts.push_back(e);
			vert f = (c + a) * 0.5f;
			cpuGeom.verts.push_back(f);

			s_triangles(d, b, e, depth - 1, cpuGeom);
			s_triangles(a, d, f, depth - 1, cpuGeom);
			s_triangles(f, e, c, depth - 1, cpuGeom);
		}
		else {
			for (int i = 0; i < GLsizei(cpuGeom.verts.size()); i+=3) {
				float c1 = (rand() % 255) / 255.0f;
				float c2 = (rand() % 255) / 255.0f;
				float c3 = (rand() % 255) / 255.0f;
				cpuGeom.cols.push_back(glm::vec3(c1, c2, c3));
				cpuGeom.cols.push_back(glm::vec3(c1, c2, c3));
				cpuGeom.cols.push_back(glm::vec3(c1, c2, c3));
			}
			return;
		}
	}

};

class SquaresDiamonds {
public:
	SquaresDiamonds() {}

	void createFractal(CPU_Geometry &cpuGeom, int depth) {
		// initial square vertices
		vert a = vert(-0.5f, -0.5f, 0.f);
		cpuGeom.verts.push_back(a);
		vert b = vert(0.5f, -0.5f, 0.f);
		cpuGeom.verts.push_back(b);
		vert c = vert(0.5f, 0.5f, 0.f);
		cpuGeom.verts.push_back(c);
		vert d = vert(-0.5f, 0.5f, 0.f);
		cpuGeom.verts.push_back(d);
		cpuGeom.verts.push_back(a);
		vert e = (a + b) * 0.5f;
		cpuGeom.verts.push_back(e);
		vert f = (b + c) * 0.5f;
		cpuGeom.verts.push_back(f);
		vert g = (c + d) * 0.5f;
		cpuGeom.verts.push_back(g);
		vert h = (d + a) * 0.5f;
		cpuGeom.verts.push_back(h);
		cpuGeom.verts.push_back(e);

		squ_dia(a, b, c, d, e, f, g, h, depth, cpuGeom);
	}

private:
	void squ_dia(vert a, vert b, vert c, vert d, vert e, vert f, vert g, vert h, int depth, CPU_Geometry &cpuGeom) {
		if (depth > 0) {
			vert i = (e + f) * 0.5f;
			cpuGeom.verts.push_back(i);
			vert j = (f + g) * 0.5f;
			cpuGeom.verts.push_back(j);
			vert k = (g + h) * 0.5f;
			cpuGeom.verts.push_back(k);
			vert l = (h + e) * 0.5f;
			cpuGeom.verts.push_back(l);
			cpuGeom.verts.push_back(i);
			vert m = (i + j) * 0.5f;
			cpuGeom.verts.push_back(m);
			vert n = (j + k) * 0.5f;
			cpuGeom.verts.push_back(n);
			vert o = (k + l) * 0.5f;
			cpuGeom.verts.push_back(o);
			vert p = (l + i) * 0.5f;
			cpuGeom.verts.push_back(p);
			cpuGeom.verts.push_back(m);

			squ_dia(i, j, k, l, m, n, o, p, depth - 1, cpuGeom);
		}
		else {
			for (int i = 0; i < GLsizei(cpuGeom.verts.size()); i+=10) {
				float c1 = (rand() % 255) / 255.0f;
				float c2 = (rand() % 255) / 255.0f;
				float c3 = (rand() % 255) / 255.0f;
				cpuGeom.cols.push_back(glm::vec3(c1, c2, c3));
				cpuGeom.cols.push_back(glm::vec3(c1, c2, c3));
				cpuGeom.cols.push_back(glm::vec3(c1, c2, c3));
				cpuGeom.cols.push_back(glm::vec3(c1, c2, c3));
				cpuGeom.cols.push_back(glm::vec3(c1, c2, c3));
				float c4 = (rand() % 255) / 255.0f;
				float c5 = (rand() % 255) / 255.0f;
				float c6 = (rand() % 255) / 255.0f;
				cpuGeom.cols.push_back(glm::vec3(c4, c5, c6));
				cpuGeom.cols.push_back(glm::vec3(c4, c5, c6));
				cpuGeom.cols.push_back(glm::vec3(c4, c5, c6));
				cpuGeom.cols.push_back(glm::vec3(c4, c5, c6));
				cpuGeom.cols.push_back(glm::vec3(c4, c5, c6));
			}
			return;
		}
	}

};
// call ab, then bc, then ca
class KochSnowflake {
public:
	KochSnowflake() {}

	void createFractal(CPU_Geometry& cpuGeom, int depth) {
		// initial triangle vertices
		vert a = vert(-0.5f, -0.5f, 0.f);
		vert b = vert(0.5f, -0.5f, 0.f);
		vert c = vert(0.f, 0.5f, 0.f);

		k_snow(a, b, depth, cpuGeom);
		k_snow(b, c, depth, cpuGeom);
		k_snow(c, a, depth, cpuGeom);

		float c1 = (rand() % 255) / 255.0f;
		float c2 = (rand() % 255) / 255.0f;
		float c3 = (rand() % 255) / 255.0f;

		col = glm::vec3(c1, c2, c3);
	}

private:
	glm::vec3 col;

	vert salientpt(vert startpt, vert endpt) {
		vert midpt = endpt - startpt;				// subtract pivot which is the startpt
		vert temp;

		temp.x = midpt.x * cos(-M_PI / 3) - midpt.y * sin(-M_PI / 3);	// rotate
		temp.y = midpt.x * sin(-M_PI / 3) + midpt.y * cos(-M_PI / 3);
		temp.z = 0.f;

		temp.x += startpt.x;					   // re-add pivot
		temp.y += startpt.y;
		return temp;
	}

	void k_snow(vert a, vert b, int depth, CPU_Geometry& cpuGeom) {
		if (depth > 0) {
			vert d = (2.0f / 3.0f) * a + (1.0f / 3.0f) * b;
			vert f = (1.0f / 3.0f) * a + (2.0f / 3.0f) * b;
			vert e = salientpt(d, f);

			k_snow(a, d, depth - 1, cpuGeom);
			k_snow(d, e, depth - 1, cpuGeom);
			k_snow(e, f, depth - 1, cpuGeom);
			k_snow(f, b, depth - 1, cpuGeom);
		}
		else { // depth == 0
			cpuGeom.verts.push_back(a);
			cpuGeom.cols.push_back(col);
			cpuGeom.verts.push_back(b);
			cpuGeom.cols.push_back(col);
		}

	}

};

class DragonCurve {
public:
	DragonCurve() {}

	void createFractal(CPU_Geometry &cpuGeom, int depth) {
		// initial vertices
		vert a = vert(0.f, 0.f, 0.f);
		cpuGeom.verts.push_back(a);
		vert b = vert(0.0375f, -0.0375f, 0.f);
		cpuGeom.verts.push_back(b);
		vert c = vert(0.075f, 0.f, 0.f);
		cpuGeom.verts.push_back(c);

		d_curve(cpuGeom, depth);
	}

private:
	void rotateBack(CPU_Geometry &cpuGeom) {
		for (int i = 1; i < GLsizei(cpuGeom.verts.size()); i++) {
			vert temp = cpuGeom.verts[i];
			vert d;
			d.x = temp.x * cos(-M_PI / 4.0f) - temp.y * sin(-M_PI / 4.0f); 
			d.y = temp.x * sin(-M_PI / 4.0f) + temp.y * cos(-M_PI / 4.0f);  
			d.z = temp.z;
			cpuGeom.verts[i] = d;
		}
	}

	void copyAndRotateForward(CPU_Geometry &cpuGeom) {
		vert pivot = cpuGeom.verts[GLsizei(cpuGeom.verts.size()) - 1];  // need pivot so point being rotated can be translated back to origin
		for (int i = (GLsizei(cpuGeom.verts.size()) - 2); i >= 0; i--) {
			vert temp = cpuGeom.verts[i];
			temp.x -= pivot.x;   // translate to origin
			temp.y -= pivot.y;   // translate to origin

			vert e;
			e.x = temp.x * cos(-M_PI / 2) - temp.y * sin(-M_PI / 2);
			e.y = temp.x * sin(-M_PI / 2) + temp.y * cos(-M_PI / 2);
			e.z = temp.z;

			e.x += pivot.x;   // translate back
			e.y += pivot.y;   // translate back

			cpuGeom.verts.push_back(e);
		}
	}

	void d_curve(CPU_Geometry &cpuGeom, int depth) {
		float c1 = (rand() % 255) / 255.0f;
		float c2 = (rand() % 255) / 255.0f;
		float c3 = (rand() % 255) / 255.0f;
		if (depth > 0) {
			rotateBack(cpuGeom);
			copyAndRotateForward(cpuGeom);


			d_curve(cpuGeom, depth - 1);
		}
		else {
			for (int i = 0; i < GLsizei(cpuGeom.verts.size()); i++) {
				cpuGeom.cols.push_back(glm::vec3(c1, c2, c3));
			}
			return;
		}
	}

};

void clear(CPU_Geometry &cpuGeom) {
	cpuGeom.verts.clear();
	cpuGeom.cols.clear();
}

void upload(CPU_Geometry &cpuGeom, GPU_Geometry &gpuGeom) {
	gpuGeom.setVerts(cpuGeom.verts);
	gpuGeom.setCols(cpuGeom.cols);
}

int main() {
	Log::debug("Starting main");

	// WINDOW
	glfwInit();
	Window window(800, 800, "CPSC 453"); // can set callbacks at construction if desired

	GLDebug::enable();

	// SHADERS
	ShaderProgram shader("shaders/test.vert", "shaders/test.frag");

	// CALLBACKS
	//auto = std::shared_ptr<MyCallbacks>
	auto callbacks = std::make_shared<MyCallbacks>(shader);
	window.setCallbacks(callbacks); // can also update callbacks to new ones

	// SIERPINSKY TRIANGLE GEOMETRY
	CPU_Geometry cpuGeomst;
	GPU_Geometry gpuGeomst;
	// SQUARES AND DIAMONDS GEOMETRY
	CPU_Geometry cpuGeomsd;
	GPU_Geometry gpuGeomsd;
	// KOCH SNOWFLAKE GEOMETRY
	CPU_Geometry cpuGeomks;
	GPU_Geometry gpuGeomks;
	// DRAGON CURVE GEOMETRY
	CPU_Geometry cpuGeomdc;
	GPU_Geometry gpuGeomdc;

	State state;

	//int cachedScene = -1;			//initialized so I can reset depth

	// RENDER LOOP
	while (!window.shouldClose()) {
		glfwPollEvents();
		if (!(state == callbacks->getState())) {
			state = callbacks->getState();
			clear(cpuGeomst);
			clear(cpuGeomsd);
			clear(cpuGeomks);
			clear(cpuGeomdc);

			/*										//trying to reset depth when scene changes...doesn't work
			if (state.scene != cachedScene) {		
				state.depth = 0;
				cachedScene = state.scene;
			}
			*/

			if (state.scene == 1) {
				//sierpinski
				SierpinskiTriangle sitr;
				sitr.createFractal(cpuGeomst, state.depth);
				upload(cpuGeomst, gpuGeomst);
			}
			else if (state.scene == 2) {
				//dia squ
				SquaresDiamonds sqdi;
				sqdi.createFractal(cpuGeomsd, state.depth);
				upload(cpuGeomsd, gpuGeomsd);
			}
			else if (state.scene == 3) {
				// koch
				KochSnowflake kosn;
				kosn.createFractal(cpuGeomks, state.depth);
				upload(cpuGeomks, gpuGeomks);
			}
			else {
				//dragon
				DragonCurve drcu;
				drcu.createFractal(cpuGeomdc, state.depth);
				upload(cpuGeomdc, gpuGeomdc);
			}
		}


		glEnable(GL_FRAMEBUFFER_SRGB);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		gpuGeomst.bind();
		glDrawArrays(GL_TRIANGLES, 0, GLsizei(cpuGeomst.verts.size()));

		gpuGeomsd.bind();
		glDrawArrays(GL_LINE_STRIP, 0, GLsizei(cpuGeomsd.verts.size()));

		gpuGeomks.bind();
		glDrawArrays(GL_LINE_LOOP, 0, GLsizei(cpuGeomks.verts.size()));

		gpuGeomdc.bind();
		glDrawArrays(GL_LINE_STRIP, 0, GLsizei(cpuGeomdc.verts.size()));


		glDisable(GL_FRAMEBUFFER_SRGB); // disable sRGB for things like imgui

		window.swapBuffers();
	}

	glfwTerminate();
	return 0;
}
