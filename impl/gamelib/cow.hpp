
#ifndef INC_1HGJGCMUC_COW_HPP
#define INC_1HGJGCMUC_COW_HPP

#include <animation.hpp>
#include <game_object.hpp>

class Cow : public jt::GameObject {
public:
    void setMPos(jt::Vector2f const& mPos);
    float m_beamValue = 0.0f;
    bool m_hasBeenBeamed { false };

private:
    std::shared_ptr<jt::Animation> m_anim;

    jt::Vector2f m_pos {};

public:
    jt::Vector2f getPos() const;

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // INC_1HGJGCMUC_COW_HPP
