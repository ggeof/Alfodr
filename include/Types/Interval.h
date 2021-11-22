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

		/**
		 * @brief Construct a new Interval object
		 * 
		 * @param val1 Value of a bounded 
		 * @param val2 Value of the other bounded
		 */
		Interval(T val1, T val2) {
			min = std::min(val1, val2); 
			max = std::max(val1, val2);
			init = true;
		}


		/**
		 * @brief clear the interval 
		 * 
		 */
		inline void reinit() {
			init = false;
		}

		/**
		 * @brief Set the born of interval
		 * 
		 * @param val1 Value of a bounded  
		 * @param val2 Value of the other bounded
		 */
		inline void set(T _val1, T _val2) {
			min = std::min(_val1, _val2);
			max = std::max(_val1, _val2);
			init = true;
		}

	
		inline void decreaseTo(Interval<T> interval) {
			if(interval.init == false) throw IntervalNotInitialized();

			if (init == false)
			{
				min = interval.min;
				max = interval.max;
				init = true;
			}
			else
			{
				min = std::max(min, interval.min);
				max = std::min(max, interval.max);
			}
		}

		inline void decreaseOf(T _val) {
			if (init == false) throw IntervalNotInitialized();
			min += _val;
			max -= _val;

			if (min > max)
				std::swap(min, max);
		}

		inline void increaseTo(Interval<T> interval) {
			if(interval.init == false) throw IntervalNotInitialized();

			if (init == false)
			{
				min = interval.min;
				max = interval.max;
				init = true;
			}
			else
			{
				min = std::min(min, interval.min);
				max = std::max(max, interval.max);
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

		/**
		 * @brief Return the position of a value in the interval 
		 * 
		 * @param value to evaluate
		 * @return float 1 : value >= max, 0 : value <= min
		 */
		inline float positionInInterval(T value) const {
			return  std::min(1.0f,	
						float(std::max(T(0), value-min)) 
						/
						float(max - min)
					);
		}

		inline T getMin() const { return this->min; }
		inline T getMax() const { return this->max; }

		inline bool isInitialized() const { return this->init; }

	private:
		bool init = false;
		
		T min; /*! Value minimum of the interval*/
		T max; /*! Value maximum of the interval*/

	};
}

#endif // __INTERVAL_H__