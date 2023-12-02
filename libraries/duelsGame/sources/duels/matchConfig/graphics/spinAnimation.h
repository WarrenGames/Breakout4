#ifndef SPIN_ANIMATION_H
#define SPIN_ANIMATION_H

#include "texturing/texturesCombo.h"
#include "time/accurateTime.h"
#include <vector>

struct AppLogFiles;

class SpinAnim
{
private:
	bool isLoadingPerfect;
	std::vector< TextureCombo > spinTextures;
	std::size_t index;
	AccurateTimeDelay delay;

public:
	explicit SpinAnim(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	~SpinAnim() = default;
	SpinAnim( const SpinAnim& ) = delete;
	SpinAnim& operator= ( const SpinAnim& ) = delete;
	SpinAnim( SpinAnim&& ) = default;
	SpinAnim& operator= ( SpinAnim&& ) = default;
	
	operator bool () const;
	void update();
	void drawSpin(sdl2::RendererWindow& rndWnd, const Offset& pos);
};

#endif //SPIN_ANIMATION_H