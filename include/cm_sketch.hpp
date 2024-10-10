#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>

#include "utils/global_radom.h"

namespace cpputil {

namespace cache {

namespace utils {

// T must support ^ and &, such as int
template <typename T, int Shard = 2, typename Allocator = std::allocator<uint8_t>>
class CMSketch4Bits {
  public:
    explicit CMSketch4Bits(size_t capacity_bit): capacity_(1 << capacity_bit) {
        capacity_mask_ = capacity_ - 1;
        for (auto& data_ptr : data_) {
            data_ptr = allocator_.allocate(capacity_ >> 1);
            memset(data_ptr, 0, sizeof data_ptr);
        }
        for (auto& seed : seed_) {
            seed = cpputil::common::global_rand();
        }
    }
    ~CMSketch4Bits() {
        for (auto data_ptr : data_) {
            allocator_.deallocate(data_ptr, capacity_ >> 1);
        }
    }
    void Increment(const T& item) {
        for (int i = 0; i < Shard; i++) {
            auto index = (item ^ seed_[i]) & capacity_mask_;
            auto offset = (index & 1) << 2;
            if ((data_[i][index >> 1] >> offset) < 15) {
                data_[i][index >> 1] += 1 << offset;
            }
        }
    }
    unsigned int Estimate(const T& item) {
        int res = 15;
        for (int i = 0; i < Shard; i++) {
            auto index = (item ^ seed_[i]) & capacity_mask_;
            res = std::min(res, data_[i][index >> 1] >> ((index & 1) << 2));
        }
        return res;
    }
    void reset() {
        for (auto data_ptr : data_) {
            for (auto& x : data_ptr) {
                x = (x >> 1) & 0x77;
            }
        }
    }
  private:
    uint8_t* data_[Shard];
    unsigned int seed_[Shard];
    size_t capacity_;
    size_t capacity_mask_;
    Allocator allocator_;
};

} // utils
} // cache 
} // cpputil