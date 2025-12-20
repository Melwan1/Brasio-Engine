#include <math/libmath.hh>

Matrix4 matrix_translate_by(const Vector3 &direction)
{
    return { { 1, 0, 0, direction[0] },
             { 0, 1, 0, direction[1] },
             { 0, 0, 1, direction[2] },
             { 0, 0, 0, 1 } };
}

Matrix4 matrix_rotate_around_x_by(double rad_angle)
{
    float c = std::cos(rad_angle);
    float s = std::sin(rad_angle);
    return { { 1, 0, 0, 0 }, { 0, c, s, 0 }, { 0, -s, c, 0 }, { 0, 0, 0, 1 } };
}

Matrix4 matrix_rotate_around_y_by(double rad_angle)
{
    float c = std::cos(rad_angle);
    float s = std::sin(rad_angle);
    return { { c, 0, s, 0 }, { 0, 1, 0, 0 }, { -s, 0, c, 0 }, { 0, 0, 0, 1 } };
}

Matrix4 matrix_rotate_around_z_by(double rad_angle)
{
    float c = std::cos(rad_angle);
    float s = std::sin(rad_angle);
    return { { c, s, 0, 0 }, { -s, c, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
}

Matrix4 matrix_look_at(const Vector3 &forward, const Vector3 &up)
{
    const Vector3 &f = forward.normalize();
    const Vector3 &s = f.cross_product(up).normalize();
    const Vector3 &u = s.cross_product(f); // already normalized
    Matrix4 R = { { s[0], s[1], s[2], 0 },
                  { u[0], u[1], u[2], 0 },
                  { f[0], f[1], f[2], 0 },
                  { 0, 0, 0, 1 } };
    return R;
}

Matrix4 matrix_look_at(const Vector3 &eye, const Vector3 &focus_point,
                       const Vector3 &up)
{
    (void)up;
    (void)focus_point;
    Vector3 f = (eye - focus_point).normalize();
    Vector3 s = f.cross_product(up).normalize();
    Vector3 u = s.cross_product(f);

    Matrix4 R = { { s[0], s[1], s[2], 0 },
                  { u[0], u[1], u[2], 0 },
                  { f[0], f[1], f[2], 0 },
                  { 0, 0, 0, 1 } };
    Matrix4 T = matrix_translate_by(Vector3{ -eye[0], -eye[1], -eye[2] });

    return T * R;
}

Matrix4 matrix_look_at(const GLfloat &eyeX, const GLfloat &eyeY,
                       const GLfloat &eyeZ, const GLfloat &centerX,
                       const GLfloat &centerY, const GLfloat &centerZ,
                       const GLfloat &upX, const GLfloat &upY,
                       const GLfloat &upZ)
{
    const Vector3 &eye = { eyeX, eyeY, eyeZ };
    const Vector3 &center = { centerX, centerY, centerZ };
    const Vector3 &up = { upX, upY, upZ };
    return matrix_look_at(eye, center, up);
}

Matrix4 matrix_frustum(const GLfloat &left, const GLfloat &right,
                       const GLfloat &bottom, const GLfloat &top,
                       const GLfloat &near, const GLfloat &far)
{
    GLfloat A = (right + left) / (right - left);
    GLfloat B = (top + bottom) / (top - bottom);
    GLfloat C = (near + far) / (near - far);
    GLfloat D = (2 * near * far) / (near - far);

    GLfloat I1 = (2 * near) / (right - left);
    GLfloat I2 = (2 * near) / (top - bottom);

    return {
        { I1, 0, A, 0 }, { 0, I2, B, 0 }, { 0, 0, C, D }, { 0, 0, -1, 0 }
    };
}

Matrix4 matrix_orthographic_projection(const GLfloat &left,
                                       const GLfloat &right,
                                       const GLfloat &bottom,
                                       const GLfloat &top, const GLfloat &near,
                                       const GLfloat &far)
{
    GLfloat tx = -(right + left) / (right - left);
    GLfloat ty = -(top + bottom) / (top - bottom);
    GLfloat tz = -(far + near) / (far - near);

    GLfloat I1 = 2 / (right - left);
    GLfloat I2 = 2 / (top - bottom);
    GLfloat I3 = -2 / (far - near);

    return {
        { I1, 0, 0, tx }, { 0, I2, 0, ty }, { 0, 0, I3, tz }, { 0, 0, 0, 1 }
    };
}

double angle_degrees_to_radians(const double degree_angle)
{
    return degree_angle * std::numbers::pi / 180.0f;
}
