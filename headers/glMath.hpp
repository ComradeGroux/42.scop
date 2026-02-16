#pragma once

#include <cmath>
#include <cstring>

typedef float mat4[16];

struct vec3 {
    float x, y, z;
    
    vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

inline float vec3_length(const vec3& v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline void vec3_normalize(vec3* v) {
    float len = vec3_length(*v);
    if (len > 0.0f) {
        v->x /= len;
        v->y /= len;
        v->z /= len;
    }
}

inline vec3 vec3_cross(const vec3& a, const vec3& b) {
    vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

inline float vec3_dot(const vec3& a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 vec3_subtract(const vec3& a, const vec3& b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}





inline void mat4_identity(mat4 m) {
    m[0] = 1.0f; m[4] = 0.0f; m[8]  = 0.0f; m[12] = 0.0f;
    m[1] = 0.0f; m[5] = 1.0f; m[9]  = 0.0f; m[13] = 0.0f;
    m[2] = 0.0f; m[6] = 0.0f; m[10] = 1.0f; m[14] = 0.0f;
    m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f; m[15] = 1.0f;
}

inline void mat4_copy(mat4 dest, const mat4 src) {
    memcpy(dest, src, sizeof(mat4));
}

inline void mat4_multiply(mat4 result, const mat4 a, const mat4 b) {
    mat4 temp;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i + j * 4] = 0.0f;
            for (int k = 0; k < 4; k++) {
                temp[i + j * 4] += a[i + k * 4] * b[k + j * 4];
            }
        }
    }
    memcpy(result, temp, sizeof(mat4));
}


inline void mat4_translate(mat4 m, float x, float y, float z) {
    mat4_identity(m);
    m[12] = x;
    m[13] = y;
    m[14] = z;
}

inline void mat4_rotate_x(mat4 m, float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    
    mat4_identity(m);
    m[5] = c;   m[9] = -s;
    m[6] = s;   m[10] = c;
}

inline void mat4_rotate_y(mat4 m, float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    
    mat4_identity(m);
    m[0] = c;   m[8] = s;
    m[2] = -s;  m[10] = c;
}

inline void mat4_rotate_z(mat4 m, float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    
    mat4_identity(m);
    m[0] = c;   m[4] = -s;
    m[1] = s;   m[5] = c;
}

inline void mat4_rotate(mat4 m, float angle, float x, float y, float z) {
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - c;
    
    float len = sqrtf(x * x + y * y + z * z);
    x /= len;
    y /= len;
    z /= len;
    
    mat4_identity(m);
    m[0] = t * x * x + c;
    m[1] = t * x * y + s * z;
    m[2] = t * x * z - s * y;
    
    m[4] = t * x * y - s * z;
    m[5] = t * y * y + c;
    m[6] = t * y * z + s * x;
    
    m[8] = t * x * z + s * y;
    m[9] = t * y * z - s * x;
    m[10] = t * z * z + c;
}

inline void mat4_scale(mat4 m, float x, float y, float z) {
    mat4_identity(m);
    m[0] = x;
    m[5] = y;
    m[10] = z;
}



inline void mat4_look_at(mat4 m, const vec3& eye, const vec3& center, const vec3& up) {
    vec3 f = vec3_subtract(center, eye);
    vec3_normalize(&f);
    
    vec3 s = vec3_cross(f, up);
    vec3_normalize(&s);
    
    vec3 u = vec3_cross(s, f);
    
    mat4_identity(m);
    m[0] = s.x;
    m[4] = s.y;
    m[8] = s.z;
    
    m[1] = u.x;
    m[5] = u.y;
    m[9] = u.z;
    
    m[2] = -f.x;
    m[6] = -f.y;
    m[10] = -f.z;
    
    m[12] = -vec3_dot(s, eye);
    m[13] = -vec3_dot(u, eye);
    m[14] = vec3_dot(f, eye);
}


inline void mat4_perspective(mat4 m, float fov, float aspect, float near, float far) {
    float tanHalfFov = tanf(fov / 2.0f);
    
    memset(m, 0, sizeof(mat4));
    m[0] = 1.0f / (aspect * tanHalfFov);
    m[5] = 1.0f / tanHalfFov;
    m[10] = -(far + near) / (far - near);
    m[11] = -1.0f;
    m[14] = -(2.0f * far * near) / (far - near);
}


inline void mat4_ortho(mat4 m, float left, float right, float bottom, float top, float near, float far) {
    mat4_identity(m);
    m[0] = 2.0f / (right - left);
    m[5] = 2.0f / (top - bottom);
    m[10] = -2.0f / (far - near);
    m[12] = -(right + left) / (right - left);
    m[13] = -(top + bottom) / (top - bottom);
    m[14] = -(far + near) / (far - near);
}

inline float deg_to_radians(float degrees) {
    return degrees * 3.14159265358979323846f / 180.0f;
}

inline float rad_to_degrees(float radians) {
    return radians * 180.0f / 3.14159265358979323846f;
}

