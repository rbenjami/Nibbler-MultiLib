/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesLib.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 16:40:04 by rbenjami          #+#    #+#             */
/*   Updated: 2015/03/11 19:14:02 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NcursesLib.hpp"

std::map<int, int>	NcursesLib::_colors;

NcursesLib::NcursesLib( void )
{
	return ;
}

NcursesLib::~NcursesLib( void )
{
	return ;
}

bool		NcursesLib::isCloseRequest( void ) const
{
	return ( this->_keys[ESC] );
}

bool		NcursesLib::createWindow( int height, int width, std::string title)
{
	this->_title = title;

	initscr();
	start_color();
	cbreak();
	nodelay( stdscr, true );
	keypad( stdscr, true );
	noecho();
	curs_set( 0 );
	this->_window = newwin( height, width, 0, 0 );
	wrefresh(this->_window);
	return ( true );
}

bool		NcursesLib::refreshWindow( void )
{
	wrefresh( this->_window );
	return ( true );
}

bool		NcursesLib::destroyWindow( void )
{
	delwin( this->_window );
	endwin( );
	return ( true );
}

bool		NcursesLib::clearWindow( void )
{
	// wclear(this->_window); seems to be too slow
	clear( );
	return ( true );
}

void		NcursesLib::updateKeys( void )
{
	static int keyLink[][2] =
	{
		{ESC, 27},
		{RIGHT, KEY_RIGHT},
		{LEFT, KEY_LEFT},
		{UP, KEY_UP},
		{DOWN, KEY_DOWN},
		{F1, '1'},
		{F2, '2'},
		{F3, '3'}
	};

	int ch;
	ch = getch();
	for (int i = 0; i < SIZEOF; i++)
	{
		this->_keys[i] = (keyLink[i][1] == ch);
	}
}

bool		NcursesLib::isKeyPressed( e_key key ) const
{
	return (this->_keys[key]);
}
#define COLOR 1
void		NcursesLib::drawSquare( int posX, int posY, int size, int color ) const
{
	int		r, g, b;
	int		c;
	std::map<int,int>::const_iterator it;

	if ( (it = NcursesLib::_colors.find( color ) ) == NcursesLib::_colors.end() )
	{
		c = NcursesLib::_colors.size() + 1;
		r = ( (color & 0xFF0000) >> 16 ) * 3.5;
		g = ( (color & 0x00FF00) >> 8 ) * 3.5;
		b = ( (color & 0x0000FF) ) * 3.5;
		// std::cout << r << std::endl;
		init_color( c, r, g, b );
		init_pair( c, c, c );
		NcursesLib::_colors.insert( std::pair<int,int>( color, c ) );
	}
	else
		c = it->second;

	attron(COLOR_PAIR(c));
	for (int x = 0; x < size; x++)
	{
			for (int y = 0; y < size; y++)
			{
				mvprintw(posY + y, (posX + x) * 2, "  ");
			}
	}
	attroff(COLOR_PAIR(c));
}

void		NcursesLib::drawLine( float x1, float y1, float x2, float y2, int color ) const
{
	(void)color;

	float tmp;
	if (x2 < x1)
	{
		tmp = x2;
		x2 = x1;
		x1 = tmp;
	}
	if (y2 < y1)
	{
		tmp = y2;
		y2 = y1;
		y1 = tmp;
	}
	if (y1 == y2)
	{
		for (int x = x1; x <= x2; x++)
		{
			this->drawSquare( x, y1, 1, color );
		}
	}
	else
	{
		for (int y = y1; y <= y2; y++)
		{
			this->drawSquare( x1, y, 1, color );
		}
	}

}
