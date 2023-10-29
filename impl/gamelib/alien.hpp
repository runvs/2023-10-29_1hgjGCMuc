#ifndef INC_2023_10_29_1HGJGCMUC_ALIEN_HPP
#define INC_2023_10_29_1HGJGCMUC_ALIEN_HPP

#include <animation.hpp>
#include <game_object.hpp>

class Alien : public jt::GameObject {

    std::shared_ptr<jt::Animation> m_anim;

    std::shared_ptr<jt::Animation> m_beam;

    jt::Vector2f m_pos {};

public:
    jt::Vector2f const getPos() const;

private:
    jt::Vector2f m_vel {};

    bool m_isBeaming { false };

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

public:
    bool isBeaming() const;
};

#endif // INC_2023_10_29_1HGJGCMUC_ALIEN_HPP
