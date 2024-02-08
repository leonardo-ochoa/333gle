# Bug 1

## A) How is your program acting differently than you expect it to?
- I am getting a memory leak on line 72.

## B) Brainstorm a few possible causes of the bug
- Possibly not freeing the allocated memory.
- Another method did not free memory before calling this method.
-

## C) How you fixed the bug and why the fix was necessary
- I fixed the bug by freeing each node in Linked_List_Free.


# Bug 2

## A) How is your program acting differently than you expect it to?
- Its not finding keys that should be in the table

## B) Brainstorm a few possible causes of the bug
- I am possibly not inserting correclty.
- I am possibly not using malloc correclty.
- I am having a hard time understanding the pointers.

## C) How you fixed the bug and why the fix was necessary
- I fixed the bug by properly casting my the struct values into
another struct instead of just setting both struct equal to each other.


# Bug 3

## A) How is your program acting differently than you expect it to?
- I am getting memory leaks in my insert HashTable_Insert function.

## B) Brainstorm a few possible causes of the bug
- My old key value pointer is pointing to some data it shouldn't.
- I am possibly not freeing a pointer I allocated space for.
- I am possibly coping the key values into some unkown memory.

## C) How you fixed the bug and why the fix was necessary
- I drew a memory diagram for my finding value function. What I ended
up finding is that I did not free memory for removed hash table key values.
