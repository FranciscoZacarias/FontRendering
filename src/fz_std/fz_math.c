internal f32 f32_abs(f32 value) {
  return fabsf(value);
}

internal f32 f32_lerp(f32 start, f32 end, f32 amount) {
  f32 result = start + amount*(end - start);
  return result;
}

internal f32 f32_normalize(f32 value, f32 start, f32 end) {
  f32 result = (value - start)/(end - start);
  return result;
}

internal f32 f32_remap(f32 value, f32 inputStart, f32 inputEnd, f32 outputStart, f32 outputEnd) {
    f32 result = (value - inputStart)/(inputEnd - inputStart)*(outputEnd - outputStart) + outputStart;
    return result;
}

internal f32 f32_wrap(f32 value, f32 min, f32 max) {
    f32 result = value - (max - min)*floorf((value - min)/(max - min));
    return result;
}

internal f32 vec2f32_distance(Vec2f32 a, Vec2f32 b) {
  f32 result = 0.0f;
  f32 dx = b.x - a.x;
  f32 dy = b.y - a.y;
  result = sqrtf(dx*dx + dy*dy);
  return result;
}

internal f32 vec2f32_distance_signed(Vec2f32 a, Vec2f32 b, Vec2f32 reference) {
  f32 result = 0.0f;
  f32 dx = b.x - a.x;
  f32 dy = b.y - a.y;
  f32 distance = sqrtf(dx*dx + dy*dy);
  
  f32 sign = (reference.x - a.x) * dy - (reference.y - a.y) * dx;
  
  if (sign < 0) {
    result = -distance;
  } else {
    result = distance;
  }
  
  return result;
}

internal Vec2f32 vec2f32_add(Vec2f32 a, Vec2f32 b) {
  Vec2f32 result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  return result;
}

internal Vec2f32 vec2f32_sub(Vec2f32 a, Vec2f32 b) {
  Vec2f32 result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  return result;
}

internal Vec2f32 vec2f32_scale(Vec2f32 v, f32 scalar) {
  Vec2f32 result;
  result.x = v.x * scalar;
  result.y = v.y * scalar;
  return result;
}

internal f32 vec2f32_dot(Vec2f32 a, Vec2f32 b) {
  return a.x * b.x + a.y * b.y;
}

internal f32 vec2f32_length(Vec2f32 v) {
  return sqrtf(v.x * v.x + v.y * v.y);
}

internal Vec2f32 vec2f32_normalize(Vec2f32 v) {
  f32 len = sqrtf(v.x * v.x + v.y * v.y);
  Vec2f32 result;
  if (len == 0.0f) {
    result.x = 0.0f;
    result.y = 0.0f;
  } else {
    result.x = v.x / len;
    result.y = v.y / len;
  }
  return result;
}

internal Vec3f32 vec3f32_from_vec4f32(Vec4f32 v) {
  Vec3f32 result = { v.x, v.y, v.z };
  return result;
}

internal Vec3f32 vec3f32_add(Vec3f32 a, Vec3f32 b) {
  Vec3f32 result = {
    a.x + b.x,
    a.y + b.y,
    a.z + b.z
  };
  return result;
}

internal Vec3f32 vec3f32_sub(Vec3f32 a, Vec3f32 b) {
  Vec3f32 result = {
    a.x - b.x,
    a.y - b.y,
    a.z - b.z
  };
  return result;
}

internal Vec3f32 vec3f32_mul(Vec3f32 a, Vec3f32 b) {
  Vec3f32 result = {
    a.x * b.x,
    a.y * b.y,
    a.z * b.z
  };
  return result;
}

internal Vec3f32 vec3f32_div(Vec3f32 a, Vec3f32 b) {
  Vec3f32 result = {
    a.x / b.x,
    a.y / b.y,
    a.z / b.z
  };
  return result;
}

internal Vec4f32 vec4f32_mul_mat4f32(Vec4f32 v, Mat4f32 m) {
  Vec4f32 result = { 
    m.m0*v.x + m.m4*v.y + m.m8 *v.z + m.m12*v.w,
    m.m1*v.x + m.m5*v.y + m.m9 *v.z + m.m13*v.w,
    m.m2*v.x + m.m6*v.y + m.m10*v.z + m.m14*v.w,
    m.m3*v.x + m.m7*v.y + m.m11*v.z + m.m15*v.w
  };
  return result;
}

internal Vec3f32 vec3f32_cross(Vec3f32 a, Vec3f32 b) {
  Vec3f32 result = {
    a.y*b.z - a.z*b.y,
    a.z*b.x - a.x*b.z,
    a.x*b.y - a.y*b.x
  };
  return result;
}

internal Vec3f32 vec3f32_scale(Vec3f32 v, f32 scalar) {
  Vec3f32 result = {
    v.x*scalar,
    v.y*scalar,
    v.z*scalar
  };
  return result;
}

internal Vec3f32 vec3f32_scale_xyz(Vec3f32 v, f32 scale_x, f32 scale_y, f32 scale_z) {
  Vec3f32 result = {
    v.x * scale_x,
    v.y * scale_y,
    v.z * scale_z
  };
  return result;  
}

internal Vec3f32 vec3f32_normalize(Vec3f32 v) {
  Vec3f32 result = v;
  f32 length = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
  if (length != 0.0f) {
    f32 ilength = 1.0f/length;
    result.x *= ilength;
    result.y *= ilength;
    result.z *= ilength;
  }
  return result;
}

internal Vec3f32 vec3f32_rotate_by_axis(Vec3f32 v, Vec3f32 axis, f32 radians) {
  // Using Euler-Rodrigues Formula
  // Ref.: https://en.wikipedia.org/w/index.php?title=Euler%E2%80%93Rodrigues_formula
  
  Vec3f32 result = v;
  
  // Vector3Normalize(axis);
  f32 length = sqrtf(axis.x*axis.x + axis.y*axis.y + axis.z*axis.z);
  if (length == 0.0f) length = 1.0f;
  f32 ilength = 1.0f/length;
  axis.x *= ilength;
  axis.y *= ilength;
  axis.z *= ilength;
  
  radians /= 2.0f;
  f32 a = sinf(radians);
  f32 b = axis.x*a;
  f32 c = axis.y*a;
  f32 d = axis.z*a;
  a = cosf(radians);
  Vec3f32 w = { b, c, d };
  
  // Vector3CrossProduct(w, v)
  Vec3f32 wv = { w.y*v.z - w.z*v.y, w.z*v.x - w.x*v.z, w.x*v.y - w.y*v.x };
  
  // Vector3CrossProduct(w, wv)
  Vec3f32 wwv = { w.y*wv.z - w.z*wv.y, w.z*wv.x - w.x*wv.z, w.x*wv.y - w.y*wv.x };
  
  // Vector3Scale(wv, 2*a)
  a *= 2;
  wv.x *= a;
  wv.y *= a;
  wv.z *= a;
  
  // Vector3Scale(wwv, 2)
  wwv.x *= 2;
  wwv.y *= 2;
  wwv.z *= 2;
  
  result.x += wv.x;
  result.y += wv.y;
  result.z += wv.z;
  
  result.x += wwv.x;
  result.y += wwv.y;
  result.z += wwv.z;
  
  return result;
}

