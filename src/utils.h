# pragma once
# include <Siv3D.hpp>
# include "MapManager.h"
# include "Player/PlayerController.h"
# include "Shop.h"
# include "Enemy.h"
# include "Hearts.h"
# include "Title.h"
# include "Boss.h"
# include "InGameUI.h"
# include "LevelTitle.h"

namespace UTILS {
    void HeartsLoop(Array<Hearts>* hearts);

}

struct PaletteSettings
{
    unsigned int currentPalette;
};

struct Particle
{
    Vec2 start;
    Vec2 velocity;
    int8_t type;
    int8_t color;
};

struct Spark : IEffect
{
    Array<Particle> m_particles;
    Texture enemyPalette;

    explicit Spark(const Vec2 &start, const int8_t &type)
        : m_particles(50)
    {
        for (auto &particle : m_particles)
        {
            particle.start = (start + RandomVec2(12.0));
            particle.velocity = (RandomVec2(1.0) * Random(100.0));
            particle.type = type;
            particle.color = ((RandomUint8() % 5) + 3);

            enemyPalette = Texture{Resource(U"Assets/EnemyPalette.png")};
        }
    }

    bool update(double t) override
    {
        for (const auto &particle : m_particles)
        {
            const Vec2 pos = (particle.start + particle.velocity * t + 0.5 * t * t * Vec2{0, 240});

            const double size = 10.0 * (1.0 - t);
            const double angle = pos.x * 10_deg;

            enemyPalette(particle.color, particle.type, 1, 1).resized(size).rotated(angle).drawAt(pos);
        }

        return (t < 1.0);
    }
};

struct RingEffect : IEffect
{
	Vec2 m_pos;

	ColorF m_color;

	explicit RingEffect(const Vec2& pos)
		: m_pos{ pos }
		, m_color{ Palette::Lightcoral } {}

	bool update(double t) override
	{
		// Easing
		const double e = EaseOutExpo(t);

		Circle{ m_pos, (e * 100) }.drawFrame((20.0 * (1.0 - e)), m_color);

		return (t < 1.0);
	}
};