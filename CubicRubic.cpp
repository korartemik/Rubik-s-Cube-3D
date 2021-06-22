#include "CubeRubic.h"
#include <Windows.h>
#define CUBE_SIZE 13
#define SPEED 10

void CubeRubic::display()
{
	//std::cout << "+ ";
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glTranslatef(0, 0, translateZ);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
	cube.draw();
	glPopMatrix();
	glutSwapBuffers();
}
void CubeRubic::recolor() {
	newcolor[1] = mas[1][1][1];
	newcolor[2] = mas[2][1][1];
	newcolor[3] = mas[3][1][1];
	newcolor[4] = mas[4][1][1];
	newcolor[5] = mas[5][1][1];
	newcolor[6] = mas[6][1][1];
	for (int k = 1; k <= 6; k++) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int d = 1; d < 7; d++) {
					if (mas[k][i][j] == newcolor[d]) {
						mas[k][i][j] = d;
						break;
					}
				}
			}
		}
	}
}
void CubeRubic::copy() {
	std::cout << "\n";
	//OutputToConsole();
	int i, j, k;
	// передн€€
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			cube.a[i][j][2].setColor(0, cube.color[mas[2][2-j][i]%6]);

	// задн€€
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			cube.a[i][j][0].setColor(1, cube.color[mas[4][2-j][2-i] % 6]);

	// снизу
	for (k = 0; k < 3; k++)
		for (j = 0; j < 3; j++)
			cube.a[j][0][k].setColor(2, cube.color[mas[1][2-k][j] % 6]);

	// сверху
	for (k = 0; k < 3; k++)
		for (j = 0; j < 3; j++)
			cube.a[j][2][k].setColor(3, cube.color[mas[6][k][j] % 6]);

	// слева
	for (i = 0; i < 3; i++)
		for (k = 0; k < 3; k++)
			cube.a[0][k][i].setColor(4, cube.color[mas[5][2-k][i] % 6]);

	// справа
	for (i = 0; i < 3; i++)
		for (k = 0; k < 3; k++)
			cube.a[2][k][i].setColor(5, cube.color[mas[3][2-k][2-i] % 6]);
}
void CubeRubic::InputFromConsole(){
	std::cout << "Top edge" << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cin >> mas[6][i][j];
		}
	}
	std::cout << "Bottom edge" << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cin >> mas[1][i][j];
		}
	}
	std::cout << "Front edge or, if viewed from above, then the lower" << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cin >> mas[2][i][j];
		}
	}
	std::cout << "Front if rotated 90 degrees clockwise" << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cin >> mas[3][i][j];
		}
	}
	std::cout << "Front if rotated 180 degrees clockwise" << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cin >> mas[4][i][j];
		}
	}
	std::cout << "Front if rotated 90 degrees counterclockwise" << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cin >> mas[5][i][j];
		}
	}
	recolor();
	copy();
}
void CubeRubic::InputFromFile(std::string nameoffile) {
	std::ifstream fin(nameoffile);
	int N = 0;
	if (!fin.good())
	{
		std::cout << "File " << nameoffile << " not found!\n";
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				fin >> N;
				mas[6][i][j] = N;
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				fin >> N;
				mas[2][i][j] = N;
			}
			for (int j = 0; j < 3; j++) {
				fin >> N;
				mas[3][i][j] = N;
			}
			for (int j = 0; j < 3; j++) {
				fin >> N;
				mas[4][i][j] = N;
			}
			for (int j = 0; j < 3; j++) {
				fin >> N;
				mas[5][i][j] = N;
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				fin >> N;
				mas[1][i][j] = N;
			}
		}
	}
	fin.close();
	recolor();
	copy();
}
void CubeRubic::OutputToConsole() {
	std::cout << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << mas[6][i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << mas[2][i][j] << " ";
		}
		std::cout << "   ";
		for (int j = 0; j < 3; j++) {
			std::cout << mas[3][i][j] << " ";
		}
		std::cout << "   ";
		for (int j = 0; j < 3; j++) {
			std::cout << mas[4][i][j] << " ";
		}
		std::cout << "   ";
		for (int j = 0; j < 3; j++) {
			std::cout << mas[5][i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << mas[1][i][j] << " ";
		}
		std::cout << "\n";
	}
}
void CubeRubic::r90cl(int n) {
	int fr[] = { 0,2,1,5,0,4,3 };
	if (((n == 2) || (n == 3)) || (n == 6)) {
		cube.Rotate(fr[n], -3);
		while (cube.current != -1) {
			Sleep(SPEED);
			cube.Rotate(fr[n], -3);
			display();
		}
	}
	else {
		cube.Rotate(fr[n], 3);
		while (cube.current != -1) {
			Sleep(SPEED);
			cube.Rotate(fr[n], 3);
			display();
		}
	}
	std::cout << n;
	int x = 0;
	int left = 0;
	int right = 0;
	int top = 0;
	int down = 0;
	if (n == 1) {
		left = 5;
		top = 2;
		down = 4;
		right = 3;
		for (int i = 0; i < 3; i++) {
			x = mas[left][2][i];
			mas[left][2][i] = mas[down][2][i];
			mas[down][2][i] = mas[right][2][i];
			mas[right][2][i] = mas[top][2][i];
			mas[top][2][i] = x;
		}
	}
	else if (n == 6) {
		left = 5;
		down = 2;
		top = 4;
		right = 3;
		for (int i = 0; i < 3; i++) {
			x = mas[left][0][i];
			mas[left][0][i] = mas[down][0][i];
			mas[down][0][i] = mas[right][0][i];
			mas[right][0][i] = mas[top][0][i];
			mas[top][0][i] = x;
		}
	}
	else if (n == 2) {
		left = 5;
		down = 1;
		top = 6;
		right = 3;
		for (int i = 0; i < 3; i++) {
			x = mas[left][i][2];
			mas[left][i][2] = mas[down][0][i];
			mas[down][0][i] = mas[right][2 - i][0];
			mas[right][2 - i][0] = mas[top][2][2 - i];
			mas[top][2][2 - i] = x;
		}
	}
	else if (n == 4) {
		left = 3;
		down = 1;
		top = 6;
		right = 5;
		for (int i = 0; i < 3; i++) {
			x = mas[left][2 - i][2];
			mas[left][2 - i][2] = mas[down][2][i];
			mas[down][2][i] = mas[right][i][0];
			mas[right][i][0] = mas[top][0][2 - i];
			mas[top][0][2 - i] = x;
		}
	}
	else if (n == 3) {
		left = 2;
		down = 1;
		top = 6;
		right = 4;
		for (int i = 0; i < 3; i++) {
			x = mas[left][i][2];
			mas[left][i][2] = mas[down][i][2];
			mas[down][i][2] = mas[right][2 - i][0];
			mas[right][2 - i][0] = mas[top][i][2];
			mas[top][i][2] = x;
		}
	}
	else if (n == 5) {
		left = 4;
		down = 1;
		top = 6;
		right = 2;
		for (int i = 0; i < 3; i++) {
			x = mas[left][2 - i][2];
			mas[left][2 - i][2] = mas[down][i][0];
			mas[down][i][0] = mas[right][i][0];
			mas[right][i][0] = mas[top][i][0];
			mas[top][i][0] = x;
		}
	}

	x = mas[n][0][0];
	mas[n][0][0] = mas[n][2][0];
	mas[n][2][0] = mas[n][2][2];
	mas[n][2][2] = mas[n][0][2];
	mas[n][0][2] = x;
	x = mas[n][0][1];
	mas[n][0][1] = mas[n][1][0];
	mas[n][1][0] = mas[n][2][1];
	mas[n][2][1] = mas[n][1][2];
	mas[n][1][2] = x;
}
void CubeRubic::r90count(int n) {
	int fr[] = { 0,2,1,5,0,4,3 };
	if (((n == 2) || (n == 3)) || (n == 6)) {
		cube.Rotate(fr[n], 3);
		while (cube.current != -1) {
			Sleep(SPEED);
			cube.Rotate(fr[n], 3);
			display();
		}
	}
	else {
		cube.Rotate(fr[n], -3);
		while (cube.current != -1) {
			Sleep(SPEED);
			cube.Rotate(fr[n], -3);
			display();
		}
	}
	std::cout << n << "'";
	int x = 0;
	int left = 0;
	int right = 0;
	int top = 0;
	int down = 0;
	if (n == 1) {
		left = 5;
		top = 2;
		down = 4;
		right = 3;
		for (int i = 0; i < 3; i++) {
			x = mas[top][2][i];
			mas[top][2][i] = mas[right][2][i];
			mas[right][2][i] = mas[down][2][i];
			mas[down][2][i] = mas[left][2][i];
			mas[left][2][i] = x;
		}
	}
	else if (n == 6) {
		left = 5;
		down = 2;
		top = 4;
		right = 3;
		for (int i = 0; i < 3; i++) {
			x = mas[top][0][i];
			mas[top][0][i] = mas[right][0][i];
			mas[right][0][i] = mas[down][0][i];
			mas[down][0][i] = mas[left][0][i];
			mas[left][0][i] = x;
		}
	}
	else if (n == 2) {
		left = 5;
		down = 1;
		top = 6;
		right = 3;
		for (int i = 0; i < 3; i++) {
			x = mas[top][2][2 - i];
			mas[top][2][2 - i] = mas[right][2 - i][0];
			mas[right][2 - i][0] = mas[down][0][i];
			mas[down][0][i] = mas[left][i][2];
			mas[left][i][2] = x;
		}
	}
	else if (n == 4) {
		left = 3;
		down = 1;
		top = 6;
		right = 5;
		for (int i = 0; i < 3; i++) {
			x = mas[top][0][2 - i];
			mas[top][0][2 - i] = mas[right][i][0];
			mas[right][i][0] = mas[down][2][i];
			mas[down][2][i] = mas[left][2 - i][2];
			mas[left][2 - i][2] = x;
		}
	}
	else if (n == 3) {
		left = 2;
		down = 1;
		top = 6;
		right = 4;
		for (int i = 0; i < 3; i++) {
			x = mas[top][i][2];
			mas[top][i][2] = mas[right][2 - i][0];
			mas[right][2 - i][0] = mas[down][i][2];
			mas[down][i][2] = mas[left][i][2];
			mas[left][i][2] = x;
		}
	}
	else if (n == 5) {
		left = 4;
		down = 1;
		top = 6;
		right = 2;
		for (int i = 0; i < 3; i++) {
			x = mas[top][i][0];
			mas[top][i][0] = mas[right][i][0];
			mas[right][i][0] = mas[down][i][0];
			mas[down][i][0] = mas[left][2 - i][2];
			mas[left][2 - i][2] = x;
		}
	}

	x = mas[n][0][0];
	mas[n][0][0] = mas[n][0][2];
	mas[n][0][2] = mas[n][2][2];
	mas[n][2][2] = mas[n][2][0];
	mas[n][2][0] = x;
	x = mas[n][0][1];
	mas[n][0][1] = mas[n][1][2];
	mas[n][1][2] = mas[n][2][1];
	mas[n][2][1] = mas[n][1][0];
	mas[n][1][0] = x;
}
void CubeRubic::r180deg(int n) {
	if (n == 1) {
		r90count(1);
		r90count(1);
	}
	else if (n == 6) {
		r90count(6);
		r90count(6);
	}
	else if (n == 2) {
		r90count(2);
		r90count(2);
	}
	else if (n == 4) {
		r90count(4);
		r90count(4);
	}
	else if (n == 3) {
		r90count(3);
		r90count(3);
	}
	else if (n == 5) {
		r90count(5);
		r90count(5);
	}

}
bool CubeRubic::Check() {
	int* check = new int[7];
	for (int i = 0; i < 7; i++) {
		check[i] = 0;
	}
	for (int k = 1; k < 7; k++) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				check[mas[k][i][j]] = check[mas[k][i][j]] + 1;
			}
		}
	}
	for (int i = 1; i < 7; i++) {
		if (check[i] != 9) {
			std::cout << check[i];
			return false;
		}
		check[i] = 0;
	}

	for (int k = 1; k < 7; k++) {
		check[mas[k][1][1]] = 1;
	}
	for (int i = 1; i < 7; i++) {
		if (check[i] != 1) {
			return false;
		}
		check[i] = 0;
	}
	for (int k = 1; k < 7; k++) {
		check[mas[k][0][1]] ++;
		check[mas[k][1][0]] ++;
		check[mas[k][2][1]] ++;
		check[mas[k][1][2]] ++;
	}
	for (int i = 1; i < 7; i++) {
		if (check[i] != 4) {
			return false;
		}
		check[i] = 0;
	}
	for (int k = 1; k < 7; k++) {
		check[mas[k][0][0]] ++;
		check[mas[k][2][0]] ++;
		check[mas[k][0][2]] ++;
		check[mas[k][2][2]] ++;
	}
	for (int i = 1; i < 7; i++) {
		if (check[i] != 4) {
			return false;
		}
		check[i] = 0;
	}
	delete[]check;
	for (int i = 0; i < 3; i++) {
		if (mas[6][2][i] == mas[2][0][i]) { return false; }
		if (mas[6][i][2] == mas[3][0][2 - i]) { return false; }
		if (mas[6][0][i] == mas[4][0][2 - i]) { return false; }
		if (mas[6][i][0] == mas[5][0][i]) { return false; }
	}
	for (int i = 0; i < 3; i++) {
		if (mas[1][0][i] == mas[2][2][i]) { return false; }
		if (mas[1][i][2] == mas[3][2][i]) { return false; }
		if (mas[1][2][i] == mas[4][2][2 - i]) { return false; }
		if (mas[1][i][0] == mas[5][2][2 - i]) { return false; }
	}
	for (int i = 0; i < 3; i++) {
		if (mas[2][i][2] == mas[3][i][0]) { return false; }
		if (mas[3][i][2] == mas[4][i][0]) { return false; }
		if (mas[4][i][2] == mas[5][i][0]) { return false; }
		if (mas[5][i][2] == mas[2][i][0]) { return false; }
	}
	return true;
}
void CubeRubic::OutputToFile(std::string nameoffile) {
	std::ofstream fout(nameoffile);
	int N = 0;
	if (!fout.good())
	{
		std::cout << "File " << nameoffile << " not found!\n";
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				fout << mas[6][i][j] << " ";
			}
			fout << "\n";
		}
		fout << "\n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				fout << mas[2][i][j] << " ";
			}
			fout << "   ";
			for (int j = 0; j < 3; j++) {
				fout << mas[3][i][j] << " ";
			}
			fout << "   ";
			for (int j = 0; j < 3; j++) {
				fout << mas[4][i][j] << " ";
			}
			fout << "   ";
			for (int j = 0; j < 3; j++) {
				fout << mas[5][i][j] << " ";
			}
			fout << "\n";
		}
		fout << "\n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				fout << mas[1][i][j] << " ";
			}
			fout << "\n";
		}
	}
	fout.close();
}
void CubeRubic::step1(){
	int k = 0;
	while (k != 4) {
		if ((mas[2][0][1] == 2) && (mas[6][2][1] == 1)) {
			r180deg(2);
		}
		else if ((mas[3][0][1] == 3) && (mas[6][1][2] == 1)) {
			r180deg(3);
		}
		else if ((mas[4][0][1] == 4) && (mas[6][0][1] == 1)) {
			r180deg(4);
		}
		else if ((mas[5][0][1] == 5) && (mas[6][1][0] == 1)) {
			r180deg(5);
		}
		else if ((mas[2][0][1] == 1) && (mas[6][2][1] == 2)) {
			r90count(6);
			r90count(3);
			r90cl(2);
			r90cl(3);
		}
		else if ((mas[3][0][1] == 1) && (mas[6][1][2] == 3)) {
			r90count(6);
			r90count(4);
			r90cl(3);
			r90cl(4);
		}
		else if ((mas[4][0][1] == 1) && (mas[6][0][1] == 4)) {
			r90count(6);
			r90count(5);
			r90cl(4);
			r90cl(5);
		}
		else if ((mas[5][0][1] == 1) && (mas[6][1][0] == 5)) {
			r90count(6);
			r90count(2);
			r90cl(5);
			r90cl(2);
		}
		else if (mas[2][1][2] == 1) {
			r90count(2);
			r90count(6);
			r90cl(2);
		}
		else if (mas[3][1][2] == 1) {
			r90count(3);
			r90count(6);
			r90cl(3);
		}
		else if (mas[4][1][2] == 1) {
			r90count(4);
			r90count(6);
			r90cl(4);
		}
		else if (mas[5][1][2] == 1) {
			r90count(5);
			r90count(6);
			r90cl(5);
		}
		else if (mas[2][1][0] == 1) {
			r90cl(2);
			r90count(6);
			r90count(2);
		}
		else if (mas[3][1][0] == 1) {
			r90cl(3);
			r90count(6);
			r90count(3);
		}
		else if (mas[4][1][0] == 1) {
			r90cl(4);
			r90count(6);
			r90count(4);
		}
		else if (mas[5][1][0] == 1) {
			r90cl(5);
			r90count(6);
			r90count(5);
		}
		else if (mas[2][2][1] == 1) {
			r180deg(2);
			r90count(6);
			r180deg(2);
		}
		else if (mas[3][2][1] == 1) {
			r180deg(3);
			r90count(6);
			r180deg(3);
		}
		else if (mas[4][2][1] == 1) {
			r180deg(4);
			r90count(6);
			r180deg(4);
		}
		else if (mas[5][2][1] == 1) {
			r180deg(5);
			r90count(6);
			r180deg(5);
		}
		else if ((mas[2][2][1] != 2) && (mas[1][0][1] == 1)) {
			r180deg(2);
			r90count(6);
			r180deg(2);
		}
		else if ((mas[3][2][1] != 3) && (mas[1][1][2] == 1)) {
			r180deg(3);
			r90count(6);
			r180deg(3);
		}
		else if ((mas[4][2][1] != 4) && (mas[1][2][1] == 1)) {
			r180deg(4);
			r90count(6);
			r180deg(4);
		}
		else if ((mas[5][2][1] != 5) && (mas[1][1][0] == 1)) {
			r180deg(5);
			r90count(6);
			r180deg(5);
		}
		else {
			r90count(6);
			k++;
			continue;
		}
		k = 0;
	}

}
void CubeRubic::step2() {
	int k = 0;
	int c = 0;
	while (k != 4) {
		if (((mas[2][0][2] == 1) && (mas[3][0][0] == 3)) && (mas[6][2][2] == 2)) {
			r90count(2);
			r90count(6);
			r90cl(2);
		}
		else if (((mas[2][0][0] == 2) && (mas[5][0][2] == 1)) && (mas[6][2][0] == 5)) {
			r90count(5);
			r90count(6);
			r90cl(5);
		}
		else if (((mas[4][0][0] == 4) && (mas[3][0][2] == 1)) && (mas[6][0][2] == 3)) {
			r90count(3);
			r90count(6);
			r90cl(3);
		}
		else if (((mas[5][0][0] == 5) && (mas[4][0][2] == 1)) && (mas[6][0][0] == 4)) {
			r90count(4);
			r90count(6);
			r90cl(4);
		}
		else if (((mas[2][0][2] == 2) && (mas[3][0][0] == 1)) && (mas[6][2][2] == 3)) {
			r90cl(3);
			r90cl(6);
			r90count(3);
		}
		else if (((mas[2][0][0] == 1) && (mas[5][0][2] == 5)) && (mas[6][2][0] == 2)) {
			r90cl(2);
			r90cl(6);
			r90count(2);
		}
		else if (((mas[4][0][0] == 1) && (mas[3][0][2] == 3)) && (mas[6][0][2] == 4)) {
			r90cl(4);
			r90cl(6);
			r90count(4);
		}
		else if (((mas[5][0][0] == 1) && (mas[4][0][2] == 4)) && (mas[6][0][0] == 5)) {
			r90cl(5);
			r90cl(6);
			r90count(5);
		}
		else if (((mas[2][0][2] == 3) && (mas[3][0][0] == 2)) && (mas[6][2][2] == 1)) {
			r90cl(3);
			r90count(6);
			r90count(3);
			r180deg(6);
			r90cl(3);
			r90cl(6);
			r90count(3);
		}
		else if (((mas[2][0][0] == 5) && (mas[5][0][2] == 2)) && (mas[6][2][0] == 1)) {
			r90cl(2);
			r90count(6);
			r90count(2);
			r180deg(6);
			r90cl(2);
			r90cl(6);
			r90count(2);
		}
		else if (((mas[4][0][0] == 3) && (mas[3][0][2] == 4)) && (mas[6][0][2] == 1)) {
			r90cl(4);
			r90count(6);
			r90count(4);
			r180deg(6);
			r90cl(4);
			r90cl(6);
			r90count(4);
		}
		else if (((mas[5][0][0] == 4) && (mas[4][0][2] == 5)) && (mas[6][0][0] == 1)) {
			r90cl(5);
			r90count(6);
			r90count(5);
			r180deg(6);
			r90cl(5);
			r90cl(6);
			r90count(5);
		}
		else if (mas[2][2][2] == 1) {
			r90count(2);
			r90count(6);
			r90cl(2);
		}
		else if (mas[3][2][0] == 1) {
			r90count(2);
			r90count(6);
			r90cl(2);
		}
		else if (mas[5][2][2] == 1) {
			r90count(5);
			r90count(6);
			r90cl(5);
		}
		else if (mas[2][2][0] == 1) {
			r90count(5);
			r90count(6);
			r90cl(5);
		}
		else if (mas[3][2][2] == 1) {
			r90count(3);
			r90count(6);
			r90cl(3);
		}
		else if (mas[4][2][0] == 1) {
			r90count(3);
			r90count(6);
			r90cl(3);
		}
		else if (mas[4][2][2] == 1) {
			r90count(4);
			r90count(6);
			r90cl(4);
		}
		else if (mas[5][2][0] == 1) {
			r90count(4);
			r90count(6);
			r90cl(4);
		}
		else if (((mas[2][2][0] != 2) || (mas[5][2][2] != 5)) && (mas[1][0][0] == 1)) {
			r90cl(2);
			r90count(6);
			r90count(2);
		}
		else if (((mas[3][2][0] != 3) || (mas[2][2][2] != 2)) && (mas[1][0][2] == 1)) {
			r90cl(3);
			r90count(6);
			r90count(3);
		}
		else if (((mas[4][2][0] != 4) || (mas[3][2][2] != 3)) && (mas[1][2][2] == 1)) {
			r90cl(4);
			r90count(6);
			r90count(4);
		}
		else if (((mas[5][2][0] != 5) || (mas[4][2][2] != 4)) && (mas[1][2][0] == 1)) {
			r90cl(5);
			r90count(6);
			r90count(5);
		}
		else {
			r90count(6);
			k++;
			continue;
		}
		k = 0;
	}

}
void CubeRubic::step3() {
	int k = 0;
	while (k != 4) {
		int c = 0;
		while (c != 4) {
			if ((mas[2][0][1] == 2) && (mas[6][2][1] == 5)) {
				r90count(6);
				r90count(5);
				r90cl(6);
				r90cl(5);
				r90cl(6);
				r90cl(2);
				r90count(6);
				r90count(2);
			}
			else if ((mas[3][0][1] == 3) && (mas[6][1][2] == 2)) {
				r90count(6);
				r90count(2);
				r90cl(6);
				r90cl(2);
				r90cl(6);
				r90cl(3);
				r90count(6);
				r90count(3);
			}
			else if ((mas[4][0][1] == 4) && (mas[6][0][1] == 3)) {
				r90count(6);
				r90count(3);
				r90cl(6);
				r90cl(3);
				r90cl(6);
				r90cl(4);
				r90count(6);
				r90count(4);
			}
			else if ((mas[5][0][1] == 5) && (mas[6][1][0] == 4)) {
				r90count(6);
				r90count(4);
				r90cl(6);
				r90cl(4);
				r90cl(6);
				r90cl(5);
				r90count(6);
				r90count(5);
			}
			if ((mas[2][0][1] == 2) && (mas[6][2][1] == 3)) {
				r90cl(6);
				r90cl(3);
				r90count(6);
				r90count(3);
				r90count(6);
				r90count(2);
				r90cl(6);
				r90cl(2);
			}
			else if ((mas[3][0][1] == 3) && (mas[6][1][2] == 4)) {
				r90cl(6);
				r90cl(4);
				r90count(6);
				r90count(4);
				r90count(6);
				r90count(3);
				r90cl(6);
				r90cl(3);
			}
			else if ((mas[4][0][1] == 4) && (mas[6][0][1] == 5)) {
				r90cl(6);
				r90cl(5);
				r90count(6);
				r90count(5);
				r90count(6);
				r90count(4);
				r90cl(6);
				r90cl(4);
			}
			else if ((mas[5][0][1] == 5) && (mas[6][1][0] == 2)) {
				r90cl(6);
				r90cl(2);
				r90count(6);
				r90count(2);
				r90count(6);
				r90count(5);
				r90cl(6);
				r90cl(5);
			}
			else {
				r90cl(6);
				c++;
				continue;
			}
			c = 0;
		}
		if ((mas[2][1][2] != 2) || (mas[3][1][0] != 3)) {
			r90cl(6);
			r90cl(3);
			r90count(6);
			r90count(3);
			r90count(6);
			r90count(2);
			r90cl(6);
			r90cl(2);
		}
		else if ((mas[5][1][2] != 5) || (mas[2][1][0] != 2)) {
			r90cl(6);
			r90cl(2);
			r90count(6);
			r90count(2);
			r90count(6);
			r90count(5);
			r90cl(6);
			r90cl(5);
		}
		else if ((mas[4][1][2] != 4) || (mas[5][1][0] != 5)) {
			r90cl(6);
			r90cl(5);
			r90count(6);
			r90count(5);
			r90count(6);
			r90count(4);
			r90cl(6);
			r90cl(4);
		}
		else if ((mas[3][1][2] != 3) || (mas[4][1][0] != 4)) {
			r90cl(6);
			r90cl(4);
			r90count(6);
			r90count(4);
			r90count(6);
			r90count(3);
			r90cl(6);
			r90cl(3);
		}
		else {
			r90count(6);
			k++;
			continue;
		}
		k = 0;
	}
}
void CubeRubic::step4() {
	if ((mas[2][0][1] == 6) && (mas[3][0][1] == 6)) {
		r90cl(2);
		r90cl(6);
		r90cl(3);
		r90count(6);
		r90count(3);
		r90count(2);
	}
	else if ((mas[2][0][1] == 6) && (mas[5][0][1] == 6)) {
		r90cl(5);
		r90cl(6);
		r90cl(2);
		r90count(6);
		r90count(2);
		r90count(5);
	}
	else if ((mas[3][0][1] == 6) && (mas[4][0][1] == 6)) {
		r90cl(3);
		r90cl(6);
		r90cl(4);
		r90count(6);
		r90count(4);
		r90count(3);
	}
	else if ((mas[4][0][1] == 6) && (mas[5][0][1] == 6)) {
		r90cl(4);
		r90cl(6);
		r90cl(5);
		r90count(6);
		r90count(5);
		r90count(4);
	}
	else if ((mas[2][0][1] == 6) && (mas[4][0][1] == 6)) {
		r90cl(2);
		r90cl(3);
		r90cl(6);
		r90count(3);
		r90count(6);
		r90count(2);
	}
	else if ((mas[3][0][1] == 6) && (mas[5][0][1] == 6)) {
		r90cl(3);
		r90cl(4);
		r90cl(6);
		r90count(4);
		r90count(6);
		r90count(3);
	}
	else if (((mas[2][0][1] == 6) && (mas[4][0][1] == 6)) && ((mas[3][0][1] == 6) && (mas[5][0][1] == 6))) {
		r90cl(2);
		r90cl(6);
		r90cl(3);
		r90count(6);
		r90count(3);
		r90count(2);
		r90cl(3);
		r90cl(4);
		r90cl(6);
		r90count(4);
		r90count(6);
		r90count(3);
	}

}
void CubeRubic::step5() {
	if (mas[3][0][1] == 2) {
		r90cl(6);
		r90count(5);
		r180deg(6);
		r90cl(5);
		r90cl(6);
		r90count(5);
		r90cl(6);
		r90cl(5);
	}
	else if (mas[5][0][1] == 2) {
		r90cl(6);
		r90count(4);
		r180deg(6);
		r90cl(4);
		r90cl(6);
		r90count(4);
		r90cl(6);
		r90cl(4);
	}
	else if (mas[4][0][1] == 2) {
		r90cl(6);
		r90count(3);
		r180deg(6);
		r90cl(3);
		r90cl(6);
		r90count(3);
		r90cl(6);
		r90cl(3);
		r90cl(6);
		r90count(4);
		r180deg(6);
		r90cl(4);
		r90cl(6);
		r90count(4);
		r90cl(6);
		r90cl(4);
		r90cl(6);
		r90count(3);
		r180deg(6);
		r90cl(3);
		r90cl(6);
		r90count(3);
		r90cl(6);
		r90cl(3);
	}
	if (mas[4][0][1] == 3) {
		r90cl(6);
		r90count(2);
		r180deg(6);
		r90cl(2);
		r90cl(6);
		r90count(2);
		r90cl(6);
		r90cl(2);
	}
	else if (mas[5][0][1] == 3) {
		r90cl(6);
		r90count(4);
		r180deg(6);
		r90cl(4);
		r90cl(6);
		r90count(4);
		r90cl(6);
		r90cl(4);
		r90cl(6);
		r90count(5);
		r180deg(6);
		r90cl(5);
		r90cl(6);
		r90count(5);
		r90cl(6);
		r90cl(5);
		r90cl(6);
		r90count(4);
		r180deg(6);
		r90cl(4);
		r90cl(6);
		r90count(4);
		r90cl(6);
		r90cl(4);
	}
	if (mas[5][0][1] == 4) {
		r90cl(6);
		r90count(3);
		r180deg(6);
		r90cl(3);
		r90cl(6);
		r90count(3);
		r90cl(6);
		r90cl(3);
	}

}
void CubeRubic::step6() {
	std::set <int> S;
	S.insert(2);
	S.insert(3);
	S.insert(6);
	if ((S.count(mas[2][0][0]) && S.count(mas[5][0][2])) && S.count(mas[6][2][0])) {
		r90count(2);
		r90count(5);
		r90cl(2);
		r90count(3);
		r90count(2);
		r90cl(5);
		r90cl(2);
		r90cl(3);
	}
	else if ((S.count(mas[4][0][0]) && S.count(mas[3][0][2])) && S.count(mas[6][0][2])) {
		r90count(3);
		r90count(2);
		r90count(5);
		r90cl(2);
		r90cl(3);
		r90count(2);
		r90cl(5);
		r90cl(2);
	}
	else if ((S.count(mas[5][0][0]) && S.count(mas[4][0][2])) && S.count(mas[6][0][0])) {
		r90count(2);
		r90count(5);
		r90count(4);
		r90cl(5);
		r90cl(2);
		r90count(5);
		r90cl(4);
		r90cl(5);
	}
	S.clear();
	S.insert(4);
	S.insert(3);
	S.insert(6);
	if ((S.count(mas[2][0][0]) && S.count(mas[5][0][2])) && S.count(mas[6][2][0])) {
		r90count(4);
		r90count(3);
		r90cl(4);
		r90count(5);
		r90count(4);
		r90cl(3);
		r90cl(4);
		r90cl(5);
	}
	else if ((S.count(mas[5][0][0]) && S.count(mas[4][0][2])) && S.count(mas[6][0][0])) {
		r90count(5);
		r90count(4);
		r90count(3);
		r90cl(4);
		r90cl(5);
		r90count(4);
		r90cl(3);
		r90cl(4);
	}
	S.clear();
}
void CubeRubic::step7() {
	for (int i = 0; i < 4; i++) {
		if (mas[3][0][0] == 6) {
			r90count( 2);
			r90cl(3);
			r90cl( 2);
			r90count(3);
			r90count(2);
			r90cl(3);
			r90cl(2);
			r90count(3);
		}
		else if (mas[2][0][2] == 6) {
			r90cl(3);
			r90count(2);
			r90count(3);
			r90cl(2);
			r90cl(3);
			r90count(2);
			r90count(3);
			r90cl(2);
		}
		r90cl(6);
	}
}
void CubeRubic::solve() {
	step1();
	step2();
	step3();
	step4();
	step5();
	step6();
	step7();
}
