#include "../include/mouse_inject.hpp"

int main()
{
  mouse_inject::action_chain ac;
  ac.press_button("left button").perform();

  for ( ;; )
  {
    if ( GetAsyncKeyState(VK_ESCAPE) & 1 )
      break;

    ac.wheel_down().perform();
  }
}

