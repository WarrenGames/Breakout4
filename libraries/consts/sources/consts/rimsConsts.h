#ifndef ONE_PLAYER_RIMS_CONSTS_H
#define ONE_PLAYER_RIMS_CONSTS_H

namespace rims{

enum{ LeftRims, RightRims, RimSideNum };

enum{ RimNullState = -1, Remove1stRim = 0, Remove2ndRim = 1, Remove3rdRim = 2, RemoveMax = 3};

enum{ RimIsStatic, RimGoesDown, RimGoesUp };

constexpr int FirstRimBonus = 400;
constexpr int SecondRimBonus = 800;
constexpr int ThirdRimBonus = 1600;
constexpr int LatterRimBonus = 400; 

enum : std::size_t {
	Points1stRow,
	Points2ndRow,
	Points3rdRow,
	PointsDefault,
	PointsRowMax
};

}

#endif //ONE_PLAYER_RIMS_CONSTS_H