internal Vec3f32 vec3f32_lerp(Vec3f32 a, Vec3f32 b, f32 t) {
  Vec3f32 result = {
    a.x + t*(b.x - a.x),
    a.y + t*(b.y - a.y),
    a.z + t*(b.z - a.z)
  };
  return result;
}

internal Vec3f32 vec3f32_unproject(Vec3f32 source, Mat4f32 projection, Mat4f32 view) {
  Vec3f32 result = { 0 };
  
  // Calculate unprojected matrix (multiply view matrix by projection matrix) and invert it
  Mat4f32 matViewProj = {      // MatrixMultiply(view, projection);
    view.m0*projection.m0 + view.m1*projection.m4 + view.m2*projection.m8 + view.m3*projection.m12,
    view.m0*projection.m1 + view.m1*projection.m5 + view.m2*projection.m9 + view.m3*projection.m13,
    view.m0*projection.m2 + view.m1*projection.m6 + view.m2*projection.m10 + view.m3*projection.m14,
    view.m0*projection.m3 + view.m1*projection.m7 + view.m2*projection.m11 + view.m3*projection.m15,
    view.m4*projection.m0 + view.m5*projection.m4 + view.m6*projection.m8 + view.m7*projection.m12,
    view.m4*projection.m1 + view.m5*projection.m5 + view.m6*projection.m9 + view.m7*projection.m13,
    view.m4*projection.m2 + view.m5*projection.m6 + view.m6*projection.m10 + view.m7*projection.m14,
    view.m4*projection.m3 + view.m5*projection.m7 + view.m6*projection.m11 + view.m7*projection.m15,
    view.m8*projection.m0 + view.m9*projection.m4 + view.m10*projection.m8 + view.m11*projection.m12,
    view.m8*projection.m1 + view.m9*projection.m5 + view.m10*projection.m9 + view.m11*projection.m13,
    view.m8*projection.m2 + view.m9*projection.m6 + view.m10*projection.m10 + view.m11*projection.m14,
    view.m8*projection.m3 + view.m9*projection.m7 + view.m10*projection.m11 + view.m11*projection.m15,
    view.m12*projection.m0 + view.m13*projection.m4 + view.m14*projection.m8 + view.m15*projection.m12,
    view.m12*projection.m1 + view.m13*projection.m5 + view.m14*projection.m9 + view.m15*projection.m13,
    view.m12*projection.m2 + view.m13*projection.m6 + view.m14*projection.m10 + view.m15*projection.m14,
    view.m12*projection.m3 + view.m13*projection.m7 + view.m14*projection.m11 + view.m15*projection.m15 };
  
  // Calculate inverted matrix -> MatrixInvert(matViewProj);
  // Cache the matrix values (speed optimization)
  f32 a00 = matViewProj.m0, a01 = matViewProj.m1, a02 = matViewProj.m2, a03 = matViewProj.m3;
  f32 a10 = matViewProj.m4, a11 = matViewProj.m5, a12 = matViewProj.m6, a13 = matViewProj.m7;
  f32 a20 = matViewProj.m8, a21 = matViewProj.m9, a22 = matViewProj.m10, a23 = matViewProj.m11;
  f32 a30 = matViewProj.m12, a31 = matViewProj.m13, a32 = matViewProj.m14, a33 = matViewProj.m15;
  
  f32 b00 = a00*a11 - a01*a10;
  f32 b01 = a00*a12 - a02*a10;
  f32 b02 = a00*a13 - a03*a10;
  f32 b03 = a01*a12 - a02*a11;
  f32 b04 = a01*a13 - a03*a11;
  f32 b05 = a02*a13 - a03*a12;
  f32 b06 = a20*a31 - a21*a30;
  f32 b07 = a20*a32 - a22*a30;
  f32 b08 = a20*a33 - a23*a30;
  f32 b09 = a21*a32 - a22*a31;
  f32 b10 = a21*a33 - a23*a31;
  f32 b11 = a22*a33 - a23*a32;
  
  // Calculate the invert determinant (inlined to avoid double-caching)
  f32 invDet = 1.0f/(b00*b11 - b01*b10 + b02*b09 + b03*b08 - b04*b07 + b05*b06);
  
  Mat4f32 matViewProjInv = {
    (a11*b11 - a12*b10 + a13*b09)*invDet,
    (-a01*b11 + a02*b10 - a03*b09)*invDet,
    (a31*b05 - a32*b04 + a33*b03)*invDet,
    (-a21*b05 + a22*b04 - a23*b03)*invDet,
    (-a10*b11 + a12*b08 - a13*b07)*invDet,
    (a00*b11 - a02*b08 + a03*b07)*invDet,
    (-a30*b05 + a32*b02 - a33*b01)*invDet,
    (a20*b05 - a22*b02 + a23*b01)*invDet,
    (a10*b10 - a11*b08 + a13*b06)*invDet,
    (-a00*b10 + a01*b08 - a03*b06)*invDet,
    (a30*b04 - a31*b02 + a33*b00)*invDet,
    (-a20*b04 + a21*b02 - a23*b00)*invDet,
    (-a10*b09 + a11*b07 - a12*b06)*invDet,
    (a00*b09 - a01*b07 + a02*b06)*invDet,
    (-a30*b03 + a31*b01 - a32*b00)*invDet,
    (a20*b03 - a21*b01 + a22*b00)*invDet };
  
  // Create quaternion from source point
  Quatf32 quat = { source.x, source.y, source.z, 1.0f };
  
  // Multiply quat point by unprojecte matrix
  Quatf32 qtransformed = {     // QuaternionTransform(quat, matViewProjInv)
    matViewProjInv.m0*quat.x + matViewProjInv.m4*quat.y + matViewProjInv.m8*quat.z + matViewProjInv.m12*quat.w,
    matViewProjInv.m1*quat.x + matViewProjInv.m5*quat.y + matViewProjInv.m9*quat.z + matViewProjInv.m13*quat.w,
    matViewProjInv.m2*quat.x + matViewProjInv.m6*quat.y + matViewProjInv.m10*quat.z + matViewProjInv.m14*quat.w,
    matViewProjInv.m3*quat.x + matViewProjInv.m7*quat.y + matViewProjInv.m11*quat.z + matViewProjInv.m15*quat.w };
  
  // Normalized world points in vectors
  result.x = qtransformed.x/qtransformed.w;
  result.y = qtransformed.y/qtransformed.w;
  result.z = qtransformed.z/qtransformed.w;
  
  return result;
}

