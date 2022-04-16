#ifndef SIMPLE_CC
#define SIMPLE_CC

#include "tracker.h"

class Simple
{
    public:
        Simple() : Simple{0} { }

        Simple(double n) : m_number{n}
        {
            s_tracker.add_instance();
            s_tracker.add_memory(sizeof(Simple));
        }

        ~Simple()
        {
            s_tracker.remove_instance();
            s_tracker.remove_memory(sizeof(Simple));
        }

        double number() const
        {
            return 0;
        }

        static const Tracker & tracker()
        {
            return s_tracker;
        }

    private:
        double m_number;
        static inline Tracker s_tracker{};
};

#endif