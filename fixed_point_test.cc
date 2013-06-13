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

// File under test.
#include "fixed_point.h"

#include "gtest/gtest.h"

TEST(FixedPointTest, ConstructionWithValidParams) {
  FixedPoint<4,11> fixed_point_a;
  FixedPoint<15,0> fixed_point_b;
}

TEST(FixedPointTest, ConvertToAndFromIntegers) {
  typedef FixedPoint<4, 11> Fixed;
  // Testing mid-range.
  ASSERT_EQ(9,  Fixed(9).ToInt());
  // Testing bottom end.
  ASSERT_EQ(-16,  Fixed(-16).ToInt());
  // Testing top end.
  ASSERT_EQ(15,  Fixed(15).ToInt());
  // Testing out of range.
  ASSERT_NE(-17,  Fixed(17).ToInt());
  // Testing out of range.
  ASSERT_NE(16,  Fixed(16).ToInt());
}

TEST(FixedPointTest, ConvertToAndFromFloats) {
  typedef FixedPoint<4, 11> Fixed;
  ASSERT_FLOAT_EQ(9.0f, Fixed(9.0f).ToFloat());
  ASSERT_FLOAT_EQ(0.25f, Fixed(0.25f).ToFloat());
  ASSERT_NEAR(-5.2884, Fixed(-5.2884f).ToFloat(), 1.0f / (1 << 11));
}

TEST(FixedPointTest, ConvertFromFloatToInt) {
  typedef FixedPoint<4, 11> Fixed;
  ASSERT_EQ(-6, Fixed(-5.2884f).ToInt());
}

TEST(FixedPointTest, Addition) {
  typedef FixedPoint<4, 11> Fixed;
  Fixed a(2.433f);
  Fixed b(0.222f);
  ASSERT_NEAR(2.655, (a + b).ToFloat(), 2.0f / (1 << 11));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
