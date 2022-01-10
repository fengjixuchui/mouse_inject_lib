#pragma once

namespace mouse_inject
{
  struct action
  {
    virtual action* clone() const = 0;
    virtual void perform() const = 0;
    virtual ~action() = default;
  };
}