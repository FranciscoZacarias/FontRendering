#ifndef FZ_MATH_H
#define FZ_MATH_H

#define PI 3.14159265358979323846f
#define EPSILON 0.000001f

#define Degrees(r) (r * (180 / PI))
#define Radians(d) (d * (PI / 180))

typedef struct Vec2f32 {
    union {
        f32 data[2];
        struct {
            f32 x;
            f32 y;
        };
    };
} Vec2f32;
#define vec2f32(x,y) (Vec2f32){x,y}

typedef struct Vec3f32 {
  union {
    f32 data[3];
    struct {
      f32 x;
      f32 y;
      f32 z;
    };
  };
} Vec3f32;
#define vec3f32(x,y,z) (Vec3f32){x,y,z}

typedef struct Vec4f32 {
  union {
    f32 data[4];
    struct {
      f32 x;
      f32 y;
      f32 z;
      f32 w;
    };
  };
} Vec4f32;
#define vec4f32(x,y,z,w) (Vec4f32){x,y,z,w}

typedef struct Mat4f32 {
  union {
    f32 data[4][4];
    struct {
      f32 m0, m4, m8,  m12,
          m1, m5, m9,  m13,
          m2, m6, m10, m14,
          m3, m7, m11, m15;
    };
  };
} Mat4f32;
#define mat4f32(diag) (Mat4f32) {diag,0.0f,0.0f,0.0f,0.0f,diag,0.0f,0.0f,0.0f,0.0f,diag,0.0f,0.0f,0.0f,0.0f,diag}
#define mat4f32_identity() mat4f32(1.0f)

typedef struct Quatf32 {
  union {
    f32 data[4];
    struct {
      f32 x;
      f32 y;
      f32 z;
      f32 w;
    };
  };
} Quatf32;
#define quatf32(x,y,z,w) (Quatf32){x,y,z,w}
#define quatf32_identity() quatf32(0.0f, 0.0f, 0.0f, 1.0f)

typedef struct Transformf32 {
  Vec3f32 translation;
  Quatf32 rotation;
  Vec3f32 scale;
} Transformf32;
#define transformf32(t,r,s) (Transformf32){t,r,s}

// TODO(Fz): Colors should not be here, I think.
#define Color_Red        vec4f32(1.0f,  0.0f,  0.0f,  1.0f)
#define Color_Green      vec4f32(0.0f,  1.0f,  0.0f,  1.0f)
#define Color_Blue       vec4f32(0.0f,  0.0f,  1.0f,  1.0f)
#define Color_Yellow     vec4f32(1.0f,  1.0f,  0.0f,  1.0f)
#define Color_Cyan       vec4f32(0.0f,  1.0f,  1.0f,  1.0f)
#define Color_Magenta    vec4f32(1.0f,  0.0f,  1.0f,  1.0f)
#define Color_White      vec4f32(1.0f,  1.0f,  1.0f,  1.0f)
#define Color_Black      vec4f32(0.0f,  0.0f,  0.0f,  1.0f)
#define Color_Gray       vec4f32(0.5f,  0.5f,  0.5f,  1.0f)
#define Color_LightGray  vec4f32(0.75f, 0.75f, 0.75f, 1.0f)
#define Color_DarkGray   vec4f32(0.25f, 0.25f, 0.25f, 1.0f)
#define Color_Orange     vec4f32(1.0f,  0.5f,  0.0f,  1.0f)
#define Color_Purple     vec4f32(0.5f,  0.0f,  0.5f,  1.0f)
#define Color_Brown      vec4f32(0.6f,  0.4f,  0.2f,  1.0f)
#define Color_Pink       vec4f32(1.0f,  0.75f, 0.8f,  1.0f)

#define AXIS_X vec3f32(1.0f, 0.0f, 0.0f)
#define AXIS_Y vec3f32(0.0f, 1.0f, 0.0f)
#define AXIS_Z vec3f32(0.0f, 0.0f, 1.0f)

