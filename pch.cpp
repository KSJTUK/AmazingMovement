#include "pch.h"
#include "Util/Engine.h"
#include "Util/RandomEngine.h"

std::unique_ptr<Engine> engine = std::make_unique<Engine>();
std::unique_ptr<RandomEngine> randomEngine = std::make_unique<RandomEngine>();

float constants::gravity = 9.8f;
float constants::epsilon = glm::epsilon<float>();