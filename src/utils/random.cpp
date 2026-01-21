#include "utils/random.h"
#include <ctime>
#include <cstdlib>

void Random::Init() {
    srand((unsigned int)time(nullptr));
}

int Random::GetRandomInt(int x, int y) {
    return x + rand() % (y - x + 1);
}

float Random::GetRandomFloat(float x, float y) {
    return x + (y - x) * (rand() / (RAND_MAX + 1.0f));
}
