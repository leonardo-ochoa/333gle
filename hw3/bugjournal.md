# Bug 1

## A) How is your program acting differently than you expect it to?
- I am getting a seg fault in my WriteDocIDToPosition method.

## B) Brainstorm a few possible causes of the bug
- The kv value being passed in is possibly not correct.
- I am not converting the kv value correctly when truncating it to 32 bits.
- I am possibly not writing the DocIDElementPosition into the correct offset.

## C) How you fixed the bug and why the fix was necessary
- To fix the bug I ended up double casting the returned payload in LLIterator_Get. This was necessary since casting it just once gives a loss in conversion error.


# Bug 2

## A) How is your program acting differently than you expect it to?
- My HashTableReader keeps on failing.

## B) Brainstorm a few possible causes of the bug
- On step 3 I am probalby no iterating through the elements correctly.
- On step 2 I am not understanding what the question is telling me. This might be the cause of the bug if I am not reading correctly.
- The bug could also be caused by my previous implementation of FileIndexReader.

## C) How you fixed the bug and why the fix was necessary
- I fixed the bug on step 1, which ended up me seeking to the right location. This was necessary since I was not reading the files correctly.


# Bug 3

## A) How is your program acting differently than you expect it to?
-

## B) Brainstorm a few possible causes of the bug
-
-
-

## C) How you fixed the bug and why the fix was necessary
-
