/*
 * Classifier.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#include "Classifier.h"
namespace hepics {
Classifier::Classifier() :
		is_running { false }, canceled { false } {
}

Classifier::~Classifier() {
	// TODO Auto-generated destructor stub
}
void Classifier::start() {
	is_running = true;
	unique_ptr<Image> output = NULL;
	while(!canceled){
		for (auto const& input: assistant->getInputs()){
			output=make_unique<Image>(*input);
			for (auto const& l: network->get_layers()) {
				if(scheduler->getUsedPlatforms()[3] && l->get_type() == Layer::Type::convolutional){
					//run on fpga
				}else{
					output=l->forward_layer(*output);
				}
			}
			datasaver->add_output(move(output));
		}
	}
}
void Classifier::pause() {
	is_running = false;
}
void Classifier::resume() {
	is_running = true;
}
void Classifier::cancel() {
	is_running = false;
	canceled = true;
}
}