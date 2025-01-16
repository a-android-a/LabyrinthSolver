#include"..\..\Field\Header\Header.h"
#include"..\..\Field\Field.h"

class WaveAlgorithm
{
public:
    bool findPathInMaze( Field& f) {
        int step_count = 5, size_arr = 0 ;
        int y = f.GetPointStart().y, x = f.GetPointStart().x;
        Vector2<int> pe = f.GetPointStart();
      
        f.clearPreviousPath();

        vector<Vector2<int>> arr = { Vector2<int>(x,y) };

        if (f.GetPointStart().x != -1 and f.GetPointStart().y != -1 and f.GetPointEnd().x != -1 and f.GetPointEnd().y != -1) {


            while (!check_position(f)) {

                size_arr = arr.size();
                for (int i = 0; i < size_arr; i++)
                {
                    y = arr[i].y;
                    x = arr[i].x;


                    if (y + 1 < f.GetNumberOfQuads() && f.Read(x, y + 1) == 0) {
                        f.Write(x, y + 1, step_count);
                        arr.push_back(Vector2<int>(x, y + 1));
                    }

                    // Check up
                    if (y - 1 >= 0 && f.Read(x, y - 1) == 0) {
                        f.Write(x, y - 1, step_count);
                        arr.push_back(Vector2<int>(x, y - 1));
                    }

                    // Check left
                    if (x - 1 >= 0 && f.Read(x - 1, y) == 0) {
                        f.Write(x - 1, y, step_count);
                        arr.push_back(Vector2<int>(x - 1, y));
                    }

                    // Check right
                    if (x + 1 < f.GetNumberOfQuads() && f.Read(x + 1, y) == 0) {
                        f.Write(x + 1, y, step_count);
                        arr.push_back(Vector2<int>(x + 1, y));
                    }



                }
                if (size_arr == arr.size()) {
                    return false;
                    isSolvable = 0;
                }
                step_count++;
            }

            isSolvable = 1;
            return true;
        }
        return false;
    }

    void DrawPath(Field& f) {
      
        if (isSolvable) {
         

            int cost = 0;
            int min_cost = INT_MAX;
            int dx = 0, dy = 0;
            int x = f.GetPointEnd().x;
            int y = f.GetPointEnd().y;
            vector<vector<int>> s;

            while (!(x == f.GetPointStart().x and y == f.GetPointStart().y)) {
                min_cost = INT_MAX;
                dx = 0;
                dy = 0;
                cost = 0;

                if (y - 1 >= 0) {
                    cost = f.Read(x,y-1);
                    if (cost < min_cost and cost != 4 and cost >4 or cost == 2 and min_cost != 2) {
                        dx = 0;
                        dy = -1;
                        min_cost = cost;
                    }
                }
                if (y + 1 < f.GetNumberOfQuads()) {
                    cost = f.Read(x,y+1);
                    if (cost < min_cost and cost != 4 and cost >4 or cost == 2 and min_cost != 2) {
                        dx = 0;
                        dy = 1;
                        min_cost = cost;
                    }
                }
                if (x - 1 >= 0) {
                    cost = f.Read(x-1,y);
                    if (cost < min_cost and cost != 4 and cost >4 or cost ==2 and min_cost !=2 ) {
                        dx = -1;
                        dy = 0;
                        min_cost = cost;
                    }
                }
                if (x + 1 < f.GetNumberOfQuads()) {
                    cost = f.Read(x+1,y);
                    if (cost < min_cost and cost != 4 and cost >4 or cost == 2 and min_cost != 2) {
                        dx = 1;
                        dy = 0;
                        min_cost = cost;
                    }
                }
                if (min_cost == 2) break;
                x += dx;
                y += dy;
                f.Write(x,y, 4);
            }
            isSolvable = 0;
            f.Write(f.GetPointStart().x, f.GetPointStart().y, 2);
        }
    }

private:
    bool isSolvable = 0;

    bool check_position(Field& f) {
        int yend = f.GetPointEnd().y, xend = f.GetPointEnd().x;
        if (yend - 1 >= 0) {
            if (f.Read(xend, yend -1) > 5) return 1;
        }
        if (yend + 1 < f.GetNumberOfQuads()) {
            if (f.Read(xend, yend+1) > 5) return 1;
        }
        if (xend - 1 >= 0) {
            if (f.Read(xend -1 ,yend) > 5) return 1;
        }
        if (xend + 1 < f.GetNumberOfQuads()) {
            if (f.Read(xend+1, yend) > 5) return 1;
        }
        return 0;
    }
};