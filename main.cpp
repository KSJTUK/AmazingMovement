#include "pch.h"
#include "Util/Engine.h"

int main(int argc, char* argv[])
{
	engine->Init(&argc, argv);
	engine->Loop();
}