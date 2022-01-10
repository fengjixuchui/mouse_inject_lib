#pragma once

#include <functional>
#include "../../include/detail/mouse.hpp"
#include "../../include/action/action_base.hpp"

namespace mouse_inject
{
  using mouse_wheel_action_callback_t = std::function<void()>;
  using mouse_btn_action_callback_t = std::function<void(const char* btn)>;
  using mouse_motion_action_callback_t = std::function<void(int x, int y)>;

  class mouse_btn_action 
    : public action
  {
    public:
      mouse_btn_action(
        mouse_btn_action_callback_t callback, 
        const char* btn
      )
        : callback_(callback), btn_(btn)
      {
      }

      virtual action* clone() const override
      {
        return new mouse_btn_action(
          callback_, 
          btn_
        );
      }

      virtual void perform() const override
      {
        callback_(btn_);
      }

    private:
      const char* btn_;
      mouse_btn_action_callback_t callback_;
  };

  struct mouse_press 
    : public mouse_btn_action
  {
    mouse_press(const char* btn)
      : mouse_btn_action(detail::press_button, btn)
    {
    }
  };

  struct mouse_release
    : public mouse_btn_action
  {
    mouse_release(const char* btn)
      : mouse_btn_action(detail::release_button, btn)
    {
    }
  };

  class mouse_motion_action 
    : public action
  {
    public:
      mouse_motion_action(
        mouse_motion_action_callback_t callback, 
        int x, 
        int y
      )
        : callback_(callback), x_(x), y_(y)
      {
      }

      virtual action* clone() const override
      {
        return new mouse_motion_action(
          callback_,
          x_,
          y_
        );
      }

      virtual void perform() const override
      {
        callback_(x_, y_);
      }

    private:
      int x_;
      int y_;
      mouse_motion_action_callback_t callback_;
  };

  struct mouse_relative_motion
    : public mouse_motion_action
  {
    mouse_relative_motion(int dx, int dy)
      : mouse_motion_action(detail::move, dx, dy)
    {
    }
  };

  struct mouse_absolute_motion
    : public mouse_motion_action
  {
    mouse_absolute_motion(int x, int y)
      : mouse_motion_action(detail::move_to, x, y)
    {
    }
  };

  class mouse_wheel_action 
    : public action
  {
    public:
      mouse_wheel_action(
        mouse_wheel_action_callback_t callback
      )
        : callback_(callback)
      {
      }

      virtual action* clone() const override
      {
        return new mouse_wheel_action(
          callback_
        );
      }

      virtual void perform() const override
      {
        callback_();
      }

    private:
      mouse_wheel_action_callback_t callback_;
  };

  struct mouse_wheel_up
    : public mouse_wheel_action
  {
    mouse_wheel_up()
      : mouse_wheel_action(detail::wheel_up)
    {
    }
  };

  struct mouse_wheel_down
    : public mouse_wheel_action
  {
    mouse_wheel_down()
      : mouse_wheel_action(detail::wheel_down)
    {
    }
  };
}