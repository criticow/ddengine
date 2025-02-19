#pragma once

#include "../ddenginepch.hpp"
#include "window.hpp"

#define MOUSE_BUTTON_LEFT "button_mouse_left"
#define MOUSE_BUTTON_RIGHT "button_mouse_right"
#define ACTION_LEFT "action_left"
#define ACTION_RIGHT "action_right"
#define ACTION_UP "action_up"
#define ACTION_FORWARD "action_forward"
#define ACTION_BACKWARD "action_backward"
#define ACTION_DOWN "action_down"
#define ACTION_JUMP "action_jump"
#define ACTION_FALL "action_fall"
#define ACTION_ACCEPT "action_accept"
#define ACTION_CANCEL "action_cancel"

#define KEY_A "key_a"
#define KEY_B "key_b"
#define KEY_C "key_c"
#define KEY_D "key_d"
#define KEY_E "key_e"
#define KEY_F "key_f"
#define KEY_G "key_g"
#define KEY_H "key_h"
#define KEY_I "key_i"
#define KEY_J "key_j"
#define KEY_K "key_k"
#define KEY_L "key_l"
#define KEY_M "key_m"
#define KEY_N "key_n"
#define KEY_O "key_o"
#define KEY_P "key_p"
#define KEY_Q "key_q"
#define KEY_R "key_r"
#define KEY_S "key_s"
#define KEY_T "key_t"
#define KEY_U "key_u"
#define KEY_V "key_v"
#define KEY_W "key_w"
#define KEY_X "key_x"
#define KEY_Y "key_y"
#define KEY_Z "key_z"

#define KEY_UP "key_up"
#define KEY_DOWN "key_down"
#define KEY_LEFT "key_left"
#define KEY_RIGHT "key_right"

#define KEY_F1 "key_f1"
#define KEY_F2 "key_f2"
#define KEY_F3 "key_f3"
#define KEY_F4 "key_f4"
#define KEY_F5 "key_f5"
#define KEY_F6 "key_f6"
#define KEY_F7 "key_f7"
#define KEY_F8 "key_f8"
#define KEY_F9  "key_f9"
#define KEY_F10 "key_f10"
#define KEY_F11 "key_f11"
#define KEY_F12 "key_f12"
#define KEY_ESC "key_esc"
#define KEY_1 "key_1"
#define KEY_2 "key_2"
#define KEY_3 "key_3"
#define KEY_4 "key_4"
#define KEY_5 "key_5"
#define KEY_6 "key_6"
#define KEY_7 "key_7"
#define KEY_8 "key_8"
#define KEY_9 "key_9"

struct Action
{
  struct State
  {
    bool pressed;
    bool held;
    bool released;
  };

  enum Origin
  {
    MOUSE,
    KEYBOARD
  };

  Origin origin;
  State state;
  std::vector<int> keys;
};

class Input
{
  public:
  Input();
  void update(const Window &window);
  bool pressed(const std::string &name);
  bool held(const std::string &name);
  bool released(const std::string &name);

  void addAction(const std::string &name, Action::Origin origin, const std::vector<int> &keys);

  private:
  std::unordered_map<std::string, Action> actions;
};