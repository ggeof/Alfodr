#ifndef __TYPE_H__
#define __TYPE_H__

#include "Types/Interval.h"
#include "Types/Parameter.h"
#include "Types/Geometry/Geometry.h"

#include <memory>

#define UNUSED(x) (void)(x);

namespace Alfodr
{
	typedef float ms; /*!< Millisecondes >!*/


	/**
	 * @brief Une classe singleton d'une classe T permet d'utiliser une seule même référence de la classe. La classe T est ainsi définit une unique fois mais appelé plusieurs fois 
	 * 
	 * @warning une fonction prenant utilisant un singleton doit avoir un constructeur prenant comme argument (void *) & que la class T est friend avec Singleton
	 * 
	 * @tparam T class dont on définit le singleton
	 */
	template <typename T>
	class Singleton
	{	
		public :

			/**
			 * @brief Construct a new Singleton object
			 * 
			 * @param args Argument optionnal
			 */
			Singleton(void* args = nullptr) { if(single == nullptr) single=std::make_shared<T>(args); } 

			/**
			 * @brief Récupère l'objet simple T
			 * 
			 * @return std::shared_ptr<T> Pointeur vers T
			 */
			inline std::shared_ptr<T> value() { return single; } 
	
		private:

			static std::shared_ptr<T> single = nullptr;
	};
}


#endif // __TYPE_H__