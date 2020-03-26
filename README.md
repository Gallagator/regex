I wrote a basic regex expression parser.
This was done with no knowledge of how these are to be implemented in code

It doesn't check for malformed expressions.
As far as I'm aware there are no memory leaks.

It uses an exponential time algorithm to actually traverse
the finite state machine representing the regex expression.

linear time ones do exist I may implement it later.
