#pragma once

#include <map>
#include <windows.h>

namespace mouse_inject
{
  namespace detail
  {
    using btns_t = std::map<const char*, int>;

    btns_t btns
    {
      { "left button",   MOUSEEVENTF_LEFTDOWN   },
      { "middle button", MOUSEEVENTF_MIDDLEDOWN },
      { "right button",  MOUSEEVENTF_RIGHTDOWN  }
    };
  }
}