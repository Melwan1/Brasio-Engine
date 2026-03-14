#include <gtest/gtest.h>

#include <math/vector.hh>

TEST(Math_Vector_Constructor_Array, 2d)
{
    constexpr unsigned size = 2;
    int array[size] = { 1, 2 };
    const brasio::math::IntVector2 vec(array);
    for (unsigned index = 0; index < size; index++)
    {
        EXPECT_EQ(vec[index], array[index]);
    }
}

TEST(Math_Vector_Constructor_Array, 3d)
{
    constexpr unsigned size = 3;
    int array[size] = { 2, 4, 6 };
    const brasio::math::IntVector3 vec(array);
    for (unsigned index = 0; index < size; index++)
    {
        EXPECT_EQ(vec[index], array[index]);
    }
}

TEST(Math_Vector_Constructor_Array, 4d)
{
    constexpr unsigned size = 4;
    int array[size] = { 0, 1, 2, 3 };
    const brasio::math::IntVector4 vec(array);
    for (unsigned index = 0; index < size; index++)
    {
        EXPECT_EQ(vec[index], array[index]);
    }
}

TEST(Math_Vector_Constructor_Resize, 2to3)
{
    const brasio::math::IntVector2 vec2({ 1, 4 });
    const brasio::math::IntVector3 vec3(vec2);
    for (unsigned index = 0; index < 2; index++)
    {
        EXPECT_EQ(vec3[index], vec2[index]);
    }
    EXPECT_EQ(vec3[2], 1);
}

TEST(Math_Vector_Constructor_Resize, 3to4)
{
    const brasio::math::IntVector3 vec3({ -2, -5, -8 });
    const brasio::math::IntVector4 vec4(vec3);
    for (unsigned index = 0; index < 3; index++)
    {
        EXPECT_EQ(vec4[index], vec3[index]);
    }
    EXPECT_EQ(vec4[3], 1);
}

TEST(Math_Vector_Constructor_Resize, 2to4)
{
    const brasio::math::IntVector2 vec2({ 4, 3 });
    const brasio::math::IntVector3 vec3(vec2);
    const brasio::math::IntVector4 vec4(vec3);
    for (unsigned index = 0; index < 2; index++)
    {
        EXPECT_EQ(vec4[index], vec2[index]);
    }
    EXPECT_EQ(vec4[2], 1);
    EXPECT_EQ(vec4[3], 1);
}

TEST(Math_Vector_Constructor_Resize, 3to2)
{
    const brasio::math::IntVector3 vec3({ 3, 2, 1 });
    const brasio::math::IntVector2 vec2(vec3);
    for (unsigned index = 0; index < 2; index++)
    {
        EXPECT_EQ(vec2[index], vec3[index]);
    }
}

TEST(Math_Vector_Constructor_Resize, 4to3)
{
    const brasio::math::IntVector4 vec4({ 4, 3, 2, 1 });
    const brasio::math::IntVector3 vec3(vec4);
    for (unsigned index = 0; index < 3; index++)
    {
        EXPECT_EQ(vec3[index], vec4[index]);
    }
}

TEST(Math_Vector_Constructor_Resize, 4to2)
{
    const brasio::math::IntVector4 vec4({ 4, 3, 2, 1 });
    const brasio::math::IntVector3 vec3(vec4);
    const brasio::math::IntVector2 vec2(vec3);
    for (unsigned index = 0; index < 2; index++)
    {
        EXPECT_EQ(vec2[index], vec4[index]);
    }
}
