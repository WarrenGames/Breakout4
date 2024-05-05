#ifndef OBJECT_MOVE_H
#define OBJECT_MOVE_H

#include "customTypes/positionTypes.h"

namespace spriteMove{

class ObjectMoving
{
private:
	AccurCoords position;
	AccurCoords on_axis_speed;
	double globalSpeed;
	Offset dirVectors;

public:
	explicit ObjectMoving();
	explicit ObjectMoving(const Offset& startingPosition);
	explicit ObjectMoving(const AccurCoords& startCoords, double newSpeed, const Offset& newDirVectors);
	~ObjectMoving() = default;
	ObjectMoving( const ObjectMoving& ) = default;
	ObjectMoving& operator= ( const ObjectMoving& ) = default;
	ObjectMoving( ObjectMoving&& ) = default;
	ObjectMoving& operator= ( ObjectMoving&& ) = default;
	
	void adjust_x_speed();
	void adjust_y_speed();
	void set_x_vector(int new_x_norm);
	void set_y_vector(int new_y_norm);
	void setBothVectors(const Offset& newVectors);
	void setSpeed(double newGlobalSpeed);
	void incrementSpeed(double increment);
	double getSpeed() const;
	int get_x_position() const;
	int get_y_position() const;
	const AccurCoords& getPosition() const;
	Offset getOffsetPosition() const;
	int get_x_norm() const;
	int get_y_norm() const;
	void reverse_x_vector();
	void reverse_y_vector();
	void moveObject();
	void setPosition(const Offset& newPosition);
	void setPosition(const AccurCoords& newPosition);
	void add_to_xpos(double x_add);
	void add_to_ypos(double y_add);
	void set_x_position(double new_x_position);
	void set_y_position(double new_y_position);
	void orientToAGivenObject(const ObjectMoving& distantObject);
	void stopObject();
};

void giveObjectNewDirection(ObjectMoving& move, const Offset& newOffset);

}

#endif //OBJECT_MOVE_H