#include "utils/global_radom.h"
#include <random>

namespace cpputil {

namespace common {

static unsigned int global_rand() {
    thread_local std::mt19937 gen(std::random_device{}());
    return gen();
}

} // common
} // cpputil