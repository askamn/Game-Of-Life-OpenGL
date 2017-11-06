#include "Color.h"

uint32_t Color::m_Colors[] = {
	// Flat UI Colors

	0x1abc9cff, // Turquiose
	0x2ecc71ff, // Emerald
	0x3498dbff, // Peter River
	0x9b59b6ff, // Amethyst
	0x34495eff, // Wet Asphalt
	0x16a085ff, // Green Sea
	0x27ae60ff, // Nephritis
	0x2980b9ff, // Belize Hole
	0x8e44adff, // Wisteria
	0x2c3e50ff, // Midnight Blue,
	0xf1c40fff, // Sun Flower
	0xe67e22ff, // Carrot
	0xe74c3cff, // Alizarin
	0xecf0f1ff, // Clouds
	0x95a5a6ff, // Concrete
	0xf39c12ff, // Orange
	0xd35400ff, // Pumpkin
	0xc0392bff, // Pomegranate
	0xbdc3c7ff, // Silver
	0x7f8c8dff, // Asbestos

	// Normal Colors

	0xffffffff, // White
	0xff0000ff, // Red
	0x00ff00ff, // Green
	0x0000ffff, // Blue
	0x000000ff, // Black
};

std::random_device Color::_randomDevice;
std::mt19937 Color::_mt(Color::_randomDevice());
std::uniform_int_distribution<int> Color::_number(0, COLOR_NUM_INTERNAL_COLORS - 1);

Color::Color()
{
	r = g = b = a = 0;
}

Color::Color(uint32_t color)
{
	r = ( color & 0xff000000 ) >> 24;
	g = ( color & 0x00ffffff ) >> 16;
	b = ( color & 0x0000ffff ) >> 8;
	a = ( color & 0x000000ff );

	normalize();
}

Color::Color(int r, int g, int b, int a) :
	r(r),
	g(g),
	b(b),
	a(a)
{
	normalize();
}

Color::Color(const glm::vec4& color, bool normalize) :
	r(color.x),
	g(color.y),
	b(color.z),
	a(color.w)
{
	if(normalize)
		this->normalize();
}

Color Color::Random()
{
	return m_Colors[_number(_mt)];
}

void Color::normalize()
{
	r = r / 255.0f;
	g = g / 255.0f;
	b = b / 255.0f;
	a = a / 255.0f;
}

Color::~Color()
{

}