internal Vec3f32 mat4f32_transform_vec3f32(Mat4f32 mat, Vec3f32 vec) {
  f32 x = mat.m0 * vec.x + mat.m4 * vec.y + mat.m8  * vec.z;
  f32 y = mat.m1 * vec.x + mat.m5 * vec.y + mat.m9  * vec.z;
  f32 z = mat.m2 * vec.x + mat.m6 * vec.y + mat.m10 * vec.z;
  return vec3f32(x, y, z);
}

internal f32 vec3f32_dot(Vec3f32 a, Vec3f32 b) {
  f32 result = a.x*b.x + a.y*b.y + a.z*b.z;
  return result;
}

internal f32 vec3f32_length(Vec3f32 v) {
  f32 result = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
  return result;
}

internal f32 vec3f32_distance(Vec3f32 a, Vec3f32 b) {
  f32 result = 0.0f;
  f32 dx = b.x - a.x;
  f32 dy = b.y - a.y;
  f32 dz = b.z - a.z;
  result = sqrtf(dx*dx + dy*dy + dz*dz);
  return result;
}

internal f32 vec3f32_angle(Vec3f32 a, Vec3f32 b) {
  f32 result = 0.0f;
  Vec3f32 cross = {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
  f32 len = sqrtf(cross.x*cross.x + cross.y*cross.y + cross.z*cross.z);
  f32 dot = (a.x*b.x + a.y*b.y + a.z*b.z);
  result  = atan2f(len, dot);
  return result;
}

internal Vec4f32 vec4f32_from_vec3f32(Vec3f32 v) {
  Vec4f32 result = {v.x, v.y, v.z};
  return result;
}

internal Vec4f32 vec4f32_add(Vec4f32 a, Vec4f32 b) {
  Vec4f32 result = {
    a.x + b.x,
    a.y + b.y,
    a.z + b.z,
    a.w + b.w
  };
  return result;
}

internal Vec4f32 vec4f32_sub(Vec4f32 a, Vec4f32 b) {
  Vec4f32 result = {
    a.x - b.x,
    a.y - b.y,
    a.z - b.z,
    a.w - b.w
  };
  return result;
}

internal Vec4f32 vec4f32_mul(Vec4f32 a, Vec4f32 b) {
  Vec4f32 result = {
    a.x * b.x,
    a.y * b.y,
    a.z * b.z,
    a.w * b.w
  };
  return result;
}

internal Vec4f32 vec4f32_div(Vec4f32 a, Vec4f32 b) {
  Vec4f32 result = {
    a.x / b.x,
    a.y / b.y,
    a.z / b.z,
    a.w / b.w
  };
  return result;
}

internal Vec4f32 vec4f32_scale(Vec4f32 v, f32 scalar) {
  Vec4f32 result = {
    v.x*scalar,
    v.y*scalar,
    v.z*scalar,
    v.w*scalar
  };
  return result;
}

internal Vec4f32 vec4f32_normalize(Vec4f32 v) {
  Vec4f32 result = v;
  f32 length = sqrtf((v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w));
  if (length > 0) {
    f32 ilength = 1.0f/length;
    result.x = v.x*ilength;
    result.y = v.y*ilength;
    result.z = v.z*ilength;
    result.w = v.w*ilength;
  }
  return result;
}

internal Vec4f32 vec4f32_lerp(Vec4f32 a, Vec4f32 b, f32 t) {
  Vec4f32 result = {
    a.x + t*(b.x - a.x),
    a.y + t*(b.y - a.y),
    a.z + t*(b.z - a.z),
    a.w + t*(b.w - a.w)
  };
  return result;
}

internal f32 vec4f32_dot(Vec4f32 a, Vec4f32 b) {
  f32 result = (a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w);
  return result;
}

internal f32 vec4f32_length(Vec4f32 v) {
  f32 result = sqrtf((v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w));
  return result;
}

internal f32 vec4f32_distance(Vec4f32 a, Vec4f32 b) {
  f32 result = 0.0f;
  f32 dx = a.x - b.x;
  f32 dy = a.y - b.y;
  f32 dz = a.z - b.z;
  f32 dw = a.w - b.w;
  result = sqrtf(dx*dx + dy*dy + dz*dz + dw*dw);
  return result;
}

//////////////////////////////////////////////
// Matrix4 f32

internal Mat4f32 mat4f32_mul(Mat4f32 left, Mat4f32 right) {
  Mat4f32 result = { 0 };
  result.m0  = left.m0 *right.m0 + left.m1 *right.m4 + left.m2 *right.m8  + left.m3 *right.m12;
  result.m1  = left.m0 *right.m1 + left.m1 *right.m5 + left.m2 *right.m9  + left.m3 *right.m13;
  result.m2  = left.m0 *right.m2 + left.m1 *right.m6 + left.m2 *right.m10 + left.m3 *right.m14;
  result.m3  = left.m0 *right.m3 + left.m1 *right.m7 + left.m2 *right.m11 + left.m3 *right.m15;
  result.m4  = left.m4 *right.m0 + left.m5 *right.m4 + left.m6 *right.m8  + left.m7 *right.m12;
  result.m5  = left.m4 *right.m1 + left.m5 *right.m5 + left.m6 *right.m9  + left.m7 *right.m13;
  result.m6  = left.m4 *right.m2 + left.m5 *right.m6 + left.m6 *right.m10 + left.m7 *right.m14;
  result.m7  = left.m4 *right.m3 + left.m5 *right.m7 + left.m6 *right.m11 + left.m7 *right.m15;
  result.m8  = left.m8 *right.m0 + left.m9 *right.m4 + left.m10*right.m8  + left.m11*right.m12;
  result.m9  = left.m8 *right.m1 + left.m9 *right.m5 + left.m10*right.m9  + left.m11*right.m13;
  result.m10 = left.m8 *right.m2 + left.m9 *right.m6 + left.m10*right.m10 + left.m11*right.m14;
  result.m11 = left.m8 *right.m3 + left.m9 *right.m7 + left.m10*right.m11 + left.m11*right.m15;
  result.m12 = left.m12*right.m0 + left.m13*right.m4 + left.m14*right.m8  + left.m15*right.m12;
  result.m13 = left.m12*right.m1 + left.m13*right.m5 + left.m14*right.m9  + left.m15*right.m13;
  result.m14 = left.m12*right.m2 + left.m13*right.m6 + left.m14*right.m10 + left.m15*right.m14;
  result.m15 = left.m12*right.m3 + left.m13*right.m7 + left.m14*right.m11 + left.m15*right.m15;
  return result;
}

internal Mat4f32 mat4f32_translate(f32 x, f32 y, f32 z) {
  Mat4f32 result = {
    1.0f, 0.0f, 0.0f, x,
    0.0f, 1.0f, 0.0f, y,
    0.0f, 0.0f, 1.0f, z,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  return result;
}

internal Mat4f32 mat4f32_rotate_axis(Vec3f32 axis, f32 radians) {
  Mat4f32 result = { 0 };
  
  f32 x = axis.x;
  f32 y = axis.y;
  f32 z = axis.z;
  f32 lengthSquared = x*x + y*y + z*z;
  
  if ((lengthSquared != 1.0f) && (lengthSquared != 0.0f)) {
    f32 ilength = 1.0f/sqrtf(lengthSquared);
    x *= ilength;
    y *= ilength;
    z *= ilength;
  }
  
  f32 sinres = sinf(radians);
  f32 cosres = cosf(radians);
  f32 t = 1.0f - cosres;
  
  result.m0 = x*x*t + cosres;
  result.m1 = y*x*t + z*sinres;
  result.m2 = z*x*t - y*sinres;
  result.m3 = 0.0f;
  
  result.m4 = x*y*t - z*sinres;
  result.m5 = y*y*t + cosres;
  result.m6 = z*y*t + x*sinres;
  result.m7 = 0.0f;
  
  result.m8 = x*z*t + y*sinres;
  result.m9 = y*z*t - x*sinres;
  result.m10 = z*z*t + cosres;
  result.m11 = 0.0f;
  
  result.m12 = 0.0f;
  result.m13 = 0.0f;
  result.m14 = 0.0f;
  result.m15 = 1.0f;
  
  return result;
}

internal Mat4f32 mat4f32_rotate_x(f32 radians) {
  Mat4f32 result = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  f32 cosres = cosf(radians);
  f32 sinres = sinf(radians);
  result.m5  = cosres;
  result.m6  = sinres;
  result.m9  = -sinres;
  result.m10 = cosres;
  return result;
}

internal Mat4f32 mat4f32_rotate_y(f32 radians) {
  Mat4f32 result = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  f32 cosres = cosf(radians);
  f32 sinres = sinf(radians);
  result.m0 = cosres;
  result.m2 = -sinres;
  result.m8 = sinres;
  result.m10 = cosres;
  return result;
}

internal Mat4f32 mat4f32_rotate_z(f32 radians) {
  Mat4f32 result = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  f32 cosres = cosf(radians);
  f32 sinres = sinf(radians);
  result.m0 = cosres;
  result.m1 = sinres;
  result.m4 = -sinres;
  result.m5 = cosres;
  return result;
}

internal Mat4f32 mat4f32_rotate_xyz(Vec3f32 radians) {
  Mat4f32 result = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  
  f32 cosz = cosf(-radians.z);
  f32 sinz = sinf(-radians.z);
  f32 cosy = cosf(-radians.y);
  f32 siny = sinf(-radians.y);
  f32 cosx = cosf(-radians.x);
  f32 sinx = sinf(-radians.x);
  
  result.m0 = cosz*cosy;
  result.m1 = (cosz*siny*sinx) - (sinz*cosx);
  result.m2 = (cosz*siny*cosx) + (sinz*sinx);
  
  result.m4 = sinz*cosy;
  result.m5 = (sinz*siny*sinx) + (cosz*cosx);
  result.m6 = (sinz*siny*cosx) - (cosz*sinx);
  
  result.m8 = -siny;
  result.m9 = cosy*sinx;
  result.m10= cosy*cosx;
  
  return result;
}

internal Mat4f32 mat4f32_rotate_zyx(Vec3f32 radians) {
  Mat4f32 result = { 0 };
  
  f32 cz = cosf(radians.z);
  f32 sz = sinf(radians.z);
  f32 cy = cosf(radians.y);
  f32 sy = sinf(radians.y);
  f32 cx = cosf(radians.x);
  f32 sx = sinf(radians.x);
  
  result.m0 = cz*cy;
  result.m4 = cz*sy*sx - cx*sz;
  result.m8 = sz*sx + cz*cx*sy;
  result.m12 = 0;
  
  result.m1 = cy*sz;
  result.m5 = cz*cx + sz*sy*sx;
  result.m9 = cx*sz*sy - cz*sx;
  result.m13 = 0;
  
  result.m2 = -sy;
  result.m6 = cy*sx;
  result.m10 = cy*cx;
  result.m14 = 0;
  
  result.m3 = 0;
  result.m7 = 0;
  result.m11 = 0;
  result.m15 = 1;
  
  return result;
}

internal Mat4f32 mat4f32_transpose(Mat4f32 m) {
  Mat4f32 result = { 0 };
  result.m0  = m.m0;
  result.m1  = m.m4;
  result.m2  = m.m8;
  result.m3  = m.m12;
  result.m4  = m.m1;
  result.m5  = m.m5;
  result.m6  = m.m9;
  result.m7  = m.m13;
  result.m8  = m.m2;
  result.m9  = m.m6;
  result.m10 = m.m10;
  result.m11 = m.m14;
  result.m12 = m.m3;
  result.m13 = m.m7;
  result.m14 = m.m11;
  result.m15 = m.m15;
  return result;
}

internal Mat4f32 mat4f32_scale(f32 x, f32 y, f32 z) {
  Mat4f32 result = {
    x,    0.0f, 0.0f, 0.0f,
    0.0f, y,    0.0f, 0.0f,
    0.0f, 0.0f, z,    0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  return result;
}

internal Mat4f32 mat4f32_frustum(f64 left, f64 right, f64 bottom, f64 top, f64 near_plane, f64 far_plane) {
  Mat4f32 result = { 0 };
  
  f32 rl = (f32)(right - left);
  f32 tb = (f32)(top - bottom);
  f32 fn = (f32)(far_plane - near_plane);
  
  result.m0 = ((f32)near_plane*2.0f)/rl;
  result.m1 = 0.0f;
  result.m2 = 0.0f;
  result.m3 = 0.0f;
  
  result.m4 = 0.0f;
  result.m5 = ((f32)near_plane*2.0f)/tb;
  result.m6 = 0.0f;
  result.m7 = 0.0f;
  
  result.m8 = ((f32)right + (f32)left)/rl;
  result.m9 = ((f32)top + (f32)bottom)/tb;
  result.m10 = -((f32)far_plane + (f32)near_plane)/fn;
  result.m11 = -1.0f;
  
  result.m12 = 0.0f;
  result.m13 = 0.0f;
  result.m14 = -((f32)far_plane*(f32)near_plane*2.0f)/fn;
  result.m15 = 0.0f;
  
  return result;
}

// TODO(Fz): These don't need to be f64 
internal Mat4f32 mat4f32_perspective(f32 fov_degrees, f32 window_width, f32 window_height, f32 near_plane, f32 far_plane) {
  Mat4f32 result = { 0 };
  
  // FOV in degrees to FOVY in radians
  f32 aspect = window_width / window_height;
  f32 fov_rad = Radians(fov_degrees);
  f32 half_fovy_rad = atan(tan(fov_rad / 2.0f) / aspect);
  f32 fovy = half_fovy_rad * 2.0f;

  f32 top = near_plane*tan(fovy*0.5);
  f32 bottom = -top;
  f32 right = top*(window_width/window_height);
  f32 left = -right;
  
  // MatrixFrustum(-right, right, -top, top, near, far);
  f32 rl = (right - left);
  f32 tb = (top - bottom);
  f32 fn = (far_plane - near_plane);
  
  result.m0 = (near_plane*2.0f)/rl;
  result.m5 = (near_plane*2.0f)/tb;
  result.m8 = (right + left)/rl;
  result.m9 = (top + bottom)/tb;
  result.m10 = -(far_plane + near_plane)/fn;
  result.m11 = -1.0f;
  result.m14 = -(far_plane*near_plane*2.0f)/fn;
  
  return result;
}

internal Mat4f32 mat4f32_ortographic(f64 left, f64 right, f64 bottom, f64 top, f64 near_plane, f64 far_plane) {
  Mat4f32 result = { 0 };
  
  f32 rl = (f32)(right - left);
  f32 tb = (f32)(top - bottom);
  f32 fn = (f32)(far_plane - near_plane);
  
  result.m0 = 2.0f/rl;
  result.m1 = 0.0f;
  result.m2 = 0.0f;
  result.m3 = 0.0f;
  result.m4 = 0.0f;
  result.m5 = 2.0f/tb;
  result.m6 = 0.0f;
  result.m7 = 0.0f;
  result.m8 = 0.0f;
  result.m9 = 0.0f;
  result.m10 = -2.0f/fn;
  result.m11 = 0.0f;
  result.m12 = -((f32)left + (f32)right)/rl;
  result.m13 = -((f32)top + (f32)bottom)/tb;
  result.m14 = -((f32)far_plane + (f32)near_plane)/fn;
  result.m15 = 1.0f;
  
  return result;
}

internal Mat4f32 mat4f32_look_at(Vec3f32 eye, Vec3f32 target, Vec3f32 up) {
  Mat4f32 result = { 0 };
  
  f32 length = 0.0f;
  f32 ilength = 0.0f;
  
  // Vector3Subtract(eye, target)
  Vec3f32 vz = { eye.x - target.x, eye.y - target.y, eye.z - target.z };
  
  // Vector3Normalize(vz)
  Vec3f32 v = vz;
  length = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
  if (length == 0.0f) length = 1.0f;
  ilength = 1.0f/length;
  vz.x *= ilength;
  vz.y *= ilength;
  vz.z *= ilength;
  
  // Vector3CrossProduct(up, vz)
  Vec3f32 vx = { up.y*vz.z - up.z*vz.y, up.z*vz.x - up.x*vz.z, up.x*vz.y - up.y*vz.x };
  
  // Vector3Normalize(x)
  v = vx;
  length = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
  if (length == 0.0f) length = 1.0f;
  ilength = 1.0f/length;
  vx.x *= ilength;
  vx.y *= ilength;
  vx.z *= ilength;
  
  // Vector3CrossProduct(vz, vx)
  Vec3f32 vy = { vz.y*vx.z - vz.z*vx.y, vz.z*vx.x - vz.x*vx.z, vz.x*vx.y - vz.y*vx.x };
  
  result.m0 = vx.x;
  result.m1 = vy.x;
  result.m2 = vz.x;
  result.m3 = 0.0f;
  result.m4 = vx.y;
  result.m5 = vy.y;
  result.m6 = vz.y;
  result.m7 = 0.0f;
  result.m8 = vx.z;
  result.m9 = vy.z;
  result.m10 = vz.z;
  result.m11 = 0.0f;
  result.m12 = -(vx.x*eye.x + vx.y*eye.y + vx.z*eye.z);
  result.m13 = -(vy.x*eye.x + vy.y*eye.y + vy.z*eye.z);
  result.m14 = -(vz.x*eye.x + vz.y*eye.y + vz.z*eye.z);
  result.m15 = 1.0f;
  
  return result;
}

internal Mat4f32 mat4f32_from_quatf32(Quatf32 q) {
  Mat4f32 result = mat4f32_identity();

  f32 a2 = q.x*q.x;
  f32 b2 = q.y*q.y;
  f32 c2 = q.z*q.z;
  f32 ac = q.x*q.z;
  f32 ab = q.x*q.y;
  f32 bc = q.y*q.z;
  f32 ad = q.w*q.x;
  f32 bd = q.w*q.y;
  f32 cd = q.w*q.z;

  result.m0 = 1 - 2*(b2 + c2);
  result.m1 = 2*(ab + cd);
  result.m2 = 2*(ac - bd);

  result.m4 = 2*(ab - cd);
  result.m5 = 1 - 2*(a2 + c2);
  result.m6 = 2*(bc + ad);

  result.m8 = 2*(ac + bd);
  result.m9 = 2*(bc - ad);
  result.m10 = 1 - 2*(a2 + b2);

  return result;
}

internal Transformf32 transformf32_from_mat4f32(Mat4f32 mat) {
  Transformf32 result = { 0 };

  // Extract translation.
  result.translation.x = mat.m12;
  result.translation.y = mat.m13;
  result.translation.z = mat.m14;

  // Extract upper-left for determinant computation
  f32 a = mat.m0;
  f32 b = mat.m4;
  f32 c = mat.m8;
  f32 d = mat.m1;
  f32 e = mat.m5;
  f32 f = mat.m9;
  f32 g = mat.m2;
  f32 h = mat.m6;
  f32 i = mat.m10;
  f32 A = e*i - f*h;
  f32 B = f*g - d*i;
  f32 C = d*h - e*g;

  // Extract scale
  f32 det = a*A + b*B + c*C;
  Vec3f32 abc = vec3f32(a, b, c);
  Vec3f32 def = vec3f32(d, e, f);
  Vec3f32 ghi = vec3f32(g, h, i);

  f32 scalex = vec3f32_length(abc);
  f32 scaley = vec3f32_length(def);
  f32 scalez = vec3f32_length(ghi);
  Vec3f32 s  = vec3f32(scalex, scaley, scalez);
  if (det < 0) {
    s = vec3f32(-s.x, -s.y, -s.z);
  }

  result.scale = s;

  // Remove scale from the matrix if it is not close to zero
  Mat4f32 clone = mat;
  if (!FloatEquals(det, 0)) {
    clone.m0 /= s.x;
    clone.m5 /= s.y;
    clone.m10 /= s.z;
    result.rotation = quatf32_from_mat4f32(clone);
  }  else {
    result.rotation = quatf32_identity();
  }

  return result;
}

internal Quatf32 quatf32_add(Quatf32 q1, Quatf32 q2) {
  Quatf32 result = {q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w};
  return result;
}

internal Quatf32 quatf32_add_value(Quatf32 q, f32 value) {
  Quatf32 result = {q.x + value, q.y + value, q.z + value, q.w + value};
  return result;
}

internal Quatf32 quatf32_subtract(Quatf32 q1, Quatf32 q2) {
  Quatf32 result = {q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w};
  return result;
}

internal Quatf32 quatf32_subtract_value(Quatf32 q, f32 value) {
  Quatf32 result = {q.x - value, q.y - value, q.z - value, q.w - value};
  return result;
}

internal f32 quatf32_length(Quatf32 q) {
  f32 result = sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
  return result;
}

internal Quatf32 quatf32_normalize(Quatf32 q) {
  Quatf32 result = { 0 };

  f32 length = sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
  if (length == 0.0f) {
    length = 1.0f;
  }
  f32 ilength = 1.0f/length;

  result.x = q.x*ilength;
  result.y = q.y*ilength;
  result.z = q.z*ilength;
  result.w = q.w*ilength;

  return result;
}

internal Quatf32 quatf32_invert(Quatf32 q) {
  Quatf32 result = q;
  f32 lengthSq = q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;

  if (lengthSq != 0.0f) {
    f32 invLength = 1.0f/lengthSq;
    result.x *= -invLength;
    result.y *= -invLength;
    result.z *= -invLength;
    result.w *= invLength;
  }
  return result;
}

internal Quatf32 quatf32_multiply(Quatf32 q1, Quatf32 q2) {
  Quatf32 result = { 0 };
  f32 qax = q1.x, qay = q1.y, qaz = q1.z, qaw = q1.w;
  f32 qbx = q2.x, qby = q2.y, qbz = q2.z, qbw = q2.w;

  result.x = qax*qbw + qaw*qbx + qay*qbz - qaz*qby;
  result.y = qay*qbw + qaw*qby + qaz*qbx - qax*qbz;
  result.z = qaz*qbw + qaw*qbz + qax*qby - qay*qbx;
  result.w = qaw*qbw - qax*qbx - qay*qby - qaz*qbz;

  return result;
}

internal Quatf32 quatf32_scale(Quatf32 q, f32 scalar) {
  Quatf32 result = { 0 };

  result.x = q.x*scalar;
  result.y = q.y*scalar;
  result.z = q.z*scalar;
  result.w = q.w*scalar;

  return result;
}

internal Quatf32 quatf32_divide(Quatf32 q1, Quatf32 q2) {
  Quatf32 result = { q1.x/q2.x, q1.y/q2.y, q1.z/q2.z, q1.w/q2.w };
  return result;
}

internal Quatf32 quatf32_lerp(Quatf32 q1, Quatf32 q2, f32 amount) {
  Quatf32 result = { 0 };

  result.x = q1.x + amount*(q2.x - q1.x);
  result.y = q1.y + amount*(q2.y - q1.y);
  result.z = q1.z + amount*(q2.z - q1.z);
  result.w = q1.w + amount*(q2.w - q1.w);

  return result;
}

internal Quatf32 quatf32_nlerp(Quatf32 q1, Quatf32 q2, f32 amount) {
  Quatf32 result = { 0 };

  // QuaternionLerp(q1, q2, amount)
  result.x = q1.x + amount*(q2.x - q1.x);
  result.y = q1.y + amount*(q2.y - q1.y);
  result.z = q1.z + amount*(q2.z - q1.z);
  result.w = q1.w + amount*(q2.w - q1.w);

  // QuaternionNormalize(q);
  Quatf32 q = result;
  f32 length = sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
  if (length == 0.0f) {
    length = 1.0f;
  }
  f32 ilength = 1.0f/length;

  result.x = q.x*ilength;
  result.y = q.y*ilength;
  result.z = q.z*ilength;
  result.w = q.w*ilength;

  return result;
}

internal Quatf32 quatf32_slerp(Quatf32 q1, Quatf32 q2, f32 amount) {
  Quatf32 result = { 0 };


  f32 cosHalfTheta = q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;

  if (cosHalfTheta < 0) {
    q2.x = -q2.x; q2.y = -q2.y; q2.z = -q2.z; q2.w = -q2.w;
    cosHalfTheta = -cosHalfTheta;
  }

  if (f32_abs(cosHalfTheta) >= 1.0f) {
    result = q1;
  } else if (cosHalfTheta > 0.95f) {
    result = quatf32_nlerp(q1, q2, amount);
  } else {
    f32 halfTheta = acosf(cosHalfTheta);
    f32 sinHalfTheta = sqrtf(1.0f - cosHalfTheta*cosHalfTheta);

    if (f32_abs(sinHalfTheta) < EPSILON) {
      result.x = (q1.x*0.5f + q2.x*0.5f);
      result.y = (q1.y*0.5f + q2.y*0.5f);
      result.z = (q1.z*0.5f + q2.z*0.5f);
      result.w = (q1.w*0.5f + q2.w*0.5f);
    } else {
      f32 ratioA = sinf((1 - amount)*halfTheta)/sinHalfTheta;
      f32 ratioB = sinf(amount*halfTheta)/sinHalfTheta;
      result.x = (q1.x*ratioA + q2.x*ratioB);
      result.y = (q1.y*ratioA + q2.y*ratioB);
      result.z = (q1.z*ratioA + q2.z*ratioB);
      result.w = (q1.w*ratioA + q2.w*ratioB);
    }
  }

  return result;
}

internal Quatf32 quatf32_cubic_hermit_spline(Quatf32 q1, Quatf32 outTangent1, Quatf32 q2, Quatf32 inTangent2, f32 t) {
  // Calculate quaternion cubic spline interpolation using Cubic Hermite Spline algorithm
  // as described in the GLTF 2.0 specification: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic
  f32 t2 = t*t;
  f32 t3 = t2*t;
  f32 h00 = 2*t3 - 3*t2 + 1;
  f32 h10 = t3 - 2*t2 + t;
  f32 h01 = -2*t3 + 3*t2;
  f32 h11 = t3 - t2;

  Quatf32 p0 = quatf32_scale(q1, h00);
  Quatf32 m0 = quatf32_scale(outTangent1, h10);
  Quatf32 p1 = quatf32_scale(q2, h01);
  Quatf32 m1 = quatf32_scale(inTangent2, h11);
  Quatf32 result = { 0 };

  result = quatf32_add(p0, m0);
  result = quatf32_add(result, p1);
  result = quatf32_add(result, m1);
  result = quatf32_normalize(result);

  return result;
}

internal Quatf32 quatf32_from_vec3f32_to_vec3f32(Vec3f32 from, Vec3f32 to) {
  Quatf32 result = { 0 };

  f32 cos2Theta = (from.x*to.x + from.y*to.y + from.z*to.z);    // Vector3DotProduct(from, to)
  Vec3f32 cross = { from.y*to.z - from.z*to.y, from.z*to.x - from.x*to.z, from.x*to.y - from.y*to.x }; // Vector3CrossProduct(from, to)

  result.x = cross.x;
  result.y = cross.y;
  result.z = cross.z;
  result.w = 1.0f + cos2Theta;

  // QuaternionNormalize(q);
  // NOTE: Normalize to essentially nlerp the original and identity to 0.5
  Quatf32 q = result;
  f32 length = sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
  if (length == 0.0f) {
    length = 1.0f;
  }
  f32 ilength = 1.0f/length;

  result.x = q.x*ilength;
  result.y = q.y*ilength;
  result.z = q.z*ilength;
  result.w = q.w*ilength;

  return result;
}

internal Quatf32 quatf32_from_mat4f32(Mat4f32 mat) {
  Quatf32 result = { 0 };

  f32 fourWSquaredMinus1 = mat.m0  + mat.m5 + mat.m10;
  f32 fourXSquaredMinus1 = mat.m0  - mat.m5 - mat.m10;
  f32 fourYSquaredMinus1 = mat.m5  - mat.m0 - mat.m10;
  f32 fourZSquaredMinus1 = mat.m10 - mat.m0 - mat.m5;

  int biggestIndex = 0;
  f32 fourBiggestSquaredMinus1 = fourWSquaredMinus1;

  if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
    fourBiggestSquaredMinus1 = fourXSquaredMinus1;
    biggestIndex = 1;
  }

  if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
    fourBiggestSquaredMinus1 = fourYSquaredMinus1;
    biggestIndex = 2;
  }

  if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
    fourBiggestSquaredMinus1 = fourZSquaredMinus1;
    biggestIndex = 3;
  }

  f32 biggestVal = sqrtf(fourBiggestSquaredMinus1 + 1.0f)*0.5f;
  f32 mult = 0.25f/biggestVal;

  switch (biggestIndex) {
    case 0: {
      result.w = biggestVal;
      result.x = (mat.m6 - mat.m9)*mult;
      result.y = (mat.m8 - mat.m2)*mult;
      result.z = (mat.m1 - mat.m4)*mult;
    } break;
    case 1: {
      result.x = biggestVal;
      result.w = (mat.m6 - mat.m9)*mult;
      result.y = (mat.m1 + mat.m4)*mult;
      result.z = (mat.m8 + mat.m2)*mult;
    } break;
    case 2: {
      result.y = biggestVal;
      result.w = (mat.m8 - mat.m2)*mult;
      result.x = (mat.m1 + mat.m4)*mult;
      result.z = (mat.m6 + mat.m9)*mult;
    } break;
    case 3: {
      result.z = biggestVal;
      result.w = (mat.m1 - mat.m4)*mult;
      result.x = (mat.m8 + mat.m2)*mult;
      result.y = (mat.m6 + mat.m9)*mult;
    } break;
  }

  return result;
}

