# Include the libraries for socket and system calls
import socket
import sys
import os
import argparse
import re

# 1MB buffer size
BUFFER_SIZE = 1000000

parser = argparse.ArgumentParser()
parser.add_argument('hostname', help='the IP Address Of Proxy Server')
parser.add_argument('port', help='the port number of the proxy server')
args = parser.parse_args()

# Create a server socket, bind it to a port and start listening
# The server IP is in args.hostname and the port is in args.port
# bind() accepts an integer only
# You can use int(string) to convert a string to an integer
# ~~~~ INSERT CODE ~~~~

# Create a tuple storing the hostname and port as an integer
address = ( args.hostname, int( args.port ) )

# ~~~~ END CODE INSERT ~~~~

try:
  # Create a server socket
  # ~~~~ INSERT CODE ~~~~

  # Using the socket library create a new socket
  serverSocket = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

  # ~~~~ END CODE INSERT ~~~~
  print 'Connected socket'
except:
  print 'Failed to create socket'
  sys.exit()

try:
  # Bind the the server socket to a host and port
  # ~~~~ INSERT CODE ~~~~

  # Bind the socket to the tuple address
  serverSocket.bind( address )

  # ~~~~ END CODE INSERT ~~~~
  print 'Port is bound'
except:
  print('Port is in use')
  sys.exit()

try:
  # Listen on the server socket
  # ~~~~ INSERT CODE ~~~~

  # Listen for one connection of the server socket
  serverSocket.listen( 1 )

  # ~~~~ END CODE INSERT ~~~~
  print 'Listening to socket'
except:
  print 'Failed to listen'
  sys.exit()

