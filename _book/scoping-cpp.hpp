#ifndef SCOPING_CPP_HPP
#define SCOPING_CPP_HPP

// Declaration of the Agent class
class Agent {
public:
    int fun();
};

// Declaration of the GlobalClass class
class GlobalClass {
private:
    inline static GlobalClass * instance_ = nullptr;
    Agent agent_;
    int x_;

public:
    virtual int run();
    GlobalClass(int x) : agent_(Agent()), x_(x) {};
    static GlobalClass & get();
    int get_x();
};

// Implementation of the GlobalClass methods
inline int GlobalClass::run() {
    GlobalClass::instance_ = this;
    return agent_.fun();
};

inline GlobalClass & GlobalClass::get() {return *instance_;};
inline int GlobalClass::get_x() {return x_;};

// Implementation of the Agent method
inline int Agent::fun() {return GlobalClass::get().get_x();};

#endif