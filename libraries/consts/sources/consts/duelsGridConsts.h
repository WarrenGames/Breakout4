#ifndef DUELS_GRID_CONSTS_H
#define DUELS_GRID_CONSTS_H

#include <cstddef>

namespace duels{

	constexpr std::size_t GridWidth = 20;
	constexpr std::size_t GridHeight = 15;

	namespace bricks{
		namespace index{
			enum{ 
				NoBrick,
				Rim,
				Tough,
				Pot,
				Max };
		}
		namespace rim{
			enum{ 	
				Blue,
				Red,
				Max };
		}
		namespace tough{
			enum{
				X4,
				Tough1,
				Tough2,
				Tough3, 
				Max };
			}
		namespace pot{
			enum{
				PotTopLeft,
				PotTopRight,
				PotBottomLeft,
				PotBottomRight,
				Max };
		}
	}
}

#endif //DUELS_GRID_CONSTS_H