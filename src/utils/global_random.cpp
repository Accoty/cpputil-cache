#include "utils/global_random.h"
#include <random>

namespace cpputil {

namespace common {

uint64_t GlobalRand() {
    static thread_local std::mt19937 gen(std::random_device{}());
    return gen();
}

} // common
} // cpputil