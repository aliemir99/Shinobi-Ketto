#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
	: music()
	, filenames()
	, volume(100.f)
{
	filenames[MusicID::TitleTheme] = "Media/Music/TitleTheme.wav";
	filenames[MusicID::MenuTheme] = "Media/Music/MenuTheme.wav";
	filenames[MusicID::JungleTheme] = "Media/Music/JungleTheme.wav";
	filenames[MusicID::LakeTheme] = "Media/Music/LakeTheme.wav";
	filenames[MusicID::CountyTheme] = "Media/Music/MushroomCountyTheme.wav";
	filenames[MusicID::ForestTheme] = "Media/Music/MysticalForestTheme.wav";
}

void MusicPlayer::play(MusicID theme)
{
	auto filename = filenames[theme];

	if (!music.openFromFile(filename))
		throw std::runtime_error("Music " + filename + "could not be loaded");

	music.setVolume(volume);
	music.setLoop(true);
	music.play();
}

void MusicPlayer::stop()
{
	music.stop();
}

void MusicPlayer::setPaused(bool paused)
{
	if (paused)
		music.pause();
	else
		music.play();
}

void MusicPlayer::setVolume(float vol)
{
	volume = vol;
}

MusicPlayer::MUSIC_TYPE MusicPlayer::getType()
{
	return musicType;
}

void MusicPlayer::setMusicType(MUSIC_TYPE type)
{
	musicType = type;
}