internal Quatf32 quatf32_from_axis_angle(Vec3f32 axis, f32 angle) {
  Quatf32 result = { 0.0f, 0.0f, 0.0f, 1.0f };
  f32 axisLength = sqrtf(axis.x*axis.x + axis.y*axis.y + axis.z*axis.z);

  if (axisLength != 0.0f) {
    angle *= 0.5f;

    f32 length = 0.0f;
    f32 ilength = 0.0f;

    // vec3f32_normalize
    length = axisLength;
    if (length == 0.0f) {
      length = 1.0f;
    }
    ilength = 1.0f/length;
    axis.x *= ilength;
    axis.y *= ilength;
    axis.z *= ilength;

    f32 sinres = sinf(angle);
    f32 cosres = cosf(angle);

    result.x = axis.x*sinres;
    result.y = axis.y*sinres;
    result.z = axis.z*sinres;
    result.w = cosres;

    // quatf32_normalize
    Quatf32 q = result;
    length = sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
    if (length == 0.0f) {
      length = 1.0f;
    }
    ilength = 1.0f/length;
    result.x = q.x*ilength;
    result.y = q.y*ilength;
    result.z = q.z*ilength;
    result.w = q.w*ilength;
  }

  return result;
}

internal Quatf32 quatf32_from_basis(Vec3f32 right, Vec3f32 up, Vec3f32 forward) {
  f32 m00 = right.x,  m01 = up.x,  m02 = forward.x;
  f32 m10 = right.y,  m11 = up.y,  m12 = forward.y;
  f32 m20 = right.z,  m21 = up.z,  m22 = forward.z;

  f32 trace = m00 + m11 + m22;
  Quatf32 q;

  if (trace > 0.0f) {
    f32 s = sqrtf(trace + 1.0f) * 2.0f;
    q.w = 0.25f * s;
    q.x = (m21 - m12) / s;
    q.y = (m02 - m20) / s;
    q.z = (m10 - m01) / s;
  } else if (m00 > m11 && m00 > m22) {
    f32 s = sqrtf(1.0f + m00 - m11 - m22) * 2.0f;
    q.w = (m21 - m12) / s;
    q.x = 0.25f * s;
    q.y = (m01 + m10) / s;
    q.z = (m02 + m20) / s;
  } else if (m11 > m22) {
    f32 s = sqrtf(1.0f + m11 - m00 - m22) * 2.0f;
    q.w = (m02 - m20) / s;
    q.x = (m01 + m10) / s;
    q.y = 0.25f * s;
    q.z = (m12 + m21) / s;
  } else {
    f32 s = sqrtf(1.0f + m22 - m00 - m11) * 2.0f;
    q.w = (m10 - m01) / s;
    q.x = (m02 + m20) / s;
    q.y = (m12 + m21) / s;
    q.z = 0.25f * s;
  }

  return q;
}

