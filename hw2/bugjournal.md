# Bug 1

## A) How is your program acting differently than you expect it to?
- I keep getting a segfault when running fileparser.

## B) Brainstorm a few possible causes of the bug
- I am possibly not reading the file correclty.
- I am probably not adding the word positions into the correct spot.
- My HTKeyValues are not pointing to the correct data.

## C) How you fixed the bug and why the fix was necessary
- I did not acount for the null terminator when coping string.


# Bug 2

## A) How is your program acting differently than you expect it to?
- My hashtable is empty when I run crawfiletree.

## B) Brainstorm a few possible causes of the bug
- Possibly not catching paths that are . or ..
- My contents are possibly not correct before passing it to parseintoword.
- Data that is not of type ASCII is being passed in with my file

## C) How you fixed the bug and why the fix was necessary
- I fixed it by checking if tab was null. This was necessary because it prevented it from inserting a null hashtable into verify function.


# Bug 3

## A) How is your program acting differently than you expect it to?
-

## B) Brainstorm a few possible causes of the bug
-
-
-

## C) How you fixed the bug and why the fix was necessary
-
