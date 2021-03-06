# Blue Noise Sequences
Source Code: [src/families/_2d/samples/blue_noise/](../../../../src/families/_2d/samples/blue_noise/)

Blue noise samples are randomized but roughly evenly spaced.

More details: [What is Blue Noise?](../../../../doc/bluenoise.md)  

There are many ways to generate 2d blue noise sample points, but there currently is only one way implemented:
* [Mitchell's Best Candidate](../../../../doc/bestcandidate.md)  

There are three variations, each using a different multiplier for the number of candidates generated compared to how many blue noise samples there already are: 1, 5 and 10.
# Test Results
 samples tested:
* BestCandidate (Progressive, Randomized)
* BestCandidate5 (Progressive, Randomized)
* BestCandidate10 (Progressive, Randomized)
## BestCandidate
### Discrete Fourier Transform
![BestCandidate](../../../_2d/samples/blue_noise/DFT_BestCandidate.png)  
### Plot
![BestCandidate](../../../_2d/samples/blue_noise/MakePlot_BestCandidate.png)  
## BestCandidate5
### Discrete Fourier Transform
![BestCandidate5](../../../_2d/samples/blue_noise/DFT_BestCandidate5.png)  
### Plot
![BestCandidate5](../../../_2d/samples/blue_noise/MakePlot_BestCandidate5.png)  
## BestCandidate10
### Discrete Fourier Transform
![BestCandidate10](../../../_2d/samples/blue_noise/DFT_BestCandidate10.png)  
### Plot
![BestCandidate10](../../../_2d/samples/blue_noise/MakePlot_BestCandidate10.png)  
## Discrepancy Test
![blue_noise](../../../_2d/samples/blue_noise/CalculateDiscrepancy.png)  
## Numerical Integration
### Disk
![blue_noise](../../../_2d/samples/blue_noise/Disk.png)  
### Triangle
![blue_noise](../../../_2d/samples/blue_noise/Triangle.png)  
### Step
![blue_noise](../../../_2d/samples/blue_noise/Step.png)  
### Gaussian
![blue_noise](../../../_2d/samples/blue_noise/Gaussian.png)  
### Bilinear
![blue_noise](../../../_2d/samples/blue_noise/Bilinear.png)  
