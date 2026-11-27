#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <cstddef>
# include <map>
# include <string>
# include <vector>

struct UploadedFile					// -> olmatske
{
	std::string	fieldName;
	std::string	fileName;
	std::string	contentType;
	std::string	data;
};

class HttpRequest
{
	public:

	enum ParseState 				// -> ombilica
	{
		READING_REQUEST_LINE,
		READING_HEADERS,
		READING_BODY,
		READING_CHUNK_SIZE,
		READING_CHUNK_DATA,
		COMPLETE,
		ERROR
	};

	private:

	ParseState							_parseState; // gets the READING_REQUEST_LINE at start
	int									_errorCode;
	std::string							_incomingBuffer;

	std::string							_method;
	std::string							_rawPath;
	std::string							_path;
	std::string							_queryString;
	std::string							_httpVersion;
	std::map<std::string, std::string>	_httpHeaders;
	std::string							_body;
	std::vector<UploadedFile>			_uploadedFiles;

	bool								_isChunked;
	std::size_t							_contentLength;
	std::size_t							_currentChunkSize;

	public:

	HttpRequest( void );
	HttpRequest( const HttpRequest& other );
	HttpRequest& operator=( const HttpRequest& other );
	~HttpRequest( void );

	ParseState	appendData( const std::string& data, std::size_t maxBodySize );	// -> ombilica
	ParseState	getParseState( void ) const;										// -> ombilica
	bool		isComplete( void ) const;											// -> ombilica
	bool		hasError( void ) const;												// -> ombilica
	int			getErrorCode( void ) const;											// -> ombilica
	void		reset( void ); // to reuse the object for the next request			// -> ombilica

	//getters
	const std::string&							getMethod( void ) const;					// -> olmatske
	const std::string&							getRawPath( void ) const;					// -> olmatske
	const std::string&							getPath( void ) const;						// -> olmatske
	const std::string&							getQueryString( void ) const;				// -> olmatske
	const std::string&							getHttpVersion( void ) const;				// -> olmatske
	const std::map<std::string, std::string>&	getHeaders( void ) const;					// -> olmatske
	std::string									getHeader( const std::string& key ) const;	// -> olmatske
	bool										hasHeader( const std::string& key ) const;	// -> olmatske
	const std::string&							getBody( void ) const;						// -> olmatske
	const std::vector<UploadedFile>&			getUploadedFiles( void ) const;				// -> olmatske
};

#endif
