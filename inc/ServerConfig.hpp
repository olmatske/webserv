#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP

# include "LocationConfig.hpp"
# include <cstddef>
# include <map>
# include <string>
# include <vector>

class ServerConfig
{
	private:

	std::string						_listenHost;
	int								_listenPort;
	std::vector<std::string>		_serverNames;
	std::size_t						_clientMaxBodySize;
	std::map<int, std::string>		_errorPages;
	std::vector<LocationConfig>		_locations;

	public:

	ServerConfig( void );
	ServerConfig( const ServerConfig& other );
	ServerConfig& operator=( const ServerConfig& other );
	~ServerConfig( void );

	//setters
	void	setListenHost( const std::string& host );
	void	setListenPort( int port );
	void	addServerName( const std::string& name );
	void	setClientMaxBodySize( std::size_t bytes );
	void	addErrorPage( int statusCode, const std::string& path );
	void	addLocation( const LocationConfig& location );

	//getters
	const std::string&					getListenHost( void ) const;					// -> ombilica, olmatske
	int									getListenPort( void ) const;					// -> ombilica, olmatske
	const std::vector<std::string>&		getServerNames( void ) const;					// -> olmatske
	std::size_t							getClientMaxBodySize( void ) const;				// -> olmatske
	const std::map<int, std::string>&	getErrorPages( void ) const;					// -> olmatske
	const std::vector<LocationConfig>&	getLocations( void ) const;						// -> olmatske

	const LocationConfig*	matchLocation( const std::string& uri ) const;				// -> olmatske
	std::string				getErrorPage( int statusCode ) const;						// -> olmatske
};

#endif
