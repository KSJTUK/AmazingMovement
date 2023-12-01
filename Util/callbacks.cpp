#include "pch.h"
#include "Util/callbacks.h"
#include "Util/Engine.h"

// 그리기 콜백함수
void renderFunc()
{
	// rendering function
	engine->Render();
}

void reshapeFunc(int x, int y)
{
	engine->ReSizeWindow(x, y);
}

void idleFunc()
{
	// Frame객체의 Update함수 사용
	engine->Update();
	glutPostRedisplay();
}


void keyboardFunc(unsigned char key, int x, int y)
{
	engine->Input(key, true);
}

void keyboardUpFunc(unsigned char key, int x, int y)
{
}

void specialkeyFunc(int key, int x, int y)
{
	engine->SpecialInput(key, true);
}

void specialKeyUpFunc(int key, int x, int y)
{

}

void mouseFunc(int button, int state, int x, int y)
{

}

void mouseLeftDown(int state, int x, int y)
{
}

void mouseRightDown(int state, int x, int y)
{
}

void mouseMotion(int x, int y)
{
	engine->MouseMotionInput(x, y);
}

void mousePassiveMotion(int x, int y)
{
	//engine->MousePassiveMotionInpit(x, y);
}

void mouseWheel(int dir, int x, int y)
{
}
