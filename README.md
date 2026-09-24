# FA_SuffixAutomation

An online, linear-time construction of the suffix automaton: the smallest DFA that accepts every suffix of a word. Written in C++ with flat arrays for states and transitions, so it handles inputs up to 10^8 characters.

For an input word it reports the number of states, edges and terminal states. Test inputs and a generator for random words (`generateInput.p`) are included.

```
./compile.sh && ./a.out < realWord.txt
```

C++ · 2017