internal void axis_angle_from_quatf32(Quatf32 q, Vec3f32 *axis, f32 *angle) {
  if (f32_abs(q.w) > 1.0f) {
    f32 length = sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
    if (length == 0.0f) {
      length = 1.0f;
    }

    f32 ilength = 1.0f/length;
    q.x = q.x*ilength;
    q.y = q.y*ilength;
    q.z = q.z*ilength;
    q.w = q.w*ilength;
  }

  Vec3f32 resAxis = { 0.0f, 0.0f, 0.0f };
  f32 resAngle = 2.0f*acosf(q.w);
  f32 den = sqrtf(1.0f - q.w*q.w);


  if (den > EPSILON) {
    resAxis.x = q.x/den;
    resAxis.y = q.y/den;
    resAxis.z = q.z/den;
  } else {
    // This occurs when the angle is zero.
    // Not a problem: just set an arbitrary normalized axis.
    resAxis.x = 1.0f;
  }

  *axis  = resAxis;
  *angle = resAngle;
}

internal Quatf32 quatf32_from_euler(f32 pitch, f32 yaw, f32 roll) {
  Quatf32 result = { 0 };

  f32 x0 = cosf(pitch*0.5f);
  f32 x1 = sinf(pitch*0.5f);
  f32 y0 = cosf(yaw*0.5f);
  f32 y1 = sinf(yaw*0.5f);
  f32 z0 = cosf(roll*0.5f);
  f32 z1 = sinf(roll*0.5f);

  result.x = x1*y0*z0 - x0*y1*z1;
  result.y = x0*y1*z0 + x1*y0*z1;
  result.z = x0*y0*z1 - x1*y1*z0;
  result.w = x0*y0*z0 + x1*y1*z1;

  return result;
}

