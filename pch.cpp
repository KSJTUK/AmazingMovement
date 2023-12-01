#include "pch.h"
#include "Util/Engine.h"

std::unique_ptr<Engine> engine = std::make_unique<Engine>();

float constants::gravity = 9.8f;
float constants::epsilon = glm::epsilon<float>();