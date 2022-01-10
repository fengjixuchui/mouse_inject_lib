#pragma once
#include "../include/detail/buttons.hpp"

#define INIT_INPUT(var) \
  INPUT var; \
  ZeroMemory(&var, sizeof(INPUT)); \
  var.type = INPUT_MOUSE; 

namespace mouse_inject
{
  namespace detail
  {
    void move(
      int x, 
      int y
    )
    {
      INIT_INPUT(input);
      input.mi.dx = x;
      input.mi.dy = y;
      input.mi.dwFlags = MOUSEEVENTF_MOVE;
      SendInput(1, &input, sizeof(INPUT));
    }

    void move_to(
      int x, 
      int y
    )
    {
      auto w_screen = GetSystemMetrics(SM_CXSCREEN) - 1;
      auto h_screen = GetSystemMetrics(SM_CYSCREEN) - 1;
      auto fx = x * (65'535.0f / w_screen);
      auto fy = y * (65'535.0f / h_screen);

      INIT_INPUT(input);
      input.mi.dx = static_cast<long>(fx);
      input.mi.dy = static_cast<long>(fy);
      input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
      SendInput(1, &input, sizeof(INPUT));
    }

    void press_button(
      const char* btn
    )
    {
      INIT_INPUT(input);
      input.mi.dwFlags = detail::btns.at(btn);
      SendInput(1, &input, sizeof(INPUT));
    }

    void release_button(
      const char* btn
    )
    {
      INIT_INPUT(input);
      input.mi.dwFlags = detail::btns.at(btn);
      SendInput(1, &input, sizeof(INPUT));
    }

    void wheel_up()
    {
      INIT_INPUT(input);
      input.mi.dwFlags = MOUSEEVENTF_WHEEL;
      input.mi.mouseData = WHEEL_DELTA;
      SendInput(1, &input, sizeof(INPUT));
    }

    void wheel_down()
    {
      INIT_INPUT(input);
      input.mi.dwFlags = MOUSEEVENTF_WHEEL;
      input.mi.mouseData = static_cast<unsigned long>(-WHEEL_DELTA);
      SendInput(1, &input, sizeof(INPUT));
    }
  }
}