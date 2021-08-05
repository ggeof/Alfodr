#ifndef __INTERVAL_H__
#define __INTERVAL_H__

#include <exception>
#include <algorithm>

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
		T min; /*! Value minimum of the interval*/
		T max; /*! Value maximum of the interval*/


		/*!
		 *  @brief Construct a new Interval with not value
		 */		
		Interval() {
			init = false;
		}

		/*!
		 *  @brief Construct a new Interval with a same value for the min and max
		 *
		 *      @param
		 */
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

		inline void decreaseTo(T _val) {
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

		inline void decreaseOf(T _val) {
			if (init == false) throw IntervalNotInitialized();
			min += _val;
			max -= _val;

			if (min > max)
				std::swap(min, max);
		}

		inline void increaseTo(T _val) {
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

		inline void increaseOf(T _val) {
			if (init == false) throw IntervalNotInitialized();
			min -= _val;
			max += _val;

			if (min > max)
				std::swap(min, max);
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