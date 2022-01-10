#pragma once

#include <list>
#include "../../include/action/wait.hpp"
#include "../../include/action/action.hpp"

namespace mouse_inject
{
  using action_chain_t = std::list<action*>;

  class action_chain :
    public action
  {
    public:
      action_chain() = default;

      action_chain(const action_chain& other)
      {
        action_chain_t::const_iterator it = other.chain_.begin();
        for ( ; it != other.chain_.end(); ++it )
          chain_.push_back((*it)->clone());
      }

      ~action_chain()
      {
        for ( auto it : chain_ )
          ::delete(it);
      }

      virtual action* clone() const override
      {
        return new action_chain(*this);
      }

      action_chain& join(action_chain& other)
      {
        chain_.push_back(other.clone());
        return *this;
      }

      action_chain& press_button(const char* btn)
      {
        chain_.push_back(new mouse_press(btn));
        return *this;
      }

      action_chain& release_button(const char* btn)
      {
        chain_.push_back(new mouse_release(btn));
        return *this;
      }

      action_chain& move(int dx, int dy)
      {
        chain_.push_back(new mouse_relative_motion(dx, dy));
        return *this;
      }

      action_chain& move_to(int x, int y)
      {
        chain_.push_back(new mouse_absolute_motion(x, y));
        return *this;
      }

      action_chain& wheel_up()
      {
        chain_.push_back(new mouse_wheel_up());
        return *this;
      }

      action_chain& wheel_down()
      {
        chain_.push_back(new mouse_wheel_down());
        return *this;
      }

      action_chain& wait(unsigned ms)
      {
        chain_.push_back(new wait_action(ms));
        return *this;
      }

      virtual void perform() const override
      {
        action_chain_t::const_iterator it = chain_.begin();
        for ( ; it != chain_.end(); ++it )
          (*it)->perform();
      }

    private:
      action_chain_t chain_;
  };
}