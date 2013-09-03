// Copyright (c) 2013, Sancho McCann

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:

// - Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef FIXED_POINT_H_
#define FIXED_POINT_H_

#include <cstdint>

template<int A>
struct BitsToDataType {
};

// Defining the data types to hold 32, 16, or 8 bit signed fixed point
// representations.
template<>
struct BitsToDataType<32> {
  typedef std::int32_t DataType;
};

template<>
struct BitsToDataType<16> {
  typedef std::int16_t DataType;
};

template<>
struct BitsToDataType<8> {
  typedef std::int8_t DataType;
};

// A+B+1 must equal 8, 16, or 32. A is the number of bits to the left
// of the decimal. B is the number of bits to the right of the
// decimal.
template<int A, int B>
struct FixedPoint {
  typedef typename BitsToDataType<A + B + 1>::DataType FixedPointType;

  FixedPoint() : fixed_point_value(0) {}
  FixedPoint(float a) :
      fixed_point_value(static_cast<FixedPointType>(a * (1 << B))) {}
  FixedPoint(int a) : fixed_point_value(a << B) {}

  void FromInt(int a) {
    fixed_point_value = (a << B);
  }

  int ToInt() const {
    return fixed_point_value >> B;
  }

  // TODO(sanchom): Handle rounding errors.
  void FromFloat(float a) {
    fixed_point_value = static_cast<FixedPointType>(a * (1 << B));
  }

  float ToFloat() const {
    return static_cast<float>(fixed_point_value) / (1 << B);
  }

  // TODO(sanchom: Handle overflow conditions.
  FixedPoint<A, B> operator+(const FixedPoint<A, B>& other) const {
    FixedPoint<A, B> result;
    result.fixed_point_value = fixed_point_value + other.fixed_point_value;
    return result;
  }

  FixedPointType fixed_point_value;
};

namespace std {

template<int A, int B>
FixedPoint<A, B> max(const FixedPoint<A, B>& a,
                     const FixedPoint<A, B>& b) {
  if (a.fixed_point_value > b.fixed_point_value) {
    return a;
  } else {
    return b;
  }
}

template<int A, int B>
FixedPoint<A, B> min(const FixedPoint<A, B>& a,
                     const FixedPoint<A, B>& b) {
  if (a.fixed_point_value < b.fixed_point_value) {
    return a;
  } else {
    return b;
  }
}

}

#endif  // FIXED_POINT_H_
