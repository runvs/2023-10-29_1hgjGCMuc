#ifndef GAME_STATE_GAME_HPP
#define GAME_STATE_GAME_HPP

#include "alien.hpp"
#include "cow.hpp"
#include "object_group.hpp"
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_state.hpp>
#include <memory>
#include <vector>

// fwd decls
namespace jt {
class Shape;
class Sprite;
class Vignette;
} // namespace jt

class Hud;

class StateGame : public jt::GameState {
public:
    std::string getName() const override;

private:
    std::shared_ptr<jt::Shape> m_background;
    std::shared_ptr<jt::Vignette> m_vignette;
    std::shared_ptr<Hud> m_hud;
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };

    std::shared_ptr<Alien> m_alien { nullptr };

    std::shared_ptr<jt::ObjectGroup<Cow>> m_cows;

    bool m_running { true };
    bool m_hasEnded { false };

    int m_scoreP1 { 0 };
    int m_scoreP2 { 0 };

    float m_cowTimer = 1.0f;

    float m_updateTimer = 1.0f;

    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const elapsed) override;
    void onDraw() const override;

    void endGame();
    void createPlayer();

    void spawnCow();
};

#endif
