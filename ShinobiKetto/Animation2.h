#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
//
// An animaiton is a collection of frames. 
// 
using Frame = sf::IntRect;
class Animation2
{
public:
	explicit 				Animation2(bool repeat = true);
	void					addFrame(Frame frame);
	void					addFrameSet(std::vector<Frame> frames);
	void 					setDuration(sf::Time duration);
	sf::Time 				getDuration() const;
	void 					setRepeating(bool flag);
	bool 					isRepeating() const;
	void 					restart();
	bool 					isFinished() const;
	Frame					getCurrentFrame() const;
	Frame 					update(sf::Time dt);
	bool					isStarting() const;
private:
	std::vector<Frame>		frames_;
	std::size_t 			currentFrame_;
	sf::Time 				duration_;
	sf::Time 				elapsedTime_;
	bool 					repeat_;
};