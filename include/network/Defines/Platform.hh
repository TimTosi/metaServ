//
// Platform.hh for Platform in /home/tosi_t//Prog/C++/BomberMan/Network/Tests/BombermanNetwork/inc
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Wed May 15 22:37:50 2013 timothee tosi
// Last update Wed May 15 22:42:31 2013 timothee tosi
//

#ifndef			PLATFORM_HH_
# define		PLATFORM_HH_

# define		LINUX		1
# define		APPLE		2
# define		WINDOWS		3

# if defined(_WIN32)
#  define		PLATFORM	WINDOWS
# elif defined(__APPLE__)
#  define		PLATFORM	APPLE
# else
#  define		PLATFORM	LINUX
# endif

#endif			/* !PLATFORM_HH_ */