internal void euler_from_quatf32(Quatf32 q, f32* pitch, f32* yaw, f32* roll) {
  // Roll (x-axis rotation)
  f32 x0 = 2.0f*(q.w*q.x + q.y*q.z);
  f32 x1 = 1.0f - 2.0f*(q.x*q.x + q.y*q.y);
  *pitch = atan2f(x0, x1);

  // Pitch (y-axis rotation)
  f32 y0 = 2.0f*(q.w*q.y - q.z*q.x);
  y0 = y0 > 1.0f ? 1.0f : y0;
  y0 = y0 < -1.0f ? -1.0f : y0;
  *yaw = asinf(y0);

  // Yaw (z-axis rotation)
  f32 z0 = 2.0f*(q.w*q.z + q.x*q.y);
  f32 z1 = 1.0f - 2.0f*(q.y*q.y + q.z*q.z);
  *roll = atan2f(z0, z1);
}

internal Quatf32 quatf32_mul_mat4f32(Quatf32 q, Mat4f32 mat) {
  Quatf32 result = { 0 };

  result.x = mat.m0*q.x + mat.m4*q.y + mat.m8*q.z + mat.m12*q.w;
  result.y = mat.m1*q.x + mat.m5*q.y + mat.m9*q.z + mat.m13*q.w;
  result.z = mat.m2*q.x + mat.m6*q.y + mat.m10*q.z + mat.m14*q.w;
  result.w = mat.m3*q.x + mat.m7*q.y + mat.m11*q.z + mat.m15*q.w;

  return result;
}

