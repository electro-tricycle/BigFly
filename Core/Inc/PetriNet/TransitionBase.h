#pragma once

class TransitionBase {
  private:
    int prioriy = 0;

  public:
    TransitionBase(int priority)
    {
        this->prioriy = prioriy;
    }
    virtual bool is_ready() = 0;

    virtual void run() = 0;

    int get_priority()
    {
        return this->prioriy;
    }
};