internal f32 f32_min(f32 a, f32 b);
internal f32 f32_max(f32 a, f32 b);
internal f32 f32_abs(f32 value);
internal f32 f32_lerp(f32 start, f32 end, f32 amount);
internal f32 f32_normalize(f32 value, f32 start, f32 end);
internal f32 f32_remap(f32 value, f32 inputStart, f32 inputEnd, f32 outputStart, f32 outputEnd);
internal f32 f32_wrap(f32 value, f32 min, f32 max);

// TODO(fz): Rename functions to match their type E,g, vec2f32_distance -> vec2f32_distance
internal f32 vec2f32_distance(Vec2f32 a, Vec2f32 b);
internal f32 vec2f32_distance_signed(Vec2f32 a, Vec2f32 b, Vec2f32 reference);

internal Vec2f32 vec2f32_add(Vec2f32 a, Vec2f32 b);
internal Vec2f32 vec2f32_sub(Vec2f32 a, Vec2f32 b);
internal Vec2f32 vec2f32_scale(Vec2f32 v, f32 scalar);
internal Vec2f32 vec2f32_normalize(Vec2f32 v);
internal f32 vec2f32_dot(Vec2f32 a, Vec2f32 b);
internal f32 vec2f32_length(Vec2f32 v);

internal Vec3f32 vec3f32_from_vec4f32(Vec4f32 v); /* Discards the w value */

internal Vec3f32 vec3f32_add(Vec3f32 a, Vec3f32 b);
internal Vec3f32 vec3f32_sub(Vec3f32 a, Vec3f32 b);
internal Vec3f32 vec3f32_mul(Vec3f32 a, Vec3f32 b);
internal Vec3f32 vec3f32_div(Vec3f32 a, Vec3f32 b);

internal Vec3f32 vec3f32_cross(Vec3f32 a, Vec3f32 b);
internal Vec3f32 vec3f32_scale(Vec3f32 v, f32 scalar);
internal Vec3f32 vec3f32_scale_xyz(Vec3f32 v, f32 scale_x, f32 scale_y, f32 scale_z);
internal Vec3f32 vec3f32_normalize(Vec3f32 v);
internal Vec3f32 vec3f32_rotate_by_axis(Vec3f32 v, Vec3f32 axis, f32 angle);
internal Vec3f32 vec3f32_lerp(Vec3f32 a, Vec3f32 b, f32 t);
internal Vec3f32 vec3f32_unproject(Vec3f32 source, Mat4f32 projection, Mat4f32 view);
internal Vec3f32 mat4f32_transform_vec3f32(Mat4f32 mat, Vec3f32 vec);

internal f32 vec3f32_dot(Vec3f32 a, Vec3f32 b);
internal f32 vec3f32_length(Vec3f32 v);
internal f32 vec3f32_distance(Vec3f32 a, Vec3f32 b);
internal f32 vec3f32_angle(Vec3f32 a, Vec3f32 b);

internal Vec4f32 vec4f32_from_vec3f32(Vec3f32 v);

internal Vec4f32 vec4f32_add(Vec4f32 a, Vec4f32 b);
internal Vec4f32 vec4f32_sub(Vec4f32 a, Vec4f32 b);
internal Vec4f32 vec4f32_mul(Vec4f32 a, Vec4f32 b);
internal Vec4f32 vec4f32_div(Vec4f32 a, Vec4f32 b);
internal Vec4f32 vec4f32_mul_mat4f32(Vec4f32 v, Mat4f32 m);

internal Vec4f32 vec4f32_scale(Vec4f32 v, f32 scalar);
internal Vec4f32 vec4f32_normalize(Vec4f32 v);
internal Vec4f32 vec4f32_lerp(Vec4f32 a, Vec4f32 b, f32 t);

internal f32 vec4f32_dot(Vec4f32 a, Vec4f32 b);
internal f32 vec4f32_length(Vec4f32 v);
internal f32 vec4f32_distance(Vec4f32 a, Vec4f32 b);

internal Mat4f32 mat4f32_mul(Mat4f32 left, Mat4f32 right); /* Apply the left matrix to the right matrix*/ 

