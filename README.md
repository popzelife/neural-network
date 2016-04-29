# Cpp - Open Neural Network v. alpha0.5
*Educational purporse  - for now. The purpose is only to keep growing an open source community on machine learning.* <br>
<br>
C++ Project that can build a simple multi layer Neural Network able to handle XOR logic problem: an non linear classification problem. 

Input1|Input2|Output
------|------|------
0|0|0
0|1|1
1|0|1
1|1|0

It uses a supervised learning, actually a Back Propagation training methods that tells where to seek the "needle" according to a set of training. It compares a bunch of Expected Outputs and Actual Outputs to get a "Layer Error". It's the usual form of a Neural Network. <br>
<br>
Now working on Genetic Algorithm to create a reinforcement training that could be less efficient than a back propagation learning but would better handle others problems like solving sudoko, or optimizing space in a limited space backpack (eg.).


## What is a Neural Network?
The project is separated into 4 classes that create the Neural Network *(network.h)*: a bunch of connected *(connection.h)* neurons *(neuron.h)* organized by a layer *(layer.h)*. The Neural Network can handles differents layers: **X neurons \*literal asterisks\* X connections**; and communicates between these layers to train them (back propagation learnin).<br>
<br>
![Neural Network](http://www.codeproject.com/KB/recipes/NeuralNetwork_1/NN2.png)<br>
<br>
If you want to learn more about Neural Network, you better read this great article of Sach Barber: [AI : Neural Network for beginners](http://www.codeproject.com/Articles/16419/AI-Neural-Network-for-beginners-Part-of)


## What to do next?
A bunch of articles to give ideas on how to optimize and improve this neural network:
- [cuDNN Deep Neural Network Library by nVidia](https://devblogs.nvidia.com/parallelforall/accelerate-machine-learning-cudnn-deep-neural-network-library/)
- [Efficient mapping of the training to a CUDA based-cluster](http://parse.ele.tue.nl/education/cluster2)
- [Neural Network for SARAH](http://blog.encausse.net/2013/05/15/sarah-gagne-quelques-neurones/) (french)
- *[SARAH Documentation](http://jpencausse.github.io/SARAH-Documentation/?lang=en) (english)*
- [AI Life](http://www.codeproject.com/Articles/28858/AI-Life)
- [Deep learning with image recognition](http://neuralnetworksanddeeplearning.com/chap1.html)
