#include "Cache.hpp"
#include <iostream>

int main () {
    cpputil::cache::Cache a("hahaha");
    std::cout << a.name() << std::endl;
}