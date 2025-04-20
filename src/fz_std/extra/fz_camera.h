#ifndef FZ_CAMERA_H
#define FZ_CAMERA_H

#define WORLD_UP      vec3f32(0.0f, 1.0f,  0.0f)
#define WORLD_RIGHT   vec3f32(1.0f, 0.0f,  0.0f)
#define WORLD_FORWARD vec3f32(0.0f, 0.0f, -1.0f)

typedef enum Camera_Mode {
  CameraMode_Select,
  CameraMode_Fly,
  CameraMode_Disabled
} Camera_Mode;

typedef enum Camera_Movement {
  CameraMovement_Front,
  CameraMovement_Back,
  CameraMovement_Right,
  CameraMovement_Left,
  CameraMovement_Up,
  CameraMovement_Down
} Camera_Movement;

typedef struct Camera {
  Vec3f32 position;
  Quatf32 orientation;
  f32 fov;
  Camera_Mode mode;
} Camera;

internal void    camera_init(Camera* camera);
internal void    camera_update(Camera* camera, f32 delta_time);
internal Vec3f32 camera_get_forward(Camera* camera);
internal Vec3f32 camera_get_right(Camera* camera);
internal Vec3f32 camera_get_up(Camera* camera);
internal Mat4f32 camera_get_view_matrix(Camera* camera);
internal void    camera_look_at(Camera* camera, Vec3f32 target);
internal void    camera_set_euler(Camera* camera, f32 pitch, f32 yaw, f32 roll);

#endif // FZ_CAMERA_H