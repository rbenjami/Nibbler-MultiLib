
#include "LimitSide.hpp"

#warning "TODO: copilian form for LimitSide"
LimitSide::LimitSide( Vec2i const & a, Vec2i const & b )
{
	setPos( a );
	setPos2( b );
	return ;
}

LimitSide::~LimitSide( void )
{
	return ;
}

int			LimitSide::update( ILib const * lib, double delta )
{
	(void)lib;
	(void)delta;
	return ( true );
}

int			LimitSide::render( ILib const * lib ) const
{
	lib->drawLine( this->_pos.getX(), this->_pos.getY(), this->_pos2.getX(), this->_pos2.getY() );
	return ( true );
}
