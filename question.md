https://www.reddit.com/r/dailyprogrammer/comments/oirb5v/20210712_challenge_398_difficult_matrix_sum/

[2021-07-12] Challenge #398 [Difficult] Matrix Sum


Example

Consider this 5x5 matrix of numbers:

123456789   752880530   826085747  576968456   721429729
173957326   1031077599  407299684  67656429    96549194
1048156299  663035648   604085049  1017819398  325233271
942914780   664359365   770319362  52838563    720059384
472459921   662187582   163882767  987977812   394465693

If you select 5 elements from this matrix such that no two elements come from the same row or column, what is the smallest possible sum? The answer in this case is 1099762961 (123456789 + 96549194 + 663035648 + 52838563 + 163882767).


Challenge

Find the minimum such sum when selecting 20 elements (one from each row and column) of this 20x20 matrix. The answer is a 10-digit number whose digits sum to 35.

There's no strict runtime requirement, but you must actually run your program all the way through to completion and get the right answer in order to qualify as a solution: a program that will eventually give you the answer is not sufficient.


Optional Bonus

What's the smallest sum you can find for this 97x97 matrix? It's okay to give a result that's not optimal in this case. If you want to prove that you found a certain sum, you can you post the indices of each element you selected from each row in order. For the 5x5 example, for instance, you could post [0,4,1,3,2].


(This challenge is a repost of Challenge #67 [difficult], originally posted by u/oskar_s in June 2012. See that post for the formula to algorithmically generate the matrices if you prefer to do it that way.)
