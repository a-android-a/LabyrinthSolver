#pragma once
#include"Header/Header.h"
#include"Field.h"

Vector2i getMousePosition(RenderWindow &window , Field &f) {

	const sf::Vector2i globalMousePosition = sf::Mouse::getPosition();
	const sf::Vector2i windowPosition = window.getPosition();
		  sf::Vector2i localMousePosition = globalMousePosition - sf::Vector2i(windowPosition.x, windowPosition.y);
	
	const int x = window.getSize().x / f.GetNumberOfQuads();
	const int y = window.getSize().x / f.GetNumberOfQuads();
	localMousePosition.x /= x;
	localMousePosition.y /= y;
	return localMousePosition;
}


