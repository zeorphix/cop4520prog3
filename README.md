# cop4520prog3
cop4520 programming assignment 3

# Problem 1: The Birthday Presents Party

- Approach

I used multithreading to simulate the scenario of the Minotaur assigning 1 of 3 random tasks to 4 servants concurrently, making functions representing each of the tasks. Then I created a concurrent linked list to represent the chain of presents, each with data that represents their unique tag number.

- Experimental Evaluation


- Instructions
1. Download 'problem1.cpp'
2. Move file to directory of your choice
3. Compile by typing 'g++ problem1.cpp'
4. Execute the file by typing './a.exe'

# Problem 2: Atmospheric Temperature Reading Module

- Approach

I used multithreading to simulate 8 sensors reading temperatures per minute at the top of the hour, so there are 60 total readings for each sensor for one hour. Then I added all the readings into an array and sorted them, listing out the highest 5 temperatures, lowest 5 temperatures, and the maximum temperature difference.

- Experimental Evaluation

I tested different temperature ranges and different seeds for the random number generator in my program. I used print statements to check the diversity and validity of the temperatures.

- Instructions
1. Download 'problem2.cpp'
2. Move file to directory of your choice
3. Compile by typing 'g++ problem2.cpp'
4. Execute the file by typing './a.exe'
