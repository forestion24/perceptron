#include <fstream>
#include <string>
#include <vector>
#include "perceptron.h"
using namespace std;

Perceptron::Perceptron(const string& weightsFile, double lr) : learningRate(lr), bias(0.0) {
    ifstream inWeights(weightsFile);
    double weight;
    while (inWeights >> weight) {
        weights.push_back(weight);
    }
    inWeights.close();
}

void Perceptron::weightsToFile(const string& weightsFile) {
    ofstream outWeights(weightsFile);
    if (outWeights.is_open()) {
        for (double weight : weights) { // weight = weights[i]
            outWeights << weight << " ";
        }
        outWeights.close();
    } else {
        cout << "unable to open weights file\n";
    }
}

void Perceptron::biasToFile(const string& biasFile) {
    ofstream outBias(biasFile);
    if (outBias.is_open()) {
        outBias << bias;
        outBias.close();
    } else {
        cout << "unable to open bias file\n";
    }
}

int Perceptron::feedForward(const vector<int>& inputs) {
    double sum = bias;
    for (int i = 0; i < weights.size(); i++) {
        sum += inputs[i]*weights[i];
    }
    
    if (sum >= 0) {
        return 1;
    } else {
        return -1;
    }
}

void Perceptron::train(const vector<int>& inputs, int label) {
    int prediction = feedForward(inputs);
    int error = label - prediction;

    bias += learningRate * error;
    for (int i = 0; i < weights.size(); i++) {
        weights[i] += learningRate * error * inputs[i];
    }

    weightsToFile("weights.txt");
    biasToFile("bias.txt");
}