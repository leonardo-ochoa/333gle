# Bug 1

## A) How is your program acting differently than you expect it to?
- HttpConnection keeps on failing.

## B) Brainstorm a few possible causes of the bug
- I am possibly not reading the next request correclty.
- I am possibly not identifying the end of the header correclty.
- I am possibly not resetting the buffer correctly.

## C) How you fixed the bug and why the fix was necessary
- I found the bug in ParseRequest. I was accidentally calling split
twice on unnecessary strings.


# Bug 2

## A) How is your program acting differently than you expect it to?
- I keep getting a memory leak.

## B) Brainstorm a few possible causes of the bug
- I am possibly not freeing memory correclty in FileReader
- The buffers I created in HttpUtils is have memory issues
- I am not checking that root_dir and test_file are safe paths.

## C) How you fixed the bug and why the fix was necessary
- Before I had realpath take in a nullptr so it would create its own
buffer based. This leaked memory when I modified that buffer. I ended passing
it a buffer instead of nullptr.

# Bug 3

## A) How is your program acting differently than you expect it to?
- I keep getting a segfault when running the web server.

## B) Brainstorm a few possible causes of the bug
- I am probably not setting the file suffix correctly.
- Another issue could be that I am not reading the passed in file correclty.
- Another issue could be that my getnextrequest function is not working
properly.

## C) How you fixed the bug and why the fix was necessary
- The issue was that I was not checking for the size of the first line
of the request. This was necessary since the first line needs to have 3
arguments.
