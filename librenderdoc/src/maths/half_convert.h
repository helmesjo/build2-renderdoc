#pragma once

#include <stdint.h>
#include <string.h>
#include <type_traits>

#include <half.hpp>

// Conversions between float and the bits of an IEEE 754 binary16, rounding
// to nearest even, by way of libhalf's half_float::half. Its bits are copied
// directly, which is valid for a trivially copyable type.

static_assert(std::is_trivially_copyable<half_float::half>::value &&
                  sizeof(half_float::half) == sizeof(uint16_t),
              "half_float::half must be a trivially copyable 16-bit type");

inline uint16_t ConvertToHalf(float comp)
{
  half_float::half h(comp);

  uint16_t ret;
  memcpy(&ret, &h, sizeof(ret));
  return ret;
}

inline float ConvertFromHalf(uint16_t comp)
{
  half_float::half h;
  memcpy(static_cast<void *>(&h), &comp, sizeof(comp));
  return (float)h;
}
