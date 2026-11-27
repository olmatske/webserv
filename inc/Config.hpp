#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "ServerConfig.hpp"
# include <string>
# include <vector>

class Config
{
	private:

	std::vector<ServerConfig>	_servers;

	public:

	Config( void );
	Config( const Config& other );
	Config& operator=( const Config& other );
	~Config( void );

	void	parse( const std::string& filePath );

	//getters
	const std::vector<ServerConfig>&	getServers( void ) const;																			// -> ombilica
	const ServerConfig*					matchServer( const std::string& listenHost, int listenPort, const std::string& serverName ) const;	// -> olmatske
};

#endif
