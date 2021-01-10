# HTTP web server
##### This is an HTTP server which is able to serve static web pages.

### How to run the server
##### Run the following commands from the terminal to run the server
```
  cd target
  ./server
```

### How to recompile the server
##### Move to the cloned directory and run the following commands from the terminal to recompile
```
  make clean
  make
```

### Note
- Files which need to be served should be placed inside the target directory
- Default port number is : 8080
- To change the port number pass --port followed by the port number as command line arguments while excuting the file.
```
  ./server --port 8989
``` 
