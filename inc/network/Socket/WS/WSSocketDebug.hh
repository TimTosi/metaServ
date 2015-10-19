//
// SocketDebug.hh for SocketDebug in /home/tosi_t//Prog/R-Type/Network/inc
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Sat Oct 26 14:52:03 2013 timothee tosi
// Last update Tue Oct 29 18:59:39 2013 timothee tosi
//

#ifndef			WSSOCKETDEBUG_HH_
# define		WSSOCKETDEBUG_HH_

# include		<errno.h>

# define		RED		"\033[31m"
# define		GREEN		"\033[32m"
# define		END		"\033[0m"
# define		NONBLOCK	"The socket is nonblocking. Man errno EINPROGRESS."
# define		NOTSOCK		"The fd is not associated with a socket."
# define		COREFUSED	"No-one listening on the remote address."

inline void		giveDetails(int err)
{
  std::cerr << RED;
  switch (err)
    {
    case EACCES : ;
      break ;
    case EPERM : ;
      break ;
    case EADDRINUSE : ;
      break ;
    case EAFNOSUPPORT : ;
      break ;
    case EAGAIN : ;
      break ;
    case EALREADY : ;
      break ;
    case EBADF : ;
      break ;
    case ECONNREFUSED : std::cerr << COREFUSED;
      break ;
    case EFAULT : ;
      break ;
    case EINPROGRESS : std::cerr << NONBLOCK;
      break ;
    case EINTR : ;
      break ;
    case EISCONN : ;
      break ;
    case ENETUNREACH : ;
      break ;
    case ENOTSOCK : std::cerr << NOTSOCK;;
      break ;
    case ETIMEDOUT : ;
    default : std::cerr << "UNDEFINED ERROR.";
    break ;
    }
  std::cerr << END << std::endl;
}

inline bool		debugInit(bool test)
{
# ifdef			_DEBUG
  std::cerr << "-----------------------SOCKET INITIALISATION-----------------------"
	    << std::endl << std::endl;
  std::cerr << "SOCKET INIT: " ;
  if (test == false)
    std::cerr << RED << "FAIL" << END << std::endl;
  else
    std::cerr << GREEN << "SUCCESS" << END << std::endl;
# endif			// !_DEBUG
  return (test);
}

inline bool		debugBind(bool test)
{
# ifdef			_DEBUG
  std::cerr << "SOCKET BIND: " ;
  if (test == false)
    std::cerr << RED << "FAIL" << END << std::endl;
  else
    std::cerr << GREEN << "SUCCESS" << END << std::endl;
# endif			// !_DEBUG
  return (test);
}

inline bool		debugSettings(bool test)
{
# ifdef			_DEBUG
  std::cerr << "SOCKET SETTINGS: " ;
  if (test == false)
    std::cerr << RED << "FAIL" << END << std::endl;
  else
    std::cerr << GREEN << "SUCCESS" << END << std::endl;
# endif			// !_DEBUG
  return (test);
}

inline bool		debugConnect(bool test)
{
# ifdef			_DEBUG
  int			err = errno;
  std::cerr << "SOCKET CONNECT: " ;
  if (test == false)
    {
      std::cerr << RED << "FAIL" << END << std::endl;
      std::cerr << "WHAT : ";
      giveDetails(err);
    }
  else
    std::cerr << GREEN << "SUCCESS" << END << std::endl;
  std::cerr << "-------------------------SOCKET PROCESSING-------------------------"
	    << std::endl << std::endl;
# endif			// !_DEBUG
  return (test);
}

inline bool		debugListen(int test)
{
# ifdef			_DEBUG
	int			err = errno;
	std::cerr << "SOCKET LISTEN: ";
	if (test < 0)
	{
		std::cerr << RED << "FAIL" << END << std::endl;
		std::cerr << "WHAT : ";
		giveDetails(err);
		return (false);
	}
	std::cerr << GREEN << "SUCCESS" << END << std::endl;
# endif			// !_DEBUG
	return (true);
}

inline int		debugAccept(int test)
{
	return (test);
}

inline bool		debugSend(bool test, APacket & packet)
{
  (void)packet;
# ifdef			_DEBUG
  std::cerr << "SEND MESSAGE: " ;
  if (test == false)
    std::cerr << RED << "FAIL" << END << std::endl;
  else
    {
      std::cerr << GREEN << "SUCCESS" << END << std::endl;
      std::cerr << "MESSAGE SENT : " << packet.getData()
		<< std::endl << std::endl;
    }
# endif			// !_DEBUG
  return (test);
}

#endif			// !WSSOCKETDEBUG_HH_
