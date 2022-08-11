# AJA_COP
Constraint Optimization Problem component solver in real time.
Using fixed time search algorithms.


Initial Problem definition:

![transportation_problem_cop](https://user-images.githubusercontent.com/30693936/183830109-65d73372-f38a-4d4b-8fe3-59edd6ce6abf.png)


Sample results:\
  Per successful optimization the result is printed.\
  Rows represent the Supply.\
  Cols represent the Demand.
  
  Finally the best result reached is displayed.
  
Example Output:

![output_example](https://user-images.githubusercontent.com/30693936/183830588-a02fc7ae-06e2-4dd7-a4a0-78dc05395d3d.jpeg)


After that we have added and changed the objective function.
Now it looks like this:

![image](https://user-images.githubusercontent.com/30693936/183833056-ae03d820-e08a-43d3-b279-f4cdc35212af.png)

where Xn is the Vault on day n. (Supply[i] = Si, Demand[i] = Di, Cost[i][j] = Cij, TransitCost[i][j] = Tij)\
      fn is the Initial objective function on day n.\
      gn is total transit cost between each "city" at day n

The resulting objective function tells the following:\
  find the minimum such that:\
    80% of the focus is to minimize the current solution given day n vault.\
    10% to the difference between the amount assigned at day n, n-1, if there is a difference penalize it by a factor of 10.\
    10% to the difference between the locations in which transits have happend at day n, n-1, if there is a difference penalize if by a factor of 10.
