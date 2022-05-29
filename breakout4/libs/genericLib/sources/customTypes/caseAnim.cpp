#include "customTypes/caseAnim.h"
#include <cassert>

CaseAnim::CaseAnim():
	animIndex{0},
	currentFrame{0}
{

}

CaseAnim::CaseAnim(unsigned newAnimIndex, unsigned newStartFrame):
	animIndex{newAnimIndex},
	currentFrame{newStartFrame}
{
	
}

unsigned CaseAnim::getModifiedIndex() const
{
	if( animIndex > 0 )
		return animIndex - 1;
	else
		return 0;
}
