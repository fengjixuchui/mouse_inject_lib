#pragma once

#include <windows.h>
#include "../../include/action/action_base.hpp"

namespace mouse_inject
{
  class wait_action
    : public action
  {
    public:
      wait_action(unsigned ms)
        : ms_(ms)
      {
      }

      virtual action* clone() const override
      {
        return new wait_action(ms_);
      }

      virtual void perform() const override
      {
        ::Sleep(ms_);
      }

    private:
      unsigned ms_;
  };
}