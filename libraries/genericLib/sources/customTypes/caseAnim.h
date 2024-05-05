#ifndef CASE_ANIM_STRUCT_TYPE_H
#define CASE_ANIM_STRUCT_TYPE_H

#include "time/accurateTime.h"

struct CaseAnim
{
	unsigned animIndex;
	unsigned currentFrame;
	AccurateTimeDelay delay;
	
	explicit CaseAnim();
	explicit CaseAnim(unsigned newAnimIndex, unsigned newStartFrame);
	CaseAnim( const CaseAnim& ) = default;
	CaseAnim& operator= ( const CaseAnim& ) = default;
	CaseAnim( CaseAnim&& ) = default;
	CaseAnim& operator= ( CaseAnim&& ) = default;
	
	unsigned getModifiedIndex() const;
};

#endif //CASE_ANIM_STRUCT_TYPE_H