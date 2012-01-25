= Simple HTTP server and a CGI-based shell skeleton =

Files:

 * httpd.py -- HTTP server with CGI support
 * cgi-bin/pysh.cgi -- shell skeleton


Running:

 1. change to the current directory.
 1. run the HTTP server:

    python httpd.py
 
 1. In your web browser, access the following URL:

         http://localhost:8080/cgi-bin/pysh.cgi

 1. Enter a command line in the input field.
 1. Press Enter.
 1. See how the command line is split and printed as
    a Python array according to the shell syntax.


Improving:

  edit cgi-bin/pysh.cgi so that it becomes a real shell.
