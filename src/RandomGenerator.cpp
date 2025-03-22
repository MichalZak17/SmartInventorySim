#include "RandomGenerator.hpp"

/**
 * @brief Returns a reference to a static random number engine
 * 
 * This method initializes a static random number engine using the current time
 * as the seed and returns a reference to it. The engine is used for generating
 * random numbers.
 * 
 * @return A reference to a static std::mt19937 random number engine
 */
std::mt19937& RandomGenerator::getEngine() {
    static std::mt19937 engine(
        static_cast<unsigned>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        )
    );
    return engine;
}

/**
 * @brief Generates a random integer within a specified range
 * 
 * This method generates a random integer between the specified minimum and
 * maximum values (inclusive) using a uniform integer distribution.
 * 
 * @param min The minimum value of the range
 * @param max The maximum value of the range
 * @return A random integer between min and max (inclusive)
 */
int RandomGenerator::getRandomInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(getEngine());
}

/**
 * @brief Generates a random double within a specified range
 * 
 * This method generates a random double between the specified minimum and
 * maximum values (inclusive) using a uniform real distribution.
 * 
 * @param min The minimum value of the range
 * @param max The maximum value of the range
 * @return A random double between min and max (inclusive)
 */
double RandomGenerator::getRandomDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(getEngine());
}
