#ifndef INC_TEMPLATE_3D_MATRIX_H
#define INC_TEMPLATE_3D_MATRIX_H

#include "matrices/matrixStructs.h"
#include <vector>
#include <cassert>
#include <utility>

template <typename T>
class MatrixTemp3D
{	
using iterator					= typename std::vector<T>::iterator;
using const_iterator			= typename std::vector<T>::const_iterator;
using reverse_iterator			= typename std::vector<T>::reverse_iterator;
using const_reverse_iterator	= typename std::vector<T>::const_reverse_iterator;
	
private:
	std::size_t width_;
	std::size_t height_;
	std::size_t depth_;
	std::vector<T> datas_;

public:
	MatrixTemp3D():
		width_{0},
		height_{0},
		depth_{0}
	{
		
	}
	
	MatrixTemp3D(const Coord3D& size):
		width_{size.width},
		height_{size.height},
		depth_{size.depth},
		datas_( size.width * size.height * size.depth )
	{
		
	}

	MatrixTemp3D(std::size_t width, std::size_t height, std::size_t depth):
		width_{width}, 
		height_{height}, 
		depth_{depth}, 
		datas_(width * height * depth)
	{
		
	}
	
	MatrixTemp3D( const MatrixTemp3D& ) = default;
	
	MatrixTemp3D& operator= ( const MatrixTemp3D& ) = default;
	
	MatrixTemp3D( MatrixTemp3D&& toMove) noexcept:
		width_{ std::exchange( toMove.width_, 0 ) },
		height_{ std::exchange( toMove.height_, 0 ) },
		depth_{ std::exchange( toMove.depth_, 0 ) },
		datas_{ std::move( toMove.datas_ ) }
	{
		
	}

	MatrixTemp3D& operator= ( MatrixTemp3D&& toMove ) noexcept
	{
		width_ = std::exchange( toMove.width_, 0 );
		height_ = std::exchange( toMove.height_, 0 );
		depth_ = std::exchange( toMove.depth_, 0 );
		datas_ = std::move( toMove.datas_ );
		return *this;
	}
	
	void resize(const Coord3D& size)
	{
		width_ = size.width;
		height_ = size.height;
		depth_ = size.depth;
		datas_.resize(size.width * size.height * size.depth);
	}

	const T & operator()(std::size_t x, std::size_t y, std::size_t z) const
	{
		assert(x < width_);
		assert(y < height_);
		assert(z < depth_);
		return datas_[width_ * height_ * z + y * width_ + x];
	}
	
	T & operator()(std::size_t x, std::size_t y, std::size_t z)
	{
		assert(x < width_);
		assert(y < height_);
		assert(z < depth_);
		return datas_[width_*height_*z + y*width_ + x];
	}
	
	const T & operator()(const Coord3D& coord) const
	{
		assert( coord.width < width_ );
		assert( coord.height < height_ );
		assert( coord.depth < depth_ );
		return datas_[width_*height_*coord.depth + coord.height * width_ + coord.width];
	}
	
	T & operator()( const Coord3D& coord)
	{
		assert(coord.width < width_);
		assert(coord.height < height_);
		assert(coord.depth < depth_);
		return datas_[width_*height_*coord.depth + coord.height * width_ + coord.width];
	}
	
	const T & operator[]( std::size_t index) const
	{
		assert(index < datas_.size() );
		return datas_[index];
	}
	T & operator[](std::size_t index)
	{
		assert(index < datas_.size() );
		return datas_[index];
	}
	
	void fillMatrix(const T& typeTemp)
	{
		std::fill( datas_.begin(), datas_.end(), typeTemp );
	}
	
	std::size_t size() const
	{
		return datas_.size();
	}
	std::size_t width() const
	{
		return width_;
	}
	std::size_t height()const 
	{
		return height_;
	}
	std::size_t depth()const
	{
		return depth_;
	}
	
	bool isInsideBoundaries(std::size_t width, std::size_t height, std::size_t depth) const
	{
		return width < width_ 
			&& height < height_ 
			&& depth < depth_;
	}
	bool isInsideBoundaries(const Coord3D& coord) const
	{
		return coord.width < width_ 
			&& coord.height < height_ 
			&& coord.depth < depth_;
	}
	
	bool isSignedInsideBoundaries(int width, int height, int depth) const
	{
		return width >= 0 
			&& static_cast<std::size_t>(width) < width_ 
			&& height >= 0
			&& static_cast<std::size_t>(height) < height_
			&& depth >= 0
			&& static_cast<std::size_t>(depth) < depth_;
	}
	
	Coord3D getCoordSize() const
	{
		return Coord3D{width_, height_, depth_};
	}
	
	void clear()
	{
		datas_.clear();
	}

	iterator begin() 
	{ 
		return datas_.begin(); 
	}
	 
	const_iterator begin() const 
	{ 
		return datas_.cbegin(); 
	}
	
	reverse_iterator rbegin() 
	{ 
		return datas_.rbegin(); 
	}
	
	const_reverse_iterator rbegin() const 
	{ 
		return datas_.crbegin(); 
	}
   
	iterator end() 
	{ 
		return datas_.end(); 
	}
  
	const_iterator end() const 
	{ 
		return datas_.cend(); 
	}
   
	reverse_iterator rend() 
	{ 
		return datas_.rend(); 
	}
	 
	const_reverse_iterator rend() const
	{ 
		return datas_.crend(); 
	}
};


#endif // INC_TEMPLATE_3D_MATRIX_H

