#pragma once
#include <Arduino.h>

#define N(a) (sizeof(a) / sizeof((a)[0]))

class prng {
  private:
    char seed_[32];

  public:
    prng();

    const char* seed() const;
};

class xmur3 {
private:
    uint32_t h_;

public:
    explicit xmur3(const char* s)
        : h_(1779033703u ^ static_cast<uint32_t>(strlen(s)))
    {
        for (const char* p = s; *p; ++p) {
            h_ = (h_ ^ static_cast<uint8_t>(*p)) * 3432918353u;
            h_ = (h_ << 13) | (h_ >> 19);
        }
    }

    uint32_t operator()() {
        h_ = (h_ ^ (h_ >> 16)) * 2246822507u;
        h_ = (h_ ^ (h_ >> 13)) * 3266489909u;
        h_ ^= h_ >> 16;
        return h_;
    }
};

class Mulberry32 {
private:
    uint32_t seed_;

public:
    explicit Mulberry32(uint32_t seed) : seed_(seed) {}

    double operator()() {
        return next_u32() / 4294967296.0;
    }

    uint32_t next_u32() {
        uint32_t t = (seed_ += 0x6D2B79F5u);
        t = (t ^ (t >> 15)) * (t | 1u);
        t ^= t + (t ^ (t >> 7)) * (t | 61u);
        return t ^ (t >> 14);
    }

    uint32_t rand_int(uint32_t maxExclusive) {
        return static_cast<uint32_t>(
            (static_cast<uint64_t>(next_u32()) * maxExclusive) >> 32);
    }
};

inline const char* pick(Mulberry32& rng, const char* base, size_t rowSize, size_t rowCount) {
    uint32_t idx = rng.rand_int(static_cast<uint32_t>(rowCount));
    return base + idx * rowSize;
}


