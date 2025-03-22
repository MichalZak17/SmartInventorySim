#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

namespace Utils {

    // A template function to print container elements
    template<typename Container>
    void printContainer(const Container& c, const std::string& prefix = "") {
        std::cout << prefix;
        std::for_each(c.begin(), c.end(), [](auto& elem) {
            std::cout << elem << " ";
        });
        std::cout << std::endl;
    }

    // A template function to copy from one container to an output iterator
    template<typename InputContainer, typename OutputIterator>
    void copyElements(const InputContainer& input, OutputIterator out) {
        std::copy(input.begin(), input.end(), out);
    }

}

#endif
