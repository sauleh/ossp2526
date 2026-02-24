#!/bin/sh
./testClient
EXIT_STATUS=$?
if [ $EXIT_STATUS -eq 0 ] ; then
   echo Now testing memory leak
   rm -f testMemLeak.txt
   valgrind --leak-check=full ./testClient 2> testMemLeak.txt
   case `grep "All heap blocks were freed -- no leaks are possible" testMemLeak.txt` in
       *"All heap blocks were freed -- no leaks are possible"*)
	   echo No memory leaks found
	   break;;
       *)
	   echo Problems with memory found
	   break
   esac
fi
	
