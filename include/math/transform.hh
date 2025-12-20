#pragma once

#include <math/matrix.hh>
#include <math/vector.hh>

#include <GL/glew.h>

Matrix4 matrix_translate_by(const Vector3 &direction);
Matrix4 matrix_rotate_around_x_by(double rad_angle);
Matrix4 matrix_rotate_around_y_by(double rad_angle);
Matrix4 matrix_rotate_around_z_by(double rad_angle);

Matrix4 matrix_look_at(const Vector3 &forward, const Vector3 &up);

Matrix4 matrix_look_at(const Vector3 &eye, const Vector3 &focus_point,
                       const Vector3 &up);

Matrix4 matrix_look_at(const GLfloat &eyeX, const GLfloat &eyeY,
                       const GLfloat &eyeZ, const GLfloat &centerX,
                       const GLfloat &centerY, const GLfloat &centerZ,
                       const GLfloat &upX, const GLfloat &upY,
                       const GLfloat &upZ);

Matrix4 matrix_frustum(const GLfloat &left, const GLfloat &right,
                       const GLfloat &bottom, const GLfloat &top,
                       const GLfloat &near, const GLfloat &far);

Matrix4 matrix_orthographic_projection(const GLfloat &left,
                                       const GLfloat &right,
                                       const GLfloat &bottom,
                                       const GLfloat &top, const GLfloat &near,
                                       const GLfloat &far);

double angle_degrees_to_radians(double degree_angle);