internal Mat4f32 mat4f32_translate(f32 x, f32 y, f32 z);
internal Mat4f32 mat4f32_rotate_axis(Vec3f32 axis, f32 radians);
internal Mat4f32 mat4f32_rotate_x(f32 radians);
internal Mat4f32 mat4f32_rotate_y(f32 radians);
internal Mat4f32 mat4f32_rotate_z(f32 radians);
internal Mat4f32 mat4f32_rotate_xyz(Vec3f32 radians);
internal Mat4f32 mat4f32_rotate_zyx(Vec3f32 radians);

internal Mat4f32 mat4f32_transpose(Mat4f32 m);
internal Mat4f32 mat4f32_scale(f32 x, f32 y, f32 z);
internal Mat4f32 mat4f32_frustum(f64 left, f64 right, f64 bottom, f64 top, f64 near_plane, f64 far_plane);
internal Mat4f32 mat4f32_perspective(f32 fovy, f32 window_width, f32 window_height, f32 near_plane, f32 far_plane);
internal Mat4f32 mat4f32_ortographic(f64 left, f64 right, f64 bottom, f64 top, f64 near_plane, f64 far_plane);
internal Mat4f32 mat4f32_look_at(Vec3f32 eye, Vec3f32 target, Vec3f32 up);
internal Mat4f32 mat4f32_from_quatf32(Quatf32 q);
internal Transformf32 transformf32_from_mat4f32(Mat4f32 mat);

internal Quatf32 quatf32_add(Quatf32 q1, Quatf32 q2);
internal Quatf32 quatf32_add_value(Quatf32 q, f32 value);
internal Quatf32 quatf32_subtract(Quatf32 q1, Quatf32 q2);
internal Quatf32 quatf32_subtract_value(Quatf32 q, f32 value);
internal f32     quatf32_length(Quatf32 q);
internal Quatf32 quatf32_normalize(Quatf32 q);
internal Quatf32 quatf32_invert(Quatf32 q);
internal Quatf32 quatf32_multiply(Quatf32 q1, Quatf32 q2);
internal Quatf32 quatf32_scale(Quatf32 q, f32 scalar);
internal Quatf32 quatf32_divide(Quatf32 q1, Quatf32 q2);
internal Quatf32 quatf32_lerp(Quatf32 q1, Quatf32 q2, f32 amount);
internal Quatf32 quatf32_nlerp(Quatf32 q1, Quatf32 q2, f32 amount);
internal Quatf32 quatf32_slerp(Quatf32 q1, Quatf32 q2, f32 amount);
internal Quatf32 quatf32_cubic_hermit_spline(Quatf32 q1, Quatf32 outTangent1, Quatf32 q2, Quatf32 inTangent2, f32 t);
internal Quatf32 quatf32_from_vec3f32_to_vec3f32(Vec3f32 from, Vec3f32 to);
internal Quatf32 quatf32_from_mat4f32(Mat4f32 mat);
internal Quatf32 quatf32_from_axis_angle(Vec3f32 axis, f32 angle);
internal void    axis_angle_from_quatf32(Quatf32 q, Vec3f32 *axis, f32 *angle);
internal Quatf32 quatf32_from_euler(f32 pitch, f32 yaw, f32 roll);
internal void    euler_from_quatf32(Quatf32 q, f32* pitch, f32* yaw, f32* roll);
internal Quatf32 quatf32_mul_mat4f32(Quatf32 q, Mat4f32 mat);
internal b32     quatf32_equals(Quatf32 p, Quatf32 q);
internal Vec3f32 quatf32_rotate_vec3f32(Quatf32 q, Vec3f32 v);
internal Quatf32 quatf32_conjugate(Quatf32 q);
internal f32     quatf32_dot(Quatf32 q1, Quatf32 q2);

///////////////////////
//~ Prints

internal void vec2f32_print(Vec2f32 v, const char8 *label);
internal void vec3f32_print(Vec3f32 v, const char8 *label);
internal void vec4f32_print(Vec4f32 v, const char8 *label);
internal void mat4f32_print(Mat4f32 m, const char8 *label);
internal void quatf32_print(Quatf32 q, const char8 *label);
internal void transformf32_print(Transformf32 t, const char8 *label);

#endif // FZ_MATH_H