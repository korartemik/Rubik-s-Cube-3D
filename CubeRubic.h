#pragma once
#include <iostream>
#include <fstream>
#include <set>
#include "Cube.h"

class CubeRubic {
	int*** mas;
	int* newcolor;
	
public:
	// координаты источника света
	GLfloat lightPos[4] = { 0, 100, 200, 0 };
	// отдаление
	double translateZ = -35.0;
	// проекции угла поворота на оси
	int xRot = 24, yRot = 34, zRot = 0;
	Cube cube;
	CubeRubic() {
		mas = new int** [7];
		for (int i = 1; i <= 6; i++) {
			mas[i] = new int* [3];
			mas[i][0] = new int[3];
			mas[i][1] = new int[3];
			mas[i][2] = new int[3];
			for (int a = 0; a < 3; a++) {
				for (int b = 0; b < 3; b++) {
					mas[i][a][b] = i;
				}
			}
		}
		newcolor = new int[7];
	}
	CubeRubic(Cube in): cube(in) {
		mas = new int** [7];
		for (int i = 1; i <= 6; i++) {
			mas[i] = new int* [3];
			mas[i][0] = new int[3];
			mas[i][1] = new int[3];
			mas[i][2] = new int[3];
		}
		newcolor = new int[7];
	}
	~CubeRubic() {
		delete[]mas;
		delete[]newcolor;
	}
	void display();
	void InputFromConsole();
	void InputFromFile(std::string nameoffile);
	void OutputToConsole();
	void recolor();
	void r90cl(int n);
	void r90count(int n);
	void r180deg(int n);
	bool Check();
	void OutputToFile(std::string nameoffile);
	void step1();
	void step2();
	void step3();
	void step4();
	void step5();
	void step6();
	void step7();
	void solve();
	void copy();
};