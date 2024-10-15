#include "levelComponents/rims/rimsPast.h"
#include "consts/rimsConsts.h"
#include <cassert>

OnePlayerRimsPast::OnePlayerRimsPast():
	hasBorderBeenActivated( rims::RemoveMax, false )
{
	
}

std::size_t OnePlayerRimsPast::size() const
{
	return hasBorderBeenActivated.size();
}

void OnePlayerRimsPast::setBorderToActiveOne(std::size_t borderNumber)
{
	assert( borderNumber < hasBorderBeenActivated.size() );
	hasBorderBeenActivated[borderNumber] = true;
}

bool OnePlayerRimsPast::wasBorderAlreadyActivated(std::size_t borderNumber) const
{
	assert( borderNumber < hasBorderBeenActivated.size() );
	return hasBorderBeenActivated[borderNumber];
}