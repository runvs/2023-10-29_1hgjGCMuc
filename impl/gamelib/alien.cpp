
#include "alien.hpp"
#include "game_properties.hpp"
#include <game_interface.hpp>
void Alien::doCreate()
{
    m_anim = std::make_shared<jt::Animation>();
    m_anim->loadFromAseprite("assets/Alien.aseprite", textureManager());
    m_anim->play("idle");

    m_beam = std::make_shared<jt::Animation>();
    m_beam->loadFromAseprite("assets/Beam.aseprite", textureManager());
    m_beam->play("idle");
    m_beam->setZ(5);
}

void Alien::doUpdate(float const elapsed)
{
    m_vel = m_vel * 0.9f;

    auto const speed = 100.0f;

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::A)) {
        m_vel.x = -speed;
    } else if (getGame()->input().keyboard()->pressed(jt::KeyCode::D)) {
        m_vel.x = speed;
    }

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::W)) {
        m_vel.y = -speed;
    } else if (getGame()->input().keyboard()->pressed(jt::KeyCode::S)) {
        m_vel.y = speed;
    }

    m_pos += elapsed * m_vel;

    if (m_pos.x < 0) {
        m_pos.x = 0;
    }
    if (m_pos.x > GP::GetScreenSize().x - 32) {
        m_pos.x = GP::GetScreenSize().x - 32;
    }

    if (m_pos.y < 0) {
        m_pos.y = 0;
    }
    if (m_pos.y > GP::GetScreenSize().y - 32) {
        m_pos.y = GP::GetScreenSize().y - 32;
    }

    m_anim->setPosition(m_pos);
    m_anim->update(elapsed);

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::Space)) {
        m_beam->setColor(jt::colors::White);
        m_isBeaming = true;
    } else {
        m_beam->setColor(jt::colors::Transparent);
        m_isBeaming = false;
    }

    m_beam->setPosition(m_pos + jt::Vector2f { 8, 16 });
    m_beam->update(elapsed);
}
void Alien::doDraw() const
{
    m_beam->draw(renderTarget());
    m_anim->draw(renderTarget());
}
bool Alien::isBeaming() const { return m_isBeaming; }
jt::Vector2f const Alien::getPos() const
{
    return m_beam->getPosition() + jt::Vector2f { 8.0f, 8.0f };
}
