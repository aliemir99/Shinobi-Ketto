
#include "JsonFrameParser.h"
#include <fstream>
#include <iostream>
using json = nlohmann::json;
JsonFrameParser::JsonFrameParser(std::string path)
{
	std::ifstream ifs(path);
	json_ = json::parse(ifs);
	// std::cout << json_.dump(6);
}
std::vector<sf::IntRect>  JsonFrameParser::getFramesFor(std::string animationName) const
{
	std::vector<sf::IntRect> data; // frame textRecs for animaionName in atlas
	json k = json_["frames"];
	for (auto i : k)
	{
		std::string tmpStr = i["filename"]; // animation name is the first part of "filename" string
		if (tmpStr.compare(0, animationName.size(), animationName) == 0)
		{
			data.push_back(sf::IntRect(i["frame"]["x"],
				i["frame"]["y"],
				i["frame"]["w"],
				i["frame"]["h"]));
		}
	}
	return data;
}
std::vector<sf::IntRect>  JsonFrameParser::getFramesBackwardsFor(std::string animationName) const
{
	std::vector<sf::IntRect> data; // frame textRecs for animaionName in atlas
	json k = json_["frames"];
	for (auto i : k)
	{
		std::string tmpStr = i["filename"]; // animation name is the first part of "filename" string
		if (tmpStr.compare(0, animationName.size(), animationName) == 0)
		{
			data.push_back(sf::IntRect(i["frame"]["x"],
				i["frame"]["y"],
				i["frame"]["w"],
				i["frame"]["h"]));
		}
	}
	std::reverse(data.begin(), data.end());
	return data;
}