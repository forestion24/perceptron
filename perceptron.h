#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <iostream>
using namespace std;

class Perceptron {
    private:
        vector<double> weights;
        double bias;
        double learningRate;
    public:
        Perceptron(const string& weightsFile, double lr);
        void weightsToFile(const string& weightsFile);
        void biasToFile(const string& biasFile);
        int feedForward(const vector<int>& inputs);
        void train(const vector<int>& input, int label);
};

#endif