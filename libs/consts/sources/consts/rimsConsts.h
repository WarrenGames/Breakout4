#ifndef ONE_PLAYER_RIMS_CONSTS_H
#define ONE_PLAYER_RIMS_CONSTS_H

namespace rims{

enum{ LeftRims, RightRims, RimSideNum };

enum{ RimNullState = -1, Remove1stRim = 0, Remove2ndRim = 1, Remove3rdRim = 2, RemoveMax = 3};

enum{ RimIsStatic, RimGoesDown, RimGoesUp };

}

#endif //ONE_PLAYER_RIMS_CONSTS_H