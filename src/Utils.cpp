#include "Utils.hpp"

/**
 * @namespace Utils
 * @brief A namespace containing utility functions for various operations.
 * 
 * The Utils namespace provides a collection of utility functions that can be
 * used for common operations such as printing container elements and copying
 * elements from one container to another.
 */
namespace Utils {

    /**
     * @brief Prints the elements of a container.
     * 
     * This template function prints the elements of a given container to the
     * standard output stream. An optional prefix can be provided to be printed
     * before the container elements.
     * 
     * @tparam Container The type of the container.
     * @param c The container whose elements are to be printed.
     * @param prefix An optional prefix to be printed before the container elements.
     */
    template<typename Container>
    void printContainer(const Container& c, const std::string& prefix = "") {
        std::cout << prefix;
        std::for_each(c.begin(), c.end(), [](auto& elem) {
            std::cout << elem << " ";
        });
        std::cout << std::endl;
    }

    /**
     * @brief Copies elements from one container to an output iterator.
     * 
     * This template function copies the elements from an input container to an
     * output iterator. The output iterator can be used to insert the elements
     * into another container or to perform other operations.
     * 
     * @tparam InputContainer The type of the input container.
     * @tparam OutputIterator The type of the output iterator.
     * @param input The input container whose elements are to be copied.
     * @param out The output iterator to which the elements are to be copied.
     */
    template<typename InputContainer, typename OutputIterator>
    void copyElements(const InputContainer& input, OutputIterator out) {
        std::copy(input.begin(), input.end(), out);
    }

}
