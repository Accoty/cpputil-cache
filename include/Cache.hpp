#pragma once

#include <cstddef>
#include <string>
namespace cpputil {

namespace cache {

class Cache {
  public:
    template <typename T>
    Cache(T&& name) {
        name_ = std::forward<T>(name);
    }
    const std::string& name() {
        return name_;
    }
  protected:
    size_t size_;
    std::string name_;
};

class WTinyWindowCache : public Cache {

};

} // cache

} // cpputil