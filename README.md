inet_pton4() implementation in C

Dependencies:
* gcc or clang compiler
* make
* glibc

Build options (using a generic template Makefile):
* make		  	  - default build (dynamic) with sanitizers
* make debug      	  - debug build (dynamic) with added -DDEBUG -g3 -O0 and with sanitizers
* make release_dynamic_O2 - builds for release with added -DNDEBUG -march=native -O2 -g0 and with sanitizers
* make release_dynamic_Os - builds for release with added -DNDEBUG -march=native -Os -g0 and with sanitizers
* make release_static_O2  - builds for release with added -DNDEBUG -march=native -O2 -g0 and without sanitizers
* make release_static_Os  - builds for release with added -DNDEBUG -march=native -Os -g0 and without sanitizers
* make run	  	  - runs the built program
* make clean	  	  - cleans the build leftovers
* make install	  	  - installs (copies) the program in /usr/local/bin/ - uncomment in the Makefile to use it
