## Exerecise 3
### (i）

- pushback`(l, x)` is the same as append`(l, x)`, and `popback(l)` is the same as the sequence
`y := get(l, length); delete(l, length)`.

- pushfront`(l, x)` is the same as insert`(l, 1, x)`, and `popfront(l)` is the same as the sequence
`y := get(l, 1); delete(l, 1)`.

### (ii)
We can see that these operations are the common deque`(double-ended queue)` operations. By using circular arrays the amortised complexity of pushfront and popfront can be reduced to become constant.

See the implement in cdeque.h