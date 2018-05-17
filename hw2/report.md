# Digital Signal Processing Project 2

#### b03902008 林煦恩

## Training Process

------------------

### Phase 1: Adjust number of states

- For state $0$ (initial state), the transition function is always going to state1.
- For state $1$ to state $n - 2$, the transition function is 50% going to the itself and 50% going to the next state($1 \rightarrow 2$, $2 \rightarrow 3$ and so on)
- For state $n - 1$ (final state), the transition function is a zero vector. 

![state](/Users/XNS/codes/DSP/hw2/images/state.png)

|   \#state(n)   |   5    |   6    |   7    |   8    |   9    |
| :------------: | :----: | :----: | :----: | :----: | :----: |
|  **accuracy**  | 74.34% | 81.47% | 87.80% | 89.64% | 90.91% |
| **\#state(n)** | **10** | **11** | **12** | **15** | **20** |
|  **accuracy**  | 93.67% | 94.25% | 95.22% | 95.91% | 94.42% |



--------------------

### Phase 2: Adjust the number of iterations

![iteration](/Users/XNS/codes/DSP/hw2/images/iteration.png)

$(n1, n2, n3)$ = (#iter of 1st HERest, #iter of 2nd HERest, #iter of 3rd HERest)

- \#states = 12

| #iteration   | (3, 3, 6) | (5, 5, 10) | (7, 7, 14) | (10, 10, 20) | (15, 15, 30) | (20, 20, 40) |
| ------------ | --------- | ---------- | ---------- | ------------ | ------------ | ------------ |
| **accuracy** | 95.22%    | 95.57%     | 95.80%     | 96.20%       | 96.43%       |96.49%|

---------------------------

### Phase 3: Adjust the number of Gaussion Mixtures

- Adjust all states except initial and final.

- \#state: 12 
- \#iteration: (20, 20, 40)

| \#Gaussion Mixtures | 2      | 3      | 4      | 5      | 6      |
| ------------------- | ------ | ------ | ------ | ------ | ------ |
| **accuracy**        | 96.49% | 96.61% | 97.12% | 97.18% | 96.89% |

-----------------

## Result

- The maximum accuracy is 97.18% (#state = 12, #iteration = (20, 20, 40), #GM = 5)
- ![max_acc](/Users/XNS/codes/DSP/hw2/images/max_acc.png)