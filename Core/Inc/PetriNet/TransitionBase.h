#pragma once

#include <any>
#include <queue>

class TransitionBase {
  private:
    int          prioriy = 0;
    unsigned int ID;

  public:
    TransitionBase(int priority, unsigned int ID)
    {
        this->prioriy = prioriy;
        this->ID      = ID;
    }
    virtual bool is_ready()     = 0;
    virtual void run()          = 0;
    virtual bool is_completed() = 0;

    int get_priority()
    {
        return this->prioriy;
    }
    unsigned int get_ID()
    {
        return this->ID;
    }
};

void queue_clear(std::queue<std::any>& q);
