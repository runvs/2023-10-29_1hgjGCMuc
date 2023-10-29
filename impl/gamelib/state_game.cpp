#include "state_game.hpp"
#include "random/random.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <color/color.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/hud.hpp>
#include <math_helper.hpp>
#include <screeneffects/vignette.hpp>
#include <shape.hpp>
#include <state_menu.hpp>

void StateGame::onCreate()
{
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 0.0f });

    getGame()->gfx().createZLayer(5);

    float const w = static_cast<float>(GP::GetWindowSize().x);
    float const h = static_cast<float>(GP::GetWindowSize().y);

    using jt::Shape;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h }, textureManager());
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    createPlayer();

    m_vignette = std::make_shared<jt::Vignette>(GP::GetScreenSize());
    add(m_vignette);
    m_hud = std::make_shared<Hud>();
    add(m_hud);

    m_cows = std::make_shared<jt::ObjectGroup<Cow>>();
    add(m_cows);

    for (auto i = 0; i != 10; ++i) {
        spawnCow();
    }

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void StateGame::onEnter() { }

void StateGame::createPlayer()
{
    m_alien = std::make_shared<Alien>();
    add(m_alien);
}

void StateGame::onUpdate(float const elapsed)
{
    if (m_running) {
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        // update game logic here

        if (getGame()->input().keyboard()->pressed(jt::KeyCode::LShift)
            && getGame()->input().keyboard()->pressed(jt::KeyCode::Escape)) {
            endGame();
        }

        m_cowTimer -= elapsed;
        if (m_cowTimer <= 0) {
            spawnCow();
            if (getAge() >= 30) {
                m_cowTimer = 1.0f;
            } else {
                m_cowTimer = 3.0f;
            }
        }

        if (m_alien->isBeaming()) {
            //            std::cout << "beaming\n";
            for (auto& c : *m_cows) {
                auto cow = c.lock();

                auto const cp = cow->getPos();
                auto const ap = m_alien->getPos();

                auto const dist = ap - cp;
                auto const l = jt::MathHelper::length(dist);

                //                std::cout << l << std::endl;
                if (l < 16) {
                    cow->m_beamValue += elapsed * 2.5;

                    if (cow->m_beamValue >= 1.0f) {
                        if (!cow->m_hasBeenBeamed) {
                            m_scoreP1 += 1;
                            m_hud->getObserverScoreP1()->notify(m_scoreP1);

                            cow->m_hasBeenBeamed = true;
                        }
                    }
                }
            }
        }

        m_updateTimer -= elapsed;
        if (m_updateTimer <= 0) {
            m_updateTimer = 1.0f;
            m_hud->getObserverScoreP2()->notify(static_cast<int>(60.0f - getAge()));
        }

        if (getAge() >= 60) {
            endGame();
        }
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
}

void StateGame::onDraw() const
{
    m_background->draw(renderTarget());
    drawObjects();
    m_vignette->draw();
    m_hud->draw();
}

void StateGame::endGame()
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_hasEnded = true;
    m_running = false;

    getGame()->stateManager().switchToStoredState("menu");
}

std::string StateGame::getName() const { return "State Game"; }
void StateGame::spawnCow()
{
    auto cow = std::make_shared<Cow>();
    cow->setMPos(jt::Random::getRandomPointIn(GP::GetScreenSize()));
    add(cow);

    m_cows->push_back(cow);
}
