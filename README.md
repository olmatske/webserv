# WEBSERV - ARCHITECTURE AND WORK DISTRIBUTION PROPOSAL

## Architecture overview

All the communication through .hpp contracts!

### 1. anshuval Parsing and Utilities
- **Config Parser:**
  - Parses Nginx-style configuration files (server { ... }, location { ... }).
  - Validates ports, hosts, server_name, client_max_body_size, error_pages, root, index, autoindex, allowed_methods, redirect, upload_store, and cgi extensions.
- **HTTP Request Parser:**
  - Incremental feed(rawChunk, maxBodySize) parser supporting partial TCP reads.
  - Parses request line (GET, POST, DELETE, URI, query string, HTTP/1.1), case-insensitive headers, Content-Length bodies, Transfer-Encoding: chunked, and multipart/form-data file uploads.
  - Sets HTTP error codes (400, 413, 414, 501) on malformed requests.
- **MimeTypes & ErrorPages:**
  - Extension-to-MIME-type mapping (.html, .css, .js, .png, .jpg, etc.).
  - Custom error page loader with clean default HTML fallback.
### 2. ombilica Network & Event Loop
 **Sockets & Multiplexing:**
  - Creates non-blocking TCP listening sockets (socket, setsockopt, bind, listen, fcntl(O_NONBLOCK)).
  - Runs the single non-blocking poll() / epoll() event loop.
- **Client Lifecycle:**
  - Manages incoming connections (accept), non-blocking recv() into HttpRequest::feed(), and partial non-blocking send() (POLLOUT).
  - Handles Keep-Alive resets, idle timeouts, and clean FD disconnection (Siege-safe).
### 3. olmatske Routing, Response & CGI
- **Routing & Response Builder:**
  - Matches request URI against ServerConfig / LocationConfig (longest prefix).
  - Enforces allowed methods (405), redirects (301/302), static file serving, autoindex directory HTML generation, POST upload saving, and DELETE handling.
  - Builds valid HTTP/1.1 response strings using MimeTypes and ErrorPages.
- **CGI Execution:**
  - Executes .py / .php scripts via fork(), pipe(), and execve() with proper CGI environment variables.
  - Feeds POST body via stdin, reads output non-blocking from stdout, parses CGI headers, and enforces script timeouts (no zombie processes or hangs).

##  Shared .hpp contracts
- Config.hpp, ServerConfig.hpp, LocationConfig.hpp
- HttpRequest.hpp

##  Example .conf File (Plain-English Guide)

nginx
server {
    listen 127.0.0.1:8080;           # IP and Port to listen on (like localhost:8080)
    server_name mysite.com;          # Optional domain name for this server
    client_max_body_size 1000000;    # Max upload size in bytes (1 MB) -> reject larger with 413!

    error_page 404 ./www/404.html;   # Custom HTML file to show when a page is not found

    # Rule for the home folder "/"
    location / {
        root ./www;                  # Folder on disk where files live (./www/index.html)
        index index.html;            # Default file if user visits "http://localhost:8080/"
        allowed_methods GET;         # Only allow GET here (reject POST/DELETE with 405!)
        autoindex off;               # If no index.html exists, don't list folder contents
    }

    # Rule for file uploads "/uploads"
    location /uploads {
        root ./www/uploads;
        allowed_methods GET POST DELETE; # Allow viewing, uploading, and deleting files
        autoindex on;                    # Show clickable list of files in the folder
        upload_store ./www/uploads;      # Where to save uploaded files from POST
    }

    # Rule for redirecting an old URL
    location /old-page {
        return 301 /new-page;        # Automatically send browser to /new-page
    }

    # Rule for running dynamic scripts (CGI)
    location /cgi-bin {
        root ./www/cgi-bin;
        allowed_methods GET POST;
        cgi .py /usr/bin/python3;    # If URL ends with ".py", run it with python3!
    }
}
