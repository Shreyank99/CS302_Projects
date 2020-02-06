## COSC_302 - Project 02: Sorting List-Based Strings and Numbers

GitHub Link: https://github.com/spatel912020/CS302_Projects/tree/master/proj2  
(Repo Link: https://github.com/spatel912020/CS302_Projects.git)


### Team-Members

| Name           | GitHub Handle  | UTK NetID  |
|----------------|----------------|------------|
| Hunter Kitts   | hkitts         | hkitts2    |
| Shreyank Patel | spatel912020   | spatel91   |
| Andrew Whitus  | awhitus1       | awhitus1   |


### Benchmarking

| Mode    | Size     | Elapsed Time  |
|---------|----------|---------------|
| OBLIVIOUS | 10       | 0.002       | 
| OBLIVIOUS | 100      | 0.002       |
| OBLIVIOUS | 1000     | 0.004       | 
| OBLIVIOUS | 10000    | 0.019       | 
| OBLIVIOUS | 100000   | 0.161       | 
| OBLIVIOUS | 1000000  | 1.584       | 
| OBLIVIOUS | 10000000 | 15.942      |
| ...     | ...      | ...           | 
| STL     | 10       | 0.002         | 
| STL     | 100      | 0.002         |
| STL     | 1000     | 0.006         | 
| STL     | 10000    | 0.023         | 
| STL     | 100000   | 0.206         | 
| STL     | 1000000  | 2.364         | 
| STL     | 10000000 | 25.748        | 
| ...     | ...      | ...           | 
| QSORT   | 10       | 0.002         | 
| QSORT   | 100      | 0.003         |
| QSORT   | 1000     | 0.004         | 
| QSORT   | 10000    | 0.020         | 
| QSORT   | 100000   | 0.189         | 
| QSORT   | 1000000  | 2.074         | 
| QSORT   | 10000000 | 22.111        | 
| ...     | ...      | ...           | 
| MERGE   | 10       | 0.002         | 
| MERGE   | 100      | 0.003         |
| MERGE   | 1000     | 0.005         | 
| MERGE   | 10000    | 0.020         | 
| MERGE   | 100000   | 0.192         | 
| MERGE   | 1000000  | 2.192         | 
| MERGE   | 10000000 | 24.696        |
| ...     | ...      | ...           | 
| QUICK   | 10       | 0.002         | 
| QUICK   | 100      | 0.003         |
| QUICK   | 1000     | 0.005         | 
| QUICK   | 10000    | 0.022         | 
| QUICK   | 100000   | 0.206         | 
| QUICK   | 1000000  | 2.785         | 
| QUICK   | 10000000 | 34.408        |  


### Summary of Individual Contributions

- Hunter Kitts

   Node, List, Quick

   Hunter implemented Node, worked with Shreyank on List, and completed Quick Sort.

- Shreyank Patel 

    List, QSort, STL, Quick

    Shreyank worked with Hunter on List, and implemented both QSort and STL. Shreyank started work on Quick Sort which Hunter followed up on. 

- Andrew Whitus

    Merge, Benchmark, QSort

    Andrew implemented Merge Sort and worked some with Shreyank when troubleshooting QSort. Additionally, Andrew wrote a Python script to generate the random numbers needed for benchmarking. Andrew completed benchmarking and finallized the README.

### Benchmarking Reflections	

1. Discuss the relative performance of each sorting method and try to explain the differences.	
	
	In our test, QSort was a clear winner, followed by Merge and STL which were very close. Finally Quick was, surprisingly, last. This result could be due to a poor implementation of Quick, or it could just be a result of the compiler and specific machine the sorts were tested on.	

2. What do these results reveal about the relationship between theoretical complexity discussed in class and actual performance?	

	Even if theoretical complexity is supposedly better, a lot of the performance comes down to implementation and the specific machine the sort is run on. Quick is less complex than Merge, yet in our tests Merge beat it. The machine likely has a lot to do with this.	

3. In your opinion, which sorting mode is the best? Justify your conclusion by examining the trade-offs for the chosen mode.	

	Even though Quick is theoretically faster, the speed of Merge combined with its relatively simple implementation makes if very attractive. Additionally, Merge can be stable, which in some cases is advantageous. Its relative ease of implementation and respectable performance make it very attractive. In most cases, though, the STL sort is a safe bet and easiest of all. If QSort reliably outperforms STL as in our testing, it may be worth the extra hassle over STL.