internal b32 quatf32_equals(Quatf32 p, Quatf32 q) {

  b32 result = (((f32_abs(p.x - q.x)) <= (EPSILON*fmaxf(1.0f, fmaxf(f32_abs(p.x), f32_abs(q.x))))) &&
                ((f32_abs(p.y - q.y)) <= (EPSILON*fmaxf(1.0f, fmaxf(f32_abs(p.y), f32_abs(q.y))))) &&
                ((f32_abs(p.z - q.z)) <= (EPSILON*fmaxf(1.0f, fmaxf(f32_abs(p.z), f32_abs(q.z))))) &&
                ((f32_abs(p.w - q.w)) <= (EPSILON*fmaxf(1.0f, fmaxf(f32_abs(p.w), f32_abs(q.w)))))) ||
                (((f32_abs(p.x + q.x)) <= (EPSILON*fmaxf(1.0f, fmaxf(f32_abs(p.x), f32_abs(q.x))))) &&
                ((f32_abs(p.y + q.y)) <= (EPSILON*fmaxf(1.0f, fmaxf(f32_abs(p.y), f32_abs(q.y))))) &&
                ((f32_abs(p.z + q.z)) <= (EPSILON*fmaxf(1.0f, fmaxf(f32_abs(p.z), f32_abs(q.z))))) &&
                ((f32_abs(p.w + q.w)) <= (EPSILON*fmaxf(1.0f, fmaxf(f32_abs(p.w), f32_abs(q.w))))));

  return result;
}

