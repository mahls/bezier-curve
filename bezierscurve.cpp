//-lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

void getPointInbetween(sf::Vector2f& p0, sf::Vector2f& p1, sf::Vector2f& pBetween, float percentage){
    float mpX = (p1.x-p0.x) *percentage + p0.x;
    float mpY = (p1.y-p0.y) *percentage + p0.y;
    pBetween.x = mpX;
    pBetween.y = mpY;
};

int main(){
  
    sf::RenderWindow window(sf::VideoMode(500, 500), "Beziers Curve");

    sf::Vertex lineFinal[10*10+1];

    sf::Vector2f p0(50,300);
    sf::Vector2f p1(250,100);
    sf::Vector2f p2(350,350);

    sf::Vertex v0(p0, sf::Color::Green);
    sf::Vertex v1(p1, sf::Color::Blue);
    sf::Vertex v2(p2, sf::Color::Blue);
    sf::Vertex line[] = {v0,v1,v1,v2};

    float percentage = 0.00;
    sf::Vector2f pGreenStart;
    sf::Vector2f pGreenEnd;
    getPointInbetween(p0,p1, pGreenStart, percentage);
    getPointInbetween(p1,p2, pGreenEnd, percentage);

    // cout <<pm.x<<" "<<pm.y<<" | "<<mpX<<" "<<mpY<<endl;

    sf::CircleShape circleGreenStart(4);
    circleGreenStart.setPosition(pGreenStart);
    circleGreenStart.setOrigin(4,4);
    
    sf::CircleShape circleGreenEnd(4);
    circleGreenEnd.setPosition(pGreenEnd);
    circleGreenEnd.setOrigin(4,4);

    sf::CircleShape circleFinal(4);
    circleFinal.setOrigin(4,4);
    circleFinal.setFillColor(sf::Color::Red);
  
    bool bUpdateCalculations = true;
    int indexFinal = 0;
    sf::Vertex lineGreen[2];
    while(window.isOpen())  
    {
        sf::Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                if(percentage < 0.995){
                    percentage = percentage +0.01;
                    cout<<percentage<<endl;
                    bUpdateCalculations = true;
                };
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                if(percentage > 0.005){
                    percentage = percentage -0.01;
                    cout<<percentage<<endl;
                    bUpdateCalculations = true;
                };
            }
            
            if(bUpdateCalculations){
                getPointInbetween(p0,p1, pGreenStart, percentage);
                getPointInbetween(p1,p2, pGreenEnd, percentage);

                sf::Vector2f pFinal;
                getPointInbetween(pGreenStart,pGreenEnd, pFinal, percentage);

                circleFinal.setPosition(pFinal);
                indexFinal = (percentage+0.005) * 100;
                sf::Vertex vFinal(pFinal, sf::Color::Red);
                lineFinal[indexFinal] = vFinal;        

                sf::Vertex vGreenStart(pGreenStart,sf::Color::Green);
                sf::Vertex vGreenEnd(pGreenEnd, sf::Color::Green);
                lineGreen[0] = vGreenStart;
                lineGreen[1] = vGreenEnd;
                
                circleGreenStart.setPosition(pGreenStart);
                circleGreenEnd.setPosition(pGreenEnd);
                bUpdateCalculations = false;
            };

        }
        

        window.clear();
        
        window.draw(lineGreen, 2, sf::Lines);
        window.draw(line, 4, sf::Lines);
        window.draw(circleGreenStart);
        window.draw(circleGreenEnd);
        window.draw(circleFinal);
        for(int i = 0; i<indexFinal; i++){
            window.draw(&lineFinal[i],2,sf::Lines);
        }
        window.display();

    }

    return 0;
};


//  int startX  = 300;
    // int endX    = 200;

    // cout << endX * 0   << endl; 
    // cout << endX * 0.3 << endl; 
    // cout << endX * 0.6 << endl; 
    // cout << endX * 0.9 << endl; 
    // cout << endX * 1   << endl;