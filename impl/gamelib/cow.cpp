#include "cow.hpp"
#include <math_helper.hpp>
#include <random/random.hpp>

void Cow::doCreate()
{
    m_anim = std::make_shared<jt::Animation>();
    m_anim->loadFromAseprite("assets/Cow.aseprite", textureManager());
    m_anim->play("idle");
    if (jt::Random::getChance()) {
        m_anim->setScale({ -1.0f, 1.0f });
        m_anim->setOffset({ 16.0f, 0.0f });
    }
}
void Cow::doUpdate(float const elapsed)
{
    m_anim->setPosition(m_pos);
    m_anim->update(elapsed);

    //    std::cout << m_beamValue << std::endl;

    if (m_beamValue <= 0) {
        m_beamValue = 0;
    } else {
        m_beamValue -= elapsed;
    }

    if (m_beamValue >= 1) {
        jt::GameObject::kill();
    }
}
void Cow::doDraw() const
{
    m_anim->draw(renderTarget());

    auto const v
        = static_cast<std::uint8_t>(255.0f * jt::MathHelper::clamp(1.0f - m_beamValue, 0.0f, 1.0f));
    m_anim->setColor(jt::Color { 255, 255, 255, v });
}

void Cow::setMPos(jt::Vector2f const& mPos) { m_pos = mPos; }
jt::Vector2f Cow::getPos() const { return m_pos + jt::Vector2f { 8.0f, 8.0f }; }
