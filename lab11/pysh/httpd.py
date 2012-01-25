# $Id$

from CGIHTTPServer import CGIHTTPRequestHandler
from BaseHTTPServer import HTTPServer

httpd = HTTPServer(("", 8080), CGIHTTPRequestHandler)
httpd.serve_forever()
