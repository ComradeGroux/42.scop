#pragma once

class Position {
	private:
		float	_x;
		float	_y;
		float	_z;
		float	_w;

	public:
		Position(void);
		Position(float x, float y, float z);
		Position(float x, float y, float z, float w);
		Position(const Position& src);
		Position& operator=(const Position &src);
		~Position(void);

		float	getX(void) const;
        void    setX(float x);
		
        float	getY(void) const;
        void    setY(float y);
		
        float	getZ(void) const;
        void    setZ(float z);
};
