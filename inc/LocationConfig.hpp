#ifndef LOCATIONCONFIG_HPP
# define LOCATIONCONFIG_HPP

# include <map>
# include <vector>
# include <set>
# include <string>

class LocationConfig // everything from the .conf file in default.conf
{
	private:

	std::string							_location; // from location /uploads or location /old-page - the URL prefix 
	std::string							_root;
	std::vector<std::string>			_index;
	std::set<std::string>				_allowedMethods;
	bool								_autoindex;
	int									_returnCode;
	std::string							_returnPage;
	std::string							_uploadStore;
	std::map<std::string, std::string>	_cgi;

	public:

	LocationConfig( void );
	LocationConfig( const LocationConfig& other );
	LocationConfig& operator=( const LocationConfig& other );
	~LocationConfig( void );

	//setters
	void	setLocation( const std::string& location );
	void	setRoot( const std::string& root );
	void	addIndex( const std::string& index );
	void	addAllowedMethods( const std::string& allowedMethods );
	void	setAutoindex( bool on );
	void	setReturnCode( int returnCode );
	void	setReturnPage( const std::string& returnPage );
	void	setUploadStore( const std::string& path );
	void	setCgi( const std::string& extension, const std::string& path );

	//getters
	const std::string&							getLocation( void ) const;			// -> olmatske
	const std::string&							getRoot( void ) const;				// -> olmatske
	const std::vector<std::string>&				getIndex( void ) const;				// -> olmatske
	const std::set<std::string>&				getAllowedMethods( void ) const;	// -> olmatske
	bool										getAutoindex( void ) const;			// -> olmatske
	int											getReturnCode( void ) const;		// -> olmatske
	const std::string&							getReturnPage( void ) const;		// -> olmatske
	const std::string&							getUploadStore( void ) const;		// -> olmatske
	const std::map<std::string, std::string>& 	getCgi( void ) const;				// -> olmatske

	bool		isMethodAllowed( const std::string& method ) const;					// -> olmatske
	bool		hasReturnCode( void ) const;										// -> olmatske
	bool		hasUploadStore( void ) const;										// -> olmatske
	bool		isCgi( const std::string& extension ) const;						// -> olmatske
	std::string	getCgiPath( const std::string& extension ) const;					// -> olmatske
};

#endif