while True:
  print 'Waiting connection...'

  clientSocket = None
  try:
    # Accept connection from client and store in the clientSocket
    # ~~~~ INSERT CODE ~~~~

    # Accept the connection from the client and create a new socket to handle their request
    ( clientSocket, clientAddress ) = serverSocket.accept()

    # ~~~~ END CODE INSERT ~~~~
    print 'Received a connection from:', args.hostname
  except:
    print 'Failed to accept connection'
    sys.exit()

  message = 'METHOD URI VERSION'
  # Get request from client
  # and store it in message
  # ~~~~ INSERT CODE ~~~~

  # Receive the GET request from the client
  # Specified a maximum length of data to be recieved arbitrarily to 4096.
  message = clientSocket.recv( 4096 )

  # ~~~~ END CODE INSERT ~~~~

  print 'Received request:'
  print '< ' + message

  # Extract the parts of the HTTP request line from the given message
  requestParts = message.split()
  method = requestParts[0]
  URI = requestParts[1]
  version = requestParts[2]

  print 'Method:\t\t' + method
  print 'URI:\t\t' + URI
  print 'Version:\t' + version
  print ''

  # Remove http protocol from the URI
  URI = re.sub('^(/?)http(s?)://', '', URI, 1)

  # Remove parent directory changes - security
  URI = URI.replace('/..', '')

  # Split hostname from resource
  resourceParts = URI.split('/', 1)
  hostname = resourceParts[0]
  resource = '/'

  if len(resourceParts) == 2:
    # Resource is absolute URI with hostname and resource
    resource = resource + resourceParts[1]

  print 'Requested Resource:\t' + resource

  cacheLocation = './' + hostname + resource
  if cacheLocation.endswith('/'):
    cacheLocation = cacheLocation + 'default'

  print 'Cache location:\t\t' + cacheLocation

  fileExists = os.path.isfile(cacheLocation)
  
  try:
    # Check wether the file exist in the cache
    cacheFile = open(cacheLocation, "r")
    outputdata = cacheFile.readlines()

    print 'Cache hit! Loading from cache file: ' + cacheLocation
    # ProxyServer finds a cache hit
    # Send back contents of cached file
    # ~~~~ INSERT CODE ~~~~

    # Send the cached file back to the client
    clientSocket.send( ''.join( outputdata ) )

    # ~~~~ END CODE INSERT ~~~~

    cacheFile.close()

  # Error handling for file not found in cache
  except IOError:
    if fileExists:
      clientResponse = ''
      # If we get here, the file exists but the proxy can't open or read it
      # What would be the appropriate status code and message to send to client?
      # store the value in clientResponse
      # ~~~~ INSERT CODE ~~~~

      # Server Errors specified as '5xx' in RFC 2616
      # Could not find an appropriate status code for a corrupted local file so defaulted to the error code:
      # 500 Internal Server Error for some unexpected internal error
      clientResponse = '500'

      # ~~~~ END CODE INSERT ~~~~

      print 'Sending to the client:'
      print '> ' + clientResponse
      print '>'
      clientSocket.sendall(clientResponse + "\r\n\r\n")

    else:
      originServerSocket = None
      # Create a socket to connect to origin server
      # and store in originServerSocket
      # ~~~~ INSERT CODE ~~~~

      # Initialise a new socket and call it originServerSocket
      originServerSocket = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

      # ~~~~ END CODE INSERT ~~~~

      print 'Connecting to:\t\t' + hostname + '\n'
      try:
        # Get the IP address for a hostname
        address = socket.gethostbyname(hostname)

        # Connect to the origin server
        # ~~~~ INSERT CODE ~~~~

        # Connect to the web server's address
        # Note that I used address to store the proxy server's address earlier but it now refers to the IP address of hostname
        # Also note that the port is always 80 for browser connections
        originServerSocket.connect( ( address, 80 ) )

        # ~~~~ END CODE INSERT ~~~~

        print 'Connected to origin Server'

        # Create a file object associated with this socket
        # This lets us use file function calls
        originServerFileObj = originServerSocket.makefile('+', 0)

        originServerRequest = ''
        originServerRequestHeader = ''
        # Create origin server request line and headers to send
        # and store in originServerRequestHeader and originServerRequest
        # originServerRequest is the first line in the request and
        # originServerRequestHeader is the second line in the request
        # ~~~~ INSERT CODE ~~~~

        # COMMENTS HERE
        originServerRequest = method + ' ' + resource + ' ' + version
        originServerRequestHeader = 'Host: ' + hostname

        # ~~~~ END CODE INSERT ~~~~

        # Construct the request to send to the origin server
        request = originServerRequest + '\r\n' + originServerRequestHeader + '\r\n\r\n'

        # Request the web resource from origin server
        print 'Forwarding request to origin server:'
        for line in request.split('\r\n'):
          print '> ' + line

        try:
          originServerSocket.sendall(request)
        except socket.error:
          print 'Send failed'
          sys.exit()

        originServerFileObj.write(request)

        # Get the response from the origin server
        # ~~~~ INSERT CODE ~~~~

        # Store the received response into the 'response' string
        response = originServerSocket.recv( 4096 )

        # ~~~~ END CODE INSERT ~~~~

        # Send the response to the client
        # ~~~~ INSERT CODE ~~~~

        # Send the response onto the client
        clientSocket.send( response )

        # ~~~~ END CODE INSERT ~~~~

        # finished sending to origin server - shutdown socket writes
        originServerSocket.shutdown(socket.SHUT_WR)

        print 'Request sent to origin server\n'

        # Create a new file in the cache for the requested file.
        # Also send the response in the buffer to client socket
        # and the corresponding file in the cache
        cacheDir, file = os.path.split(cacheLocation)
        print 'cached directory ' + cacheDir
        if not os.path.exists(cacheDir):
          os.makedirs(cacheDir)
        cacheFile = open(cacheLocation, 'wb')

        # Save orogin server response in the cache file
        # ~~~~ INSERT CODE ~~~~

        cacheFile.write( response )

        # ~~~~ END CODE INSERT ~~~~

        print 'done sending'
        originServerSocket.close()
        cacheFile.close()
        print 'cache file closed'
        clientSocket.shutdown(socket.SHUT_WR)
        print 'client socket shutdown for writing'
      except IOError, (value, message):
        print 'origin server request failed. ' + message
  try:
    clientSocket.close()
  except:
    print 'Failed to close client socket'
