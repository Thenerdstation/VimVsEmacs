Round 1 Challenge

In this, you are given a large .txt file and you must find and replace all words accoring to the directions in changes.txt

For example, if the .txt file only contains

```
Will this class be curved? this is really hard.
```

And the changes file says

```
this -> every
```

Then the new file you make should say

```
Will every class be curved? every is really hard.
```

The changes are case sensitive, so only replace exact matchings of the word.


You are given the competition file and the solution file. After your edits, the competition file should exactly match the solution file, otherwise you will have to try again.


Partial words should also be replaced. So if you are asked to `every -> help` and you see the word everytime, the solution file should read helptime.
