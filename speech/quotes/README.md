Quotes
======

The quotes folder used to handle all predetermined speech that tyrone will used. 'Predetermined' used loosely.

## Examples:
### Playing a random quote from GLaDOS:
```bash
./randomFromWeb.sh links/GLaDOS.list
```
   This will play a quote that has already been downloaded from the previous run, then download a
   new random quote which is picked out of a list of links (GLaDOS.list). The order is reversed to reduce
   latency between running the program and hearing a quote.
   
   Blank lines and those beginning with '#' are ignored in GLaDOS.list.
   
   randomFromWeb.sh supports storing quotes locally from multiple lists without confusing which quote 
   to play at runtime. It also is a bit thread safe, subsequent calls to randomFromWeb.sh will close
   early if an instance is already running. It does this by setting ../../service/ownership/gettingRandomQuote
   to 1
