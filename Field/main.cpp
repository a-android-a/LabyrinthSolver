#include"Header/Header.h"
#include"auxiliary_functions.h"
#include"..\generation_algorithms\BinaryTreeAlgorithm\BinaryTreeAlgorithm.h"
#include"..\solution_algorithms\WaveAlgorithm\WaveAlgorithm.h"
#include"Field.h"

int main() {
	srand(time(0));
	setlocale(LC_ALL, "ru");
	 int width = 800;
	 int height = 800;

	RenderWindow window(VideoMode(width, height), L"Project ", Style::Default);
	
	sf::RectangleShape ButtonGenerate(sf::Vector2f(100, 50));

	sf::Font font;
	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");

	ButtonGenerate.setFillColor(sf::Color::Blue);
	ButtonGenerate.setPosition(width-100, height-600);
	sf::Text buttonText("generate", font, 24);
	buttonText.setPosition(width - 100, height - 600);
	
	
	
	sf::RectangleShape inputField(sf::Vector2f(200, 30));
	inputField.setFillColor(sf::Color::White);
	inputField.setPosition(width-300 , height-800);
	
	sf::Text inputText("set the number of squares", font, 24);
	inputText.setPosition(width-300, height-800);
	inputText.setFillColor(Color::Blue);
	std::string inputString;

	window.setFramerateLimit(15);
	window.setVerticalSyncEnabled(0);

	int NumberOfQuads = 50;





	

	Field f;
	f.SetNumberOfQuads(NumberOfQuads);


	WaveAlgorithm alg1;
	
	BinaryTreeAlgorithm alg2;

	alg2.generate(f);

	
	

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
				

                if (event.type == Event::Closed)
                    window.close();
				

				if (event.type == sf::Event::KeyPressed) {
					if (event.mouseButton.button == sf::Keyboard::F4) {
						f.Write(getMousePosition(window, f).x, getMousePosition(window, f).y, 1);
						
					}
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.mouseButton.button == sf::Keyboard::F3) {
						
						f.Write(getMousePosition(window, f).x, getMousePosition(window, f).y, 0);
						
					}
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Space) {
					
						if (alg1.findPathInMaze(f)) {
							alg1.DrawPath(f);
						}
						else
						{
							MessageBox(NULL, L"The maze cannot be solved", L"Error", MB_ICONERROR);
						}
							
							
							
					}
				}
 				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::F1)
					{
					
						f.SetPointStart(Vector2<int>(getMousePosition(window, f)));
						
					}
				}
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::F2)
					{
					
						f.SetPointEnd(Vector2<int>(getMousePosition(window, f)));
						
					}
				}
				
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
						if (ButtonGenerate.getGlobalBounds().contains(mousePosition)) {
							alg2.generate(f);
						}
					}
				}

				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode < 128) {
						if (event.text.unicode == 13) {
							
						}
						else if (event.text.unicode == 8) {
							if (inputString.size() > 0) {
								inputString.resize(inputString.size() - 1);
							}
						}
						else {
							inputString += static_cast<char>(event.text.unicode);
						}
						inputText.setString(inputString);
						
						
						
					}
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Enter)
					{
						NumberOfQuads = atoi(inputString.c_str());
						if (NumberOfQuads <= 200 and NumberOfQuads >= 0) {
							f.SetNumberOfQuads(NumberOfQuads);
						
						}
						else
						{
							if (NumberOfQuads < 0) {
								MessageBox(NULL, L"The value must be greater than zero", L"Error", MB_ICONERROR);
							}
							else
							{


								MessageBox(NULL, L"The field is too big", L"Error", MB_ICONERROR);
							}
						}
						
						inputString.clear();
						
						
						inputText.setString("set the number of squares");
						
					}
				}
            }
			
			


			window.clear();
		
			f.DrawWindow(window);

			window.draw(ButtonGenerate);
			window.draw(buttonText);
			window.draw(inputField);
			window.draw(inputText);
			window.display();
			
        }
    
	return EXIT_SUCCESS;
}