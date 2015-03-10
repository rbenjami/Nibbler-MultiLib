#ifndef WALL_HPP
# define WALL_HPP
# include "../../core/AComponent.hpp"
# include "../../utils/vec.hpp"
# include <stdlib.h>

class Wall : public AComponent
{
public:
	// Wall( void );
	Wall( float x1, float y1, float x2, float y2 );
	~Wall( void );
	virtual int					update( ILib const * lib, double delta );
	virtual int					render( ILib const * lib ) const;

	void						setPos2(Vec2i pos);
	Vec2i						getPos2(void);

private:
	Vec2i	_pos2;
};

#endif
