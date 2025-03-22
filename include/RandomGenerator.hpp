#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>
#include <chrono>

class RandomGenerator {
    // We use a static function returning a reference to a static engine
    static std::mt19937& getEngine();

public:
    static int getRandomInt(int min, int max);
    static double getRandomDouble(double min, double max);
};

#endif
