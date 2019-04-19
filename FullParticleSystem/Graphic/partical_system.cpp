#include "partical_system.h"
#include "utils.h"

extern const sf::Vector2u WINDOW_SIZES;


Particle::Particle(const sf::Vector2f position, const sf::Vector2f velocity, const sf::Vector2f acceleration, const float radius, const float mass)
    : position_(position)
    , velocity_(velocity)
    , acceleration_(acceleration)
    , radius_(radius)
    , mass_(mass)
{
    shape_.setRadius(radius);
    shape_.setFillColor(sf::Color::Yellow);
    shape_.setOrigin(sf::Vector2f(radius, radius));
    shape_.setPosition(position);
}


void Particle::Push(const sf::Vector2f delta_velocity)
{
    velocity_ += delta_velocity;
}


void Particle::Update(const float dt)
{
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
}


void Particle::Render(sf::RenderWindow& window)
{
    shape_.setPosition(position_);
    shape_.setRadius(radius_);

    window.draw(shape_);
}


ParticleSystem::ParticleID ParticleSystem::AddParticle(sf::Vector2f position,
    sf::Vector2f velocity,
    sf::Vector2f acceleration, 
    float radius,
    float mass)
{
    Particle new_particle(position, velocity, acceleration, radius, mass);
    particles_.push_back(new_particle);
    return particles_.size() - 1;
}


void ParticleSystem::AddLink(const ParticleID particle1_id, const ParticleID particle2_id,
    const float stiffness)
{
    links_.push_back(Link{
        particle1_id, particle2_id,
        ComputeDistanceBetween(particle1_id, particle2_id),
        stiffness
    });
}


const Particle& ParticleSystem::GetParticleByID(const ParticleID particle_id) const
{
    return particles_[particle_id];
}


float ParticleSystem::ComputeDistanceBetween(
    const ParticleID particle1_id,
    const ParticleID particle2_id) const
{
    const Particle& particle1 = GetParticleByID(particle1_id);
    const Particle& particle2 = GetParticleByID(particle2_id);

    const sf::Vector2f distance_vector12 = particle2.position_ - particle1.position_;
    return utils::ComputeLength(distance_vector12);
}


void ParticleSystem::Render(sf::RenderWindow& window)
{
    for (Link& link : links_)
    {
        const Particle& particle1 = GetParticleByID(link.particle1_id);
        const Particle& particle2 = GetParticleByID(link.particle2_id);

        sf::Vertex line[2] =
        {
            sf::Vertex(particle1.position_),
            sf::Vertex(particle2.position_)
        };

        window.draw(line, 2, sf::Lines);
    }

    for (Particle& particle : particles_)
    {
        particle.Render(window);
    }
}


void ParticleSystem::Update(const float dt)
{
    for (Particle& particle : particles_)
    {
        particle.acceleration_ = sf::Vector2f(0.0f, 0.0f);
    }

    SolveLinks();
    ApplyGravity();

    for (Particle& particle : particles_)
    {
        particle.Update(dt);
    }

    HandleCollisions();
}


void ParticleSystem::Push(const sf::Vector2f delta_velocity)
{
    for (Particle& particle : particles_)
    {
        particle.Push(delta_velocity);
    }
}


void ParticleSystem::ApplyGravity()
{
    const sf::Vector2f acceleration_g(0.0f, 98.0f);
    for (Particle& particle : particles_)
    {
        particle.acceleration_ += acceleration_g;
    }
}



void ParticleSystem::SolveLinks()
{
    for (Link& link : links_)
    {
        Particle& particle1 = particles_[link.particle1_id];
        Particle& particle2 = particles_[link.particle2_id];
        const sf::Vector2f distance_vector12 = (
            particle2.position_ - particle1.position_
        );
        const float distance = utils::ComputeLength(distance_vector12);
        const float delta = distance - link.initial_length;
        const float force = link.stiffness * delta;
        const sf::Vector2f unit_vector12 = distance_vector12 / distance; //вспомогательный единичный вектор
        particle1.acceleration_ += (force * unit_vector12) / particle1.mass_;
        particle2.acceleration_ -= (force * unit_vector12) / particle2.mass_;
    }
}


void ParticleSystem::HandleCollisions()
{
    for (Particle& particle : particles_)
    {
        if (particle.position_.x < particle.radius_)
        {
            particle.position_.x = particle.radius_;
            particle.velocity_.x = -particle.velocity_.x / 2.0f;
        }

        if (particle.position_.x + particle.radius_ > WINDOW_SIZES.x)
        {
            particle.position_.x = WINDOW_SIZES.x - particle.radius_;
            particle.velocity_.x = -particle.velocity_.x / 2.0f;
        }

        if (particle.position_.y < particle.radius_)
        {
            particle.position_.y = particle.radius_;
            particle.velocity_.y = -particle.velocity_.y / 2.0f;
        }

        const float bottom_gap = 50.0f;
        if (particle.position_.y + particle.radius_ + bottom_gap > WINDOW_SIZES.y)
        {
            particle.position_.y = WINDOW_SIZES.y - particle.radius_ - bottom_gap;
            particle.velocity_.y = -particle.velocity_.y / 2.0f;
        }
    }
}

