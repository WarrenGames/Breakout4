#ifndef DUELS_GRID_CONSTS_H
#define DUELS_GRID_CONSTS_H

#include <cstddef>

namespace duels{

	constexpr std::size_t GRID_WIDTH = 20;
	constexpr std::size_t GRID_HEIGHT = 15;

	namespace BRICKS{
		namespace INDEX{
			enum{ 
				NO_BRICK,
				RIM,
				TOUGH,
				POT,
				MAX };
		}
		namespace RIM{
			enum{ 	
				BLUE,
				RED,
				MAX };
		}
		namespace TOUGH{
			enum{
				X4,
				TOUGH1,
				TOUGH2,
				TOUGH3, 
				MAX };
			}
		namespace POT{
			enum{
				POT_TOP_LEFT,
				POT_TOP_RIGHT,
				POT_BOTTOM_LEFT,
				POT_BOTTOM_RIGHT,
				MAX };
		}
	}
}

#endif //DUELS_GRID_CONSTS_H