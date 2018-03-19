#include<cstddef>
#include<cstdlib>
#include<ctime>
#include<limits>
#include<sstream>
#include<SFML/Graphics/CircleShape.hpp>
#include<SFML/Graphics/Color.hpp>
#include<SFML/Graphics/Font.hpp>
#include<SFML/Graphics/Image.hpp>
#include<SFML/Graphics/RectangleShape.hpp>
#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/System/Clock.hpp>
#include<SFML/System/Time.hpp>
#include<SFML/System/Vector2.hpp>
#include<SFML/Window/Event.hpp>
#include<SFML/Window/VideoMode.hpp>

class Game
{
    public:
        Game()
        {
            float obstacleSpeeds[10u];
            sf::CircleShape circleShapes[10u];
            for(unsigned int index(0u); index<10u; ++index)
            {
                circleShapes[index].setFillColor(sf::Color::Red);
                circleShapes[index].setPointCount(4u);
                if(!index)
                {
                    obstacleSpeeds[index]=10.0f;
                    circleShapes[index].setPosition(rand()%static_cast<int>(640.0f-circleShapes[index].getRadius()*2.0f), 60.0f);
                }

                else
                {
                    obstacleSpeeds[index]=obstacleSpeeds[index-1u]*-1.0f;
                    circleShapes[index].setPosition(rand()%static_cast<int>(640.0f-circleShapes[index].getRadius()*2.0f), circleShapes[index-1u].getPosition().y+circleShapes[index-1u].getRadius()*2.0f+22.75f);
                }

                circleShapes[index].setRadius(7.5f);
            }

            float playerSpeed(400.0f);

            unsigned int state(0u);

            size_t score(0u);

            std::ostringstream stringStream;

            srand(time(NULL));

            sf::CircleShape circleShape(10.0f, 3u);
            circleShape.setFillColor(sf::Color::Blue);
            circleShape.setPosition(300.0f, 440.0f);

            sf::Clock clock;

            sf::Color color(sf::Color::Black);

            sf::Event event;

            sf::Font font;
            font.loadFromFile("jelly_donuts/Jelly Donuts.otf");

            sf::Image image;
            image.create(100u, 100u, sf::Color::Yellow);
            for(unsigned int index(0u); index<100u; ++index)
            {
                image.setPixel(50u-index, index, sf::Color::Red);
                image.setPixel(50u+index, index, sf::Color::Red);
                image.setPixel(51u-index, index, sf::Color::Red);
                image.setPixel(51u+index, index, sf::Color::Red);
                image.setPixel(52u-index, index, sf::Color::Red);
                image.setPixel(52u+index, index, sf::Color::Red);
                image.setPixel(53u-index, index, sf::Color::Red);
                image.setPixel(53u+index, index, sf::Color::Red);
                image.setPixel(54u-index, index, sf::Color::Red);
                image.setPixel(54u+index, index, sf::Color::Red);
                image.setPixel(100u-index, index, sf::Color::Black);
                image.setPixel(100u+index, index, sf::Color::Black);
                image.setPixel(99u-index, index, sf::Color::Black);
                image.setPixel(99u+index, index, sf::Color::Black);
                image.setPixel(98u-index, index, sf::Color::Black);
                image.setPixel(98u+index, index, sf::Color::Black);
                image.setPixel(97u-index, index, sf::Color::Black);
                image.setPixel(97u+index, index, sf::Color::Black);
                image.setPixel(96u-index, index, sf::Color::Black);
                image.setPixel(96u+index, index, sf::Color::Black);
            }

            sf::RectangleShape rectangleShape0(sf::Vector2f(640.0f, 5.0f));
            rectangleShape0.setFillColor(sf::Color::Black);
            rectangleShape0.setPosition(0.0f, 420.0f);

            sf::RectangleShape rectangleShape1(sf::Vector2f(640.0f, 5.0f));
            rectangleShape1.setFillColor(sf::Color::Yellow);
            rectangleShape1.setPosition(0.0f, 50.0f);

            sf::RenderWindow renderWindow(sf::VideoMode(640u, 480u), "Rachid's Shape Dodger Project");
            renderWindow.setIcon(100u, 100u, image.getPixelsPtr());
            renderWindow.setVerticalSyncEnabled(true);

            sf::Text text0;
            text0.setCharacterSize(30u);
            text0.setFillColor(sf::Color::Yellow);
            text0.setFont(font);
            text0.setPosition(renderWindow.getSize().x/4u, renderWindow.getSize().y/50u);
            text0.setString("SHAPE DODGER");

            sf::Text text1;
            text1.setCharacterSize(20u);
            text1.setFillColor(sf::Color::Yellow);
            text1.setFont(font);
            text1.setPosition(renderWindow.getSize().x/4u, renderWindow.getSize().y/5u);
            text1.setString("Press ESC to quit the game\n\nPress I for instructions\n\nPress P to play");

            sf::Text text2;
            text2.setCharacterSize(10u);
            text2.setFillColor(sf::Color::Black);
            text2.setFont(font);
            text2.setPosition(renderWindow.getSize().x/50u, renderWindow.getSize().y/7u);
            text2.setString("Summary:\n\n\tThe goal of the game is to avoid the obstacle shapes\n\n\tand get to the other side.\n\n\tIf you get hit even once, it is game over!\n\n\tHow many times can you get to the other side!?.");

            sf::Text text3;
            text3.setCharacterSize(10u);
            text3.setFillColor(sf::Color::Black);
            text3.setFont(font);
            text3.setPosition(renderWindow.getSize().x/50u, renderWindow.getSize().y/2.2f);
            text3.setString("Game Controls:\n\n\tPress the down arrow or S key to move the triangle character down\n\n\tPress the left arrow or A key to move the triangle character left\n\n\tPress the right arrow or D key to move the triangle character right\n\n\tPress the up arrow or W key to move the triangle character up.");

            sf::Time time;

            while(renderWindow.isOpen())
            {
                renderWindow.clear(color);

                switch(state)
                {
                    case 0u:
                    {
                        renderWindow.draw(text0);
                        renderWindow.draw(text1);

                        while(renderWindow.pollEvent(event))
                        {
                            switch(event.type)
                            {
                                case sf::Event::Closed:
                                {
                                    renderWindow.close();

                                    break;
                                }

                                case sf::Event::KeyPressed:
                                {
                                    switch(event.key.code)
                                    {
                                        case sf::Keyboard::Escape:
                                        {
                                            renderWindow.close();

                                            break;
                                        }

                                        case sf::Keyboard::I:
                                        {
                                            state=1u;

                                            color=sf::Color::Green;

                                            text0.setFillColor(sf::Color::Black);
                                            text0.setString("INSTRUCTIONS");

                                            text1.setCharacterSize(10u);
                                            text1.setFillColor(sf::Color::Black);
                                            text1.setPosition(renderWindow.getSize().x/50u, renderWindow.getSize().y/1.30f);
                                            text1.setString("Press B to return to title screen\n\nPress ESC to quit the game\n\nPress P to play");

                                            break;
                                        }

                                        case sf::Keyboard::P:
                                        {
                                            state=2u;

                                            color=sf::Color::Magenta;

                                            break;
                                        }

                                        default:
                                        {
                                            break;
                                        }
                                    }

                                    break;
                                }

                                default:
                                {
                                    break;
                                }
                            }
                        }

                        break;
                    }

                    case 1u:
                    {
                        renderWindow.draw(text0);
                        renderWindow.draw(text1);
                        renderWindow.draw(text2);
                        renderWindow.draw(text3);

                        while(renderWindow.pollEvent(event))
                        {
                            switch(event.type)
                            {
                                case sf::Event::Closed:
                                {
                                    renderWindow.close();

                                    break;
                                }

                                case sf::Event::KeyPressed:
                                {
                                    switch(event.key.code)
                                    {
                                        case sf::Keyboard::B:
                                        {
                                            state=0u;

                                            color=sf::Color::Black;

                                            text0.setFillColor(sf::Color::Yellow);
                                            text0.setString("SHAPE DODGER");

                                            text1.setCharacterSize(20u);
                                            text1.setFillColor(sf::Color::Yellow);
                                            text1.setPosition(renderWindow.getSize().x/4u, renderWindow.getSize().y/5u);
                                            text1.setString("Press ESC to quit the game\n\nPress I for instructions\n\nPress P to play");

                                            break;
                                        }

                                        case sf::Keyboard::Escape:
                                        {
                                            renderWindow.close();

                                            break;
                                        }

                                        case sf::Keyboard::P:
                                        {
                                            state=2u;

                                            color=sf::Color::Magenta;

                                            break;
                                        }

                                        default:
                                        {
                                            break;
                                        }
                                    }

                                    break;
                                }

                                default:
                                {
                                    break;
                                }
                            }
                        }

                        break;
                    }

                    case 2u:
                    {
                        renderWindow.draw(circleShape);
                        for(unsigned int index(0u); index<10u; ++index)
                        {
                            circleShapes[index].move(obstacleSpeeds[index]*time.asSeconds(), 0.0f);
                            if(circleShapes[index].getPosition().x<=0.0f||circleShapes[index].getPosition().x>=640.0f-circleShapes[index].getRadius()*2.0f)
                            {
                                obstacleSpeeds[index]*=-1.0f;
                            }
                            renderWindow.draw(circleShapes[index]);
                        }
                        renderWindow.draw(rectangleShape0);
                        renderWindow.draw(rectangleShape1);

                        time=clock.restart();

                        while(renderWindow.pollEvent(event))
                        {
                            switch(event.type)
                            {
                                case sf::Event::Closed:
                                {
                                    renderWindow.close();

                                    break;
                                }

                                case sf::Event::KeyPressed:
                                {
                                    switch(event.key.code)
                                    {
                                        case sf::Keyboard::A:
                                        {
                                            if(circleShape.getPosition().x>0.0f)
                                            {
                                                circleShape.move(-playerSpeed*time.asSeconds(), -time.asSeconds());
                                            }

                                            break;
                                        }

                                        case sf::Keyboard::D:
                                        {
                                            if(circleShape.getPosition().x<640.0f-circleShape.getRadius()*2.0f)
                                            {
                                                circleShape.move(playerSpeed*time.asSeconds(), time.asSeconds());
                                            }

                                            break;
                                        }

                                        case sf::Keyboard::Down:
                                        {
                                            if(circleShape.getPosition().y<480.0f-circleShape.getRadius()*2.0f)
                                            {
                                                circleShape.move(time.asSeconds(), playerSpeed*time.asSeconds());
                                            }

                                            break;
                                        }

                                        case sf::Keyboard::Escape:
                                        {
                                            renderWindow.close();

                                            break;
                                        }

                                        case sf::Keyboard::Left:
                                        {
                                            if(circleShape.getPosition().x>0.0f)
                                            {
                                                circleShape.move(-playerSpeed*time.asSeconds(), -time.asSeconds());
                                            }

                                            break;
                                        }

                                        case sf::Keyboard::Right:
                                        {
                                            if(circleShape.getPosition().x<640.0f-circleShape.getRadius()*2.0f)
                                            {
                                                circleShape.move(playerSpeed*time.asSeconds(), time.asSeconds());
                                            }

                                            break;
                                        }

                                        case sf::Keyboard::S:
                                        {
                                            if(circleShape.getPosition().y<480.0f-circleShape.getRadius()*2.0f)
                                            {
                                                circleShape.move(time.asSeconds(), playerSpeed*time.asSeconds());
                                            }

                                            break;
                                        }

                                        case sf::Keyboard::Up:
                                        {
                                            if(circleShape.getPosition().y>0.0f)
                                            {
                                                circleShape.move(-time.asSeconds(), -playerSpeed*time.asSeconds());
                                            }

                                            break;
                                        }

                                        case sf::Keyboard::W:
                                        {
                                            if(circleShape.getPosition().y>0.0f)
                                            {
                                                circleShape.move(-time.asSeconds(), -playerSpeed*time.asSeconds());
                                            }

                                            break;
                                        }

                                        default:
                                        {
                                            break;
                                        }
                                    }
                                }

                                default:
                                {
                                    break;
                                }
                            }
                        }

                        for(unsigned int index(0u); index<10u; ++index)
                        {
                            if(circleShape.getGlobalBounds().intersects(circleShapes[index].getGlobalBounds()))
                            {
                                state=3u;

                                stringStream<<"You avoided the shapes "<<score<<" time(s)";

                                color=sf::Color::Cyan;

                                text0.setFillColor(sf::Color::Red);
                                text0.setString("GAME OVER");

                                text1.setCharacterSize(20u);
                                text1.setFillColor(sf::Color::Red);
                                text1.setPosition(renderWindow.getSize().x/10u, renderWindow.getSize().y/5u);
                                text1.setString(stringStream.str());

                                text2.setCharacterSize(20u);
                                text2.setFillColor(sf::Color::Red);
                                text2.setPosition(renderWindow.getSize().x/10u, renderWindow.getSize().y/3u);
                                text2.setString("Press B to return to title screen\n\nPress ESC to quit the game\n\nPress I for instructions\n\nPress P to play again");

                                for(unsigned int index(0u); index<10u; ++index)
                                {
                                    if(!index)
                                    {
                                        obstacleSpeeds[index]=10.0f;
                                        circleShapes[index].setPosition(rand()%static_cast<int>(640.0f-circleShapes[index].getRadius()*2.0f), 60.0f);
                                    }

                                    else
                                    {
                                        obstacleSpeeds[index]=obstacleSpeeds[index-1u]*-1.0f;
                                        circleShapes[index].setPosition(rand()%static_cast<int>(640.0f-circleShapes[index].getRadius()*2.0f), circleShapes[index-1u].getPosition().y+circleShapes[index-1u].getRadius()*2.0f+22.75f);
                                    }
                                }

                                circleShape.setPosition(300.0f, 440.0f);

                                score=0;

                                stringStream.str("");
                                stringStream.clear();

                                break;
                            }
                        }

                        if(circleShape.getPosition().y<50.0f)
                        {
                            ++score;

                            for(unsigned int index(0u); index<10u; ++index)
                            {
                                if(obstacleSpeeds[index]<std::numeric_limits<float>::max())
                                {
                                    obstacleSpeeds[index]*=-2.0f;
                                }

                                if(!index)
                                {
                                    circleShapes[index].setPosition(rand()%static_cast<int>(640.0f-circleShapes[index].getRadius()*2.0f), 60.0f);
                                }

                                else
                                {
                                    circleShapes[index].setPosition(rand()%static_cast<int>(640.0f-circleShapes[index].getRadius()*2.0f), circleShapes[index-1u].getPosition().y+circleShapes[index-1u].getRadius()*2.0f+22.75f);
                                }
                            }

                            circleShape.setPosition(300.0f, 440.0f);
                        }

                        break;
                    }

                    case 3u:
                    {
                        renderWindow.draw(text0);
                        renderWindow.draw(text1);
                        renderWindow.draw(text2);

                        while(renderWindow.pollEvent(event))
                        {
                            switch(event.type)
                            {
                                case sf::Event::Closed:
                                {
                                    renderWindow.close();

                                    break;
                                }

                                case sf::Event::KeyPressed:
                                {
                                    switch(event.key.code)
                                    {
                                        case sf::Keyboard::B:
                                        {
                                            state=0u;

                                            color=sf::Color::Black;

                                            text0.setFillColor(sf::Color::Yellow);
                                            text0.setString("SHAPE DODGER");

                                            text1.setCharacterSize(20u);
                                            text1.setFillColor(sf::Color::Yellow);
                                            text1.setPosition(renderWindow.getSize().x/4u, renderWindow.getSize().y/5u);
                                            text1.setString("Press ESC to quit the game\n\nPress I for instructions\n\nPress P to play");

                                            break;
                                        }

                                        case sf::Keyboard::Escape:
                                        {
                                            renderWindow.close();

                                            break;
                                        }

                                        case sf::Keyboard::I:
                                        {
                                            state=1u;

                                            color=sf::Color::Green;

                                            text0.setFillColor(sf::Color::Black);
                                            text0.setString("INSTRUCTIONS");

                                            text1.setCharacterSize(10u);
                                            text1.setFillColor(sf::Color::Black);
                                            text1.setPosition(renderWindow.getSize().x/50u, renderWindow.getSize().y/1.30f);
                                            text1.setString("Press B to return to title screen\n\nPress ESC to quit the game\n\nPress P to play");

                                            text2.setCharacterSize(10u);
                                            text2.setFillColor(sf::Color::Black);
                                            text2.setPosition(renderWindow.getSize().x/50u, renderWindow.getSize().y/7u);
                                            text2.setString("Summary:\n\n\tThe goal of the game is to avoid the obstacle shapes\n\n\tand get to the other side.\n\n\tIf you get hit even once, it is game over!\n\n\tHow many times can you get to the other side!?.");

                                            break;
                                        }

                                        case sf::Keyboard::P:
                                        {
                                            state=2u;

                                            color=sf::Color::Magenta;

                                            break;
                                        }

                                        default:
                                        {
                                            break;
                                        }
                                    }

                                    break;
                                }

                                default:
                                {
                                    break;
                                }
                            }
                        }

                        break;
                    }

                    default:
                    {
                        break;
                    }
                }

                renderWindow.display();
            }
        }
};

int main()
{
    Game game;

    return 0;
}
