#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
    friend class ParticleSystem;

public:
    Particle(const sf::Vector2f position_, 
        const sf::Vector2f velocity_,
        const sf::Vector2f acceleration_,
        const float radius_,
        const float mass_);
    virtual ~Particle() = default;

    void Push(const sf::Vector2f increment);

    void Update(const float dt);
    void Render(sf::RenderWindow& window);

private:
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
    float radius_;
    float mass_;

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
        const float radius,
        const float mass);

    const Particle& GetParticleByID(const ParticleID particle_id) const;

    void AddLink(const ParticleID particle1_id,
        const ParticleID particle2_id,
        const float stiffness
    );

    float ComputeDistanceBetween(const ParticleID particle1_id,
        const ParticleID particle2_id) const;

    void Push(const sf::Vector2f delta_velocity);

    void Update(const float dt);
    void Render(sf::RenderWindow& window);

private:

    void ApplyGravity();
    void SolveLinks();
    void HandleCollisions();

    struct Link
    {
        ParticleID particle1_id;
        ParticleID particle2_id;
        float initial_length;
        float stiffness;
    };

    std::vector<Particle> particles_;
    std::vector<Link> links_;
};