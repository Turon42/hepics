/*
 * NeuralNetwork.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: Mehyar
 */

#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(){

}

NeuralNetwork::NeuralNetwork(string name, int numberOfLayers) {
	this->name=name;
	this->numberOfLayers=numberOfLayers;
	topology = NULL;
	this->index = (int *) calloc(1, sizeof(int));
	*index = 0;
}


string NeuralNetwork::getName(){
	return name;
}

void NeuralNetwork::setName(string name) {
	this->name = name;
}

void NeuralNetwork::addLayer(Layer layer){
	layers[*index]=layer;
	*(index)++;
	if(*index==numberOfLayers){
		cout << "All layers are set" << std::endl;
	}
}

int NeuralNetwork::getNumberOfLayers() {
	return numberOfLayers;
}

void NeuralNetwork::setNumberOfLayers(int numberOfLayers) {
	this->numberOfLayers = numberOfLayers;
}

void NeuralNetwork::displayTopology() {

}

void NeuralNetwork::setTopology(Image *topology) {
	this->topology = topology;
}

Image* NeuralNetwork::getTopology(){
	return this->topology;
}

Layer NeuralNetwork::getLayerAt(int i){
	return layers[i];
}
void NeuralNetwork::setLayerAt(int i, Layer layer){
	layers[i]=layer;
}
