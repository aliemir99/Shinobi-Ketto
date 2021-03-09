#include "json.h"
#include <vector>
#include <SFML/Graphics/Rect.hpp>
using nlohmann::json;

struct IntRect {
    IntRect(int l, int t, int w, int h) : left(l), top(t), width(w), height(h) {}
    int left;
    int top;
    int width;
    int height;
};
class JsonFrameParser
{
public:
    JsonFrameParser(std::string path);
    std::vector<sf::IntRect>        getFramesFor(std::string animationName) const;
    std::vector<sf::IntRect>        getFramesBackwardsFor(std::string animationName) const;
private:
    json              json_;
};

