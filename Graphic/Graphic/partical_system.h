#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(const sf::Vector2f position_, 
        const sf::Vector2f velocity_,
        const sf::Vector2f acceleration_,
        const float radius_);
    virtual ~Particle() = default;

    void Push(const sf::Vector2f increment);

    void Update(const float dt);
    void Render(sf::RenderWindow& window);

private:
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
    float radius_;

    sf::CircleShape shape_;

};

class ParticleSystem
{
public:
    ParticleSystem() = default;
    virtual ~ParticleSystem() = default;

    using ParticleID = size_t;

    ParticleID AddParticle(const sf::Vector2f position,
        const sf::Vector2f velocity,
        const sf::Vector2f acceleration,
        const float radius);

    const Particle& GetParticleByID(const ParticleID particle_id);

    void Push(const sf::Vector2f delta_velocity);

    void Update(const float dt);
    void Render(sf::RenderWindow& window);

private:
    std::vector<Particle> particles_;
};