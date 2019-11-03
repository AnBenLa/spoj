//https://www.spoj.com/problems/BULK/
#include <iostream>
#include <vector>
#include <fstream>

using  namespace std;

struct point_2d{
    float x = 0.0f;
    float y = 0.0f;
};

struct segment_2d{
    point_2d a;
    point_2d b;
};

struct point{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct ray{
    point origin;
    point direction;
};

struct ray_2d{
    point_2d origin;
    point_2d direction;
};

struct line_2d{
    point_2d origin;
    point_2d direction;
};

struct face{
    vector<point> points;
    //x == 0, y == 1, z == 2
    int normal = -1;
};

point operator - (point const& a, point const& b){
    return {a.x-b.x, a.y-b.y, a.z-b.z};
}

point cross_p(point const& a, point const& b){
    return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};
}

int ori(point_2d const& a, point_2d const& b, point_2d const& c){
    int dx21 = b.x - a.x;
    int dy21 = b.y - a.y;
    int dx31 = c.x - a.x;
    int dy31 = c.y - a.y;
    if(dy31*dx21 > dx31*dy21)
        return -1; //ccw
    if(dy31*dx21 < dx31*dy21)
        return + 1; //cw
    return 0; //collinear
}

bool intersect(segment_2d const& s, line_2d const& r){
    point a{s.a.x,s.a.y,1};
    point b{s.b.x,s.b.y,1};

    double min_y = min(s.a.y, s.b.y);
    double max_y = max(s.a.y, s.b.y);

    point l_ab = cross_p(a, b);

    point c{r.origin.x, r.origin.y, 1};
    point d{r.origin.x + r.direction.x, r.origin.y + r.direction.y, 1};

    point l_cd = cross_p(c, d);

    //intersection point of the lines going through the segment and the ray
    point inter = cross_p(l_ab, l_cd);

    if(inter.z != 0) {
        //if the intersection point is between the points of the segment returns true
        if (ori(s.a, point_2d{inter.x / inter.z, inter.y / inter.z}, s.b) == 0)
            if(inter.x/inter.z >= r.origin.x && inter.y/inter.z >= min_y && inter.y/inter.z <= max_y)
                return true;
    }
    return false;
}

bool inside(vector<point_2d> const& f, point_2d const& p){
    int cuts = 0;

    for(int i = 0; i < f.size(); ++i){
        segment_2d seg{f.at(i), f.at((i + 1)%f.size())};
        if(intersect(seg, line_2d{p, point_2d{1,0}})){
            cuts += 1;
        }
    }

    return cuts % 2 == 1;
}

//check if face is cut by ray with origin of point and direction (1, 0, 0)
bool cut(face const& f, point const& p){

    if(f.normal == 0){
        //convert face and point to 2d

        if(p.x > f.points.at(0).x)
            return false;

        point_2d p_2d{p.y, p.z};
        vector<point_2d> face_2d;

        for(auto point : f.points) {
            face_2d.push_back({point.y, point.z});
        }

        //check if inside
        if(!inside(face_2d, p_2d))
            return false;

    } else if(f.normal == 1){
        if(p.y != f.points.at(0).y) {
            return false;
        } else {
            //convert face and point to 2d
            point_2d p_2d{p.x, p.z};
            vector<point_2d> face_2d;
            for(auto point : f.points) {
                face_2d.push_back({point.x, point.z});
            }

            //check if inside
            if(!inside(face_2d, p_2d))
                return false;
        }
    } else {
        if(p.z != f.points.at(0).z) {
            return false;
        } else {
            //convert face and point to 2d
            point_2d p_2d{p.x, p.y};
            vector<point_2d> face_2d;
            for(auto point : f.points) {
                face_2d.push_back({point.x, point.y});
            }
            //check if inside
            if(!inside(face_2d, p_2d))
                return false;
        }
    }
    return true;
}

int main() {
    //ifstream inFile ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\7\\in.txt");

    int cases, faces, points_n, tmp;
    cin >> cases;

    for(int i = 0; i < cases; ++i){
        int min_x = -1, min_y = -1, min_z = -1, max_x = -1, max_y = -1, max_z = -1;
        int itt = 0;
        cin >> faces;
        vector<face> faces_v {};
        int units = 0;
        for(int k = 0; k < faces; ++k){
            face tmp_f;
            cin >> points_n;
            vector<int> tmp_v {};
            for(int l = 0; l < points_n; ++l){
                point p {};
                for(int m = 0; m < 3; ++m) {
                    cin >> tmp;

                    if(m == 0)
                       p.x = tmp;
                    if(m == 1)
                        p.y = tmp;
                    if(m == 2)
                        p.z = tmp;

                    if(m == 0 && (min_x == -1 || tmp < min_x))
                        min_x = tmp;
                    if(m == 0 && (max_x == -1 || tmp > max_x))
                        max_x = tmp;
                    if(m == 1 && (min_y == -1 || tmp < min_y))
                        min_y = tmp;
                    if(m == 1 && (max_y == -1 || tmp > max_y))
                        max_y = tmp;
                    if(m == 2 && (min_z == -1 || tmp < min_z))
                        min_z = tmp;
                    if(m == 2 && (max_z == -1 || tmp > max_z))
                        max_z = tmp;
                }
                tmp_f.points.push_back(p);
            }

            point ab = tmp_f.points.at(0) - tmp_f.points.at(1);
            point bc = tmp_f.points.at(1) - tmp_f.points.at(2);
            point normal = cross_p(ab, bc);

            int n = -1;
            if(normal.x != 0)
                n = 0;
            if(normal.y != 0)
                n = 1;
            if(normal.z != 0)
                n = 2;

            tmp_f.normal = n;

            faces_v.push_back(tmp_f);
        }


        for(int j = min_x; j < max_x; ++j){
            for(int k = min_y; k < max_y; ++k){
                for(int l = min_z; l < max_z; ++l){
                    //check if point at (j,k,l) is inside
                    int cuts = 0;
                    for(const auto & o : faces_v){
                        point p{j + 0.5f,k + 0.5f,l + 0.5f};
                        //check how many faces ray (1,0,0) cuts starting from point (j,k,l)
                        if(cut(o, p)) {
                            cuts += 1;
                        }
                    }
                    itt += 1;
                    if(cuts % 2 == 1) {
                        units += 1;
                    }
                }
            }
        }

        cout << "The bulk is composed of " << units << " units." <<endl;
    }

    return 0;
}