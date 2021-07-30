#ifndef __INTERVAL_H__
#define __INTERVAL_H__

#include <exception>

namespace Alfodr
{

    class IntervalNotInitialized : public std::exception
    {
        virtual const char* what() const throw()
        {
            return "Interval Not Initialized !";
        }
    };

    template<typename T>
    struct Interval
    {
        T min;
        T max;

        Interval() {
            init = false;
        }

        Interval(T val) {
            min = val;
            max = val;
            init = true;
        }

        Interval(T val1, T val2) {
            min = std::min(val1, val2);
            max = std::min(val1, val2);
            init = true;
        }

        inline void reinit() {
            init = false;
        }

        inline void set(T _val1, T _val2) {
            min = std::min(_val1, _val2);
            max = std::max(_val1, _val2);
        }

        inline void decrease(T _val) {
            if (init == false)
            {
                min = _val;
                max = _val;
                init = true;
            }
            else
            {
                min = std::max(min, _val);
                max = std::min(max, _val);
            }
        }


        inline void increase(T _val) {
            if (init == false)
            {
                min = _val;
                max = _val;
                init = true;
            }
            else
            {
                min = std::min(min, _val);
                max = std::max(max, _val);
            }
        }

        inline void increase(T _val1, T _val2) {
            min = std::min(_val1, _val2);
            max = std::max(_val1, _val2);
        }


        inline bool isInExclusif(T _val) {
            if (init == false) throw IntervalNotInitialized();
            return _val > min && _val < max;
        }

        inline bool isInInclusif(T _val) {
            if (init == false) throw IntervalNotInitialized();
            return _val >= min && _val <= max;
        }


        inline bool isOut(T _val) {
            if (init == false) throw IntervalNotInitialized();
            return _val < min&& _val > max;
        }

    private:
        bool init = false;
    };

}

#endif // __INTERVAL_H__