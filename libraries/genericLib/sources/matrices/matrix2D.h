#ifndef INC_TEMPLATE_2D_MATRIX_H
#define INC_TEMPLATE_2D_MATRIX_H

#include "matrices/matrixStructs.h"
#include <vector>
#include <cassert>
#include <utility>

template <typename T>
class MatrixTemp2D
{
using iterator					= typename std::vector<T>::iterator;
using const_iterator			= typename std::vector<T>::const_iterator;
using reverse_iterator			= typename std::vector<T>::reverse_iterator;
using const_reverse_iterator	= typename std::vector<T>::const_reverse_iterator;

private:
	std::size_t width_;
	std::size_t height_;
	std::vector<T> datas_;
	
public:
	explicit MatrixTemp2D():
		width_{0},
		height_{0}
	{
	
	}
	
	explicit MatrixTemp2D(const Coord2D& size):
		width_{ size.width },
		height_{ size.height },
		datas_( size.width * size.height )
	{
		
	}

	explicit MatrixTemp2D(std::size_t width, std::size_t height):
		width_{width},
		height_{height},
		datas_(width * height)
	{
		
	}
	
	MatrixTemp2D( const MatrixTemp2D& ) = default;
	
	MatrixTemp2D& operator= ( const MatrixTemp2D& ) = default;
	
	MatrixTemp2D( MatrixTemp2D&& toMove ) noexcept:
		width_{ std::exchange(toMove.width_, 0 ) },
		height_{ std::exchange(toMove.height_, 0 ) },
		datas_{ std::move( toMove.datas_ ) }
	{
		
	}
	
	MatrixTemp2D& operator= ( MatrixTemp2D&& toMove ) noexcept
	{
		width_ = std::exchange( toMove.width_, 0 );
		height_ = std::exchange( toMove.height_, 0 );
		datas_ = std::move( toMove.datas_ );
		return *this;
	}
	
	void resize(const Coord2D& size)
	{
		datas_.resize(size.width * size.height);
		width_ = size.width;
		height_ = size.height;
	}

	const T & operator()(std::size_t x, std::size_t y) const
	{
		assert( x < width_ );
		assert( y < height_ );
		return datas_[ y * width_ + x ];
	}

	T & operator()(std::size_t x, std::size_t y)
	{
		assert( x < width_ );
		assert( y < height_ );
		return datas_[ y * width_ + x ];
	}
	
	const T & operator()(const Coord2D& coord) const
	{
		assert( coord.width < width_ );
		assert( coord.height < height_ );
		return datas_[ coord.height * width_ + coord.width ];
	}
	
	T & operator()( const Coord2D& coord)
	{
		assert( coord.width < width_ );
		assert( coord.height < height_ );
		return datas_[ coord.height * width_ + coord.width ];
	}
	
	void fillMatrix(const T& typeTemp)
	{
		std::fill( datas_.begin(), datas_.end(), typeTemp );
	}
	
	void set(std::size_t width, std::size_t height, T typeTemp)
	{
		assert( width < width_ );
		assert( height < height_ );
		datas_[ height * width_ + width ] = typeTemp;
	}
	
	const T & operator[](std::size_t index) const
	{
		assert( index < datas_.size() );
		return datas_[index];
	}
	
	T & operator[](std::size_t index)
	{
		assert(index < datas_.size() );
		return datas_[index];
	}
	
	std::size_t width() const
	{
		return width_;
	}
	
	std::size_t height() const
	{
		return height_;
	}
	
	std::size_t size() const
	{
		return datas_.size();
	}
	
	bool isInsideBoundaries(std::size_t width, std::size_t height) const
	{
		return width < width_ 
			&& height < height_;
	}
	
	bool isInsideBoundaries(const Coord2D& coords) const
	{
		return coords.width < width_
			&& coords.height < height_;
	}
	
	bool isSignedInsideBoundaries(int width, int height) const
	{ 
		return width >= 0 
			&& static_cast<std::size_t>(width) < width_ 
			&& height >= 0 
			&& static_cast<std::size_t>(height) < height_;
	}
	
	void reverseDimensions()
	{
		std::size_t temp{ width_ };
		width_ = height_;
		height_ = temp;
	}
	
	Coord2D getCoordSize() const
	{
		return Coord2D{width_, height_};
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
	 
	iterator end() 
	{ 
		return datas_.end(); 
	}
  
	const_iterator end() const 
	{ 
		return datas_.cend(); 
	}
   
	reverse_iterator rbegin() 
	{ 
		return datas_.rbegin(); 
	}
   
	const_reverse_iterator rbegin() const 
	{ 
		return datas_.crbegin(); 
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

#endif // INC_TEMPLATE_2D_MATRIX_H
