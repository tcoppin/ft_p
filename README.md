# ft_p

<table border="0">
   <tr>
      <td border="0">
         * This is a project of <a href="https://42.fr" target="_blank" >Ecole 42</a><br />
         * This program contain a ft_p server and a ft_p client.<br />
         * When you launch the server a folder "d_server" is create and it's the root of it.<br />
         * When a new client is launch a folder "client_X" (where X is the number of the client) was create.<br />
         * You can find the logs of the server in ft_p.log.
      </td>
      <td width="45%" border="0">
         <img src="http://i.imgur.com/Y27XA3B.png?1" width="100%" /><br />
         <img src="http://i.imgur.com/QxdpRzu.png?1" width="100%" />
      </td>
   </tr>
</table>

## Usage
	$>  make
	$>  usage: ./server <port>
	$>  usage: ./client <addr> <port>

## Available commands :

   * whoami (display the number of client)
   * pwd (writes the pathname of the current working directory)
   * cd (change the working directory of the server for the current client)
   * get (transfert a file server to client)
   * put (transfert a file client to server)
   * ls (list directory contents of the server)
   * mkdir (create a new directory on the server)
   * rm (remove directory entries)
   * lls (list directory contents of the client)
   * lmkdir (create a new directory on the client)
   * lrm (remove directory entries on the client)
   * quit (disconnect and exit the client)