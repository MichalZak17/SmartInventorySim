#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>
#include <chrono>

/**
 * @brief RandomGenerator class for generating random numbers
 * 
 * The RandomGenerator class provides static methods to generate random integers
 * and doubles within specified ranges. It uses a static method to return a reference
 * to a static random number engine.
 */
class RandomGenerator {
    /**
     * @brief Returns a reference to a static random number engine
     * 
     * This method initializes a static random number engine using the current time
     * as the seed and returns a reference to it. The engine is used for generating
     * random numbers.
     * 
     * @return A reference to a static std::mt19937 random number engine
     */
    static std::mt19937& getEngine();

public:
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
    static int getRandomInt(int min, int max);

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
    static double getRandomDouble(double min, double max);
};

#endif
