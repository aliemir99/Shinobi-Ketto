#pragma once
/*
	Team: std::pair(Ali-Ibrahim)
	Date: 2020-12-07
	Purpose: Create a frogger replica using GEX Engine
*/
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

enum class EffectID
{
	GongHit,
	GongRoll,
	H1Attack1,
	H1Attack2,
	H1GetHit,
	H2Attack1,
	H2Attack2,
	H2GetHit,
	H3Attack1,
	H3Attack2,
	H3GetHit,
	TakeDamage,
	MissAttack,
	Block

};

enum class MusicID
{
	TitleTheme,
	MenuTheme,
	JungleTheme,
	LakeTheme,
	CountyTheme,
	ForestTheme
};

enum class TextureID
{

	TitleScreen,
	MenuScreen,
	CharacterSelectionScreen,
	MapSelectionScreen,
	OptionsScreen,
	HowToPlayScreen,

	p1Controls,
	p2Controls,

	Particle,

	Background,

	platform,

	LeftHUD,
	RightHUD,

	Hero1,
	Hero1Avatar,

	Hero2,
	Hero2Avatar,

	Hero3,
	Hero3Avatar,

	BlockShield


};

enum class FontID
{
	Main,
	Side,
};

enum class ShaderID
{
	BrightnessPass,
	DownSamplePass,
	GaussianBlurPass,
	AddPass,
};


template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder_t = ResourceHolder <sf::Texture, TextureID>;
using FontHolder_t = ResourceHolder <sf::Font, FontID>;
using ShaderHolder_t = ResourceHolder<sf::Shader, ShaderID>;
using SoundBufferHolder_t = ResourceHolder<sf::SoundBuffer, EffectID>;