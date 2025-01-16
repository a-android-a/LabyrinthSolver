#pragma once
#include"Header/Header.h"
class Field
{
private:
	size_t number_of_quads = 0;
	vector<vector<int>> fieldarr = { {} };
	vector<RectangleShape> squares = {};
	Vector2u size_window = Vector2u(0, 0);
	Vector2<int> pointstart = Vector2<int>(-1,-1) ;
	Vector2<int> pointend   = Vector2<int>(-1,-1);
	bool array_event = 1;
	void initializeField(vector<vector<int>>& f, size_t n) {
		int direction = 0;
		
		f.resize(n);
		for_each(f.begin(), f.end(), [n](auto& elem) { elem.resize(n); });

		for (int i = 0; i < f.size(); i++) {
			direction = 0;
			for (int j = 0; j < f[i].size(); j++) {
				if (direction == 0) {
					f[i][j] = 1;
					direction = 1;
				}
				else {
					f[j][i] = 1;
					direction = 0;
				}
			}
		}
	}
	
	void initializeSquares(vector<RectangleShape> &s, Vector2u size_window) {
		squares.resize(number_of_quads * number_of_quads);
		float widthx = static_cast<float>(size_window.x) / number_of_quads;
		float heighty = static_cast<float>(size_window.y) / number_of_quads;
	
		float x = 0, y = 0;
		for (int i = 0; i < squares.size(); i++) {
			if (i % number_of_quads == 0 && i != 0) {
				x = 0;
				y += heighty;
			}


			squares[i].setSize(Vector2f(widthx, heighty));
			squares[i].setPosition(x, y);
		

			x += widthx;
		}
	}
	void SetColor(vector<RectangleShape>& squares, vector<vector<int>>& f) {
		int l = 0;
		// 0 free space 1 wall 2 start point 3 end point 4 solutions

		for (int i = 0; i < f.size(); i++)
		{
			for (int j = 0; j < f.size(); j++)
			{
				if (f[i][j] == 0) squares[l].setFillColor(Color(255, 255, 255)); // free
				if (f[i][j] == 1) squares[l].setFillColor(Color(0, 0, 0)); // wall
				if (f[i][j] == 2) squares[l].setFillColor(Color(255, 0, 0)); // start_point
				if (f[i][j] == 3) squares[l].setFillColor(Color(0, 0, 255)); // end_point
				if (f[i][j] == 4) squares[l].setFillColor(Color(0, 255, 0)); // true path
				if (f[i][j] >= 5) squares[l].setFillColor(Color(192, 192, 192)); //the path traversed by the algorithm
				l++;
			}
		}

	}
public:
	
	Field() {
		
		number_of_quads = 0;
		fieldarr = {};
		squares = {};
		size_window = Vector2u(0, 0);
		pointstart = Vector2<int>(-1, -1);
		pointend = Vector2<int>(-1, -1);
		array_event = 1;
	}

	void SetNumberOfQuads(const size_t v) {
		number_of_quads = v;
		array_event = 1;
		initializeField(fieldarr, v);
		pointend.x = -1;
		pointend.y = -1;
		pointstart.x = -1;
		pointstart.y = -1;
		
	}
	

	void DrawWindow(RenderWindow& window) {
		size_window = window.getSize();

		if (array_event) {
			initializeSquares(squares, size_window);
			SetColor(squares, fieldarr);
			array_event = 0;
		}
		

	
		for (size_t i = 0; i < squares.size(); i++)
		{
			window.draw(squares[i]);
		}
		
	}
	

	bool SetPointStart(const Vector2<int> ps) {
	
			if (ps.x < fieldarr.size() and ps.y < fieldarr.size()) {
				if (pointstart.x == -1 and pointstart.y == -1) {
					
					fieldarr[ps.y][ps.x] = 2;
					pointstart = ps;
					array_event = 1;
				}
				else
				{
					fieldarr[pointstart.y][pointstart.x] = 0;
					fieldarr[ps.y][ps.x] = 2;
					pointstart = ps;
					array_event = 1;

				}
				
				return true;
			}
			else
			{
				return false;
			}

	}

	bool SetPointEnd(const Vector2<int> pe) {
		if (pe.x < fieldarr.size() and pe.y < fieldarr.size()) {

			if (pointend.x == -1 and pointend.y == -1) {

				fieldarr[pe.y][pe.x] = 3;
				pointend = pe;
				array_event = 1;
			}
			else
			{
				fieldarr[pointend.y][pointend.x] = 0;
				fieldarr[pe.y][pe.x] = 3;
				pointend = pe;
				array_event = 1;

			}
			return true;
		}
		else
		{
			return false;
		}
	}


	void clearPreviousPath() {
		for (int i = 0; i < number_of_quads; i++)
		{
			for (int j = 0; j < number_of_quads; j++)
			{
				if (fieldarr[i][j] > 1 and fieldarr[i][j] != 3 and fieldarr[i][j] != 2)fieldarr[i][j] = 0;
			}
		}

	}
	int Read(const size_t x, const size_t y) {
		
		
		try {
			if (x < fieldarr.size() and y < fieldarr.size()) {
				
				return fieldarr[y][x];
			}
			else
			{
				throw std::out_of_range("reading outside the field");
			}
			
		}
		catch (const std::out_of_range& e) {
			MessageBox(NULL, L"reading outside the field", L"Error", MB_ICONERROR);

		}
	}
	
	void Write(const size_t x , const size_t y, const int val) {
		try {
			if (x < fieldarr.size() and y < fieldarr.size()) {

				fieldarr[y][x] = val;
				array_event = 1;
			}
			else
			{
				throw std::out_of_range("recording outside the field");
			}

		}
		catch (const std::out_of_range& e) {
			MessageBox(NULL, L"recording outside the field", L"Error", MB_ICONERROR);

		}
	}

	Vector2<int> GetPointStart() {
		return pointstart;
	}
	Vector2<int> GetPointEnd() {
		return pointend;
	}
	size_t GetNumberOfQuads() { return number_of_quads;}


};