internal Vec3f32 quatf32_rotate_vec3f32(Quatf32 q, Vec3f32 v) {
  Quatf32 q_norm = quatf32_normalize(q);
  Quatf32 v_q = {0.0f, v.x, v.y, v.z};
  Quatf32 q_conj = quatf32_invert(q_norm);
  Quatf32 temp = quatf32_multiply(q_norm, v_q);
  Quatf32 result = quatf32_multiply(temp, q_conj);
  return (Vec3f32){result.x, result.y, result.z};
}

internal Quatf32 quatf32_conjugate(Quatf32 q) {
  return (Quatf32){q.w, -q.x, -q.y, -q.z};
}

internal f32 quatf32_dot(Quatf32 q1, Quatf32 q2) {
  return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

internal void vec2f32_print(Vec2f32 v, const char8 *label) {
  printf("%s: Vec2f32\n", label);
  printf("  x: %.6f\n", v.x);
  printf("  y: %.6f\n", v.y);
}

internal void vec3f32_print(Vec3f32 v, const char8 *label) {
  printf("%s: Vec3f32\n", label);
  printf("  x: %.6f\n", v.x);
  printf("  y: %.6f\n", v.y);
  printf("  z: %.6f\n", v.z);
}

internal void vec4f32_print(Vec4f32 v, const char8 *label) {
  printf("%s: Vec4f32\n", label);
  printf("  x: %.6f\n", v.x);
  printf("  y: %.6f\n", v.y);
  printf("  z: %.6f\n", v.z);
  printf("  w: %.6f\n", v.w);
}

internal void mat4f32_print(Mat4f32 m, const char8 *label) {
  printf("%s: Mat4f32\n", label);
  for (int row = 0; row < 4; row++) {
    printf("  ");
    for (int col = 0; col < 4; col++) {
      printf("%.6f ", m.data[col][row]);
    }
    printf("\n");
  }
}

internal void quatf32_print(Quatf32 q, const char8 *label) {
  printf("%s: Quatf32\n", label);
  printf("  x: %.6f\n", q.x);
  printf("  y: %.6f\n", q.y);
  printf("  z: %.6f\n", q.z);
  printf("  w: %.6f\n", q.w);
}

internal void transformf32_print(Transformf32 t, const char8 *label) {
  printf("%s: Transformf32\n", label);
  vec3f32_print(t.translation, "  translation");
  quatf32_print(t.rotation, "  rotation");
  vec3f32_print(t.scale, "  scale");
}