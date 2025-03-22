#include "RandomGenerator.hpp"

std::mt19937& RandomGenerator::getEngine() {
    static std::mt19937 engine(
        static_cast<unsigned>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        )
    );
    return engine;
}

int RandomGenerator::getRandomInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(getEngine());
}

double RandomGenerator::getRandomDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(getEngine());
}
