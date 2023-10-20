#include <iostream>
#include <SFML/Graphics.hpp>
#include <format>
#include "game_state.cpp"
#include "states/menu_state.cpp"
#include "context.hpp"
#include "react_likes/layouts/global_logger.layout.cpp"
#include "react_likes/layouts/state_logger.layout.cpp"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(), "Starcraft", sf::Style::Fullscreen);
    Context* ctx = new Context(window);
    GameStateManager gsm = ctx->gameStateManager;
    //GlobalLoggerLayout gll;
    StateLoggerLayout sll;

    try {
        gsm.pushState(ctx, new MenuState());

        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                switch (event.type) {
                    case sf::Event::Closed:
						window->close();
						break;
					case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Escape) {
							window->close();
						}
						break;
					case sf::Event::Resized:
						ctx->update();
						gsm.currentState()->onWindowResize(*window);
						break;
                    case sf::Event::KeyReleased:
                        if (event.key.code == sf::Keyboard::LAlt || event.key.code == sf::Keyboard::RAlt) {
                            if (event.key.code == sf::Keyboard::Return) {
                                if (window->getSize().x == sf::VideoMode::getDesktopMode().width && window->getSize().y == sf::VideoMode::getDesktopMode().height) {
									window->create(sf::VideoMode(1280, 720), "Starcraft", sf::Style::Default);
								}
                                else {
									window->create(sf::VideoMode::getDesktopMode(), "Starcraft", sf::Style::Fullscreen);
								}
								ctx->update();
								gsm.currentState()->onWindowResize(*window);
							}
						}
						break;
                }
            }

            try {
                // update context
                ctx->update();
                window->clear();

                cout << format("\n[{}s] Render Paint: dt({}s) fps({}) ------", 
                    ctx->currentLocalTime, ctx->deltaTime, ctx->frameRate) << endl;
                if (gsm.currentState()) {
                    gsm.currentState()->handleInput();
                    gsm.currentState()->update();
                    gsm.currentState()->draw(*window);
                }

                // draw global logger
                //gll.updateCheck
                //gll.render(*window);
                //gll.logs(ctx->logs).build(*window);
                sll.updateCheck(StateLoggerState(ctx->frameRate, ctx->deltaTime));
                sll.render(*window);

                window->display();
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
        window->close();
	}

    return 0;
}