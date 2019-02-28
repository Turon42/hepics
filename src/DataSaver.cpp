#include "DataSaver.h"
namespace hepics{
DataSaver::DataSaver() {

}

DataSaver::~DataSaver() {
	// TODO Auto-generated destructor stub
}
void DataSaver::add_result(Image input, Result result){
	resultMap.insert(std::pair<int,Result>(input.id,result));
}
void DataSaver::set_result(Image input, Result result){
	resultMap.insert(std::pair<int,Result>(input.id,result));
}
Result DataSaver::getResult(Image input){
	return resultMap[input.id];
}
void DataSaver::writeResultInFile(Image input){
	std::ofstream out("ClassificationResults.txt");
	out << resultMap[input.id].toString();
}

void DataSaver::add_output(unique_ptr<Image> &&output){
		this->outputs.push_back(move(output));
}
vector<unique_ptr<Image>> &DataSaver::getOutputs(){
	return outputs;
}
bool cmp(const pair<string, float>  &p1, const pair<string, float> &p2){
    return p1.second < p2.second;
}


std::vector<pair<std::string, float> > DataSaver::convertToVector(std::map<std::string,float> map){
	std::vector<pair<std::string, float> > toVector;
	copy(map.begin(), map.end(), back_inserter(toVector));
	sort(toVector.begin(), toVector.end(), cmp);
	return toVector;
}

Result DataSaver::aggregate(vector<Image> images){
	//1- each image has 4 class names, add these to one map (globalMap) on this class, total of 4* number of images class names
	//2- if class name already exists in globalMap, add percentage of current image classification
	//3- parse through whole globalMap and select 4 biggest percentages
	//4- divide percentages by 4 and save aggregation as a new Result

	map<string,float> global;
	std::vector<Image>::iterator it;
	for (it = images.begin() ; it != images.end(); ++it){
		//iterate through images
//		std::map<std::string, float> currResult = resultMap[it->id].getPercentage();
		std::map<std::string, float> currResult;
		std::map<std::string, float>::iterator it2 = currResult.begin();
		while (it2 != currResult.end()){
			//iterating through results of the image
			if( global.find(it2->first) == global.end()){
				//if classname doesn't exist add it
				global[it2->first]= it2->second;
			} else {
				//if classname exists, add the new value to it
				global[it2->first] += it2->second;
			}
			it2++; // next classname of the results
		}
	}
	// now global is filled with all the classnames, need to look for the biggest 4


	Result aggregationResult;
	std::map<std::string, float>::iterator iterator = global.begin();
	while (iterator != global.end()){
		global[iterator->first]=iterator->second/images.size();
		// to get the aggregation right
	}
	std::vector<pair<std::string, float>> vector = convertToVector(global);
	//std::vector<pair<std::string, float>>::iterator i;
	for(int i =0; i != 4; ++i) {
	    aggregationResult.save_result(vector[i].first, vector[i].second);
	}
	return aggregationResult;
}
void DataSaver::delete_result(Image input){
	this->resultMap.erase(input.id);
}
}
