//https://www.spoj.com/problems/ARITH/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

struct line{
    int whitespace = 0;
    vector<int> content;
    char op = 0;
    int lenght;
};

vector<int> operator+(vector<int> const& a, vector<int> const& b){
    vector<int> c;
    int la, lb, t, d, r, m, l;
    la = a.size();
    lb = b.size();
    d = 0;
    if(la < lb) {
        r = la;
        m = lb;
    } else {
        r = lb;
        m = la;
    }
    for(int i = 1; i <= r; ++i){
        t = a.at(a.size() - i) + b.at(b.size() - i);
        l = ((t % 10) + d) % 10;
        c.push_back(l);
        d = (t + d) / 10;
    }
    if(d > 0 && (la == lb)) {
        c.push_back(d);
        reverse(c.begin(), c.end());
        return c;
    }
    for(int j = r; j < m; ++j){
        if(la < lb) {
            t = b.at(b.size() - 1 - j) + d;
        } else {
            t = a.at(a.size() - 1 - j) + d;
        }
        c.push_back(t % 10);
        d = t / 10;
    }
    if(d > 0){
        c.push_back(d);
    }
    reverse(c.begin(), c.end());
    return c;
}

vector<int> operator-(vector<int> const& a, vector<int> const& b){
    vector<int> c {0};
    int ind = 1;
    int carry = 0;

    for(int k = 0; k < a.size(); ++k) {
        vector<int> add{1};
        bool t = false;


        for (int i = 0; i < ind - 1; ++i) {
            add.push_back(0);
        }
        int u = b.size() - ind;
        int v = c.size() - ind;

        int a1 = 0, a2 = 0;

        if(u >= 0) {
            a1 = b.at(b.size() - ind);
        }
        if(v >= 0) {
            a2 = c.at(c.size() - ind);
        }

        if ((a1 + a2 + carry) % 10 != a.at(a.size() - ind)) {
            t = true;
        } else {
            if(a1 + a2 + carry >= 10){
                carry = 1;
            }else {
                carry = 0;
            }
        }

        while (t) {
            c = c + add;
            a2 = c.at(c.size() - ind);
            if ((a1 + a2 + carry) % 10 == a.at(a.size() - ind)) {
                if ((a1 + a2 + carry) >= 10)
                    carry = 1;
                else
                    carry = 0;
                t = false;
            }
        }
        ind += 1;
    }
    return c;
}

vector<int> operator*(vector<int> const& a, int b){
    vector<int> c;
    c.push_back(0);
    for(int i = 0; i < b; i++){
        c = c + a;
    }
    return c;
}

vector<int> operator*(vector<int> const& a, vector<int> const& b){
    vector<int> c;
    c.push_back(0);
    for(int i = 0; i < b.size(); ++i){
        auto t = a * b.at(b.size() - 1 - i);
        for(int j = 0; j < i; ++j)
            t.push_back(0);
        c = c + t;
    }
    return c;
}

ostream& operator << (ostream& out, vector<int>const& vec){
    for(int i = 0; i < vec.size(); ++i){
        out << vec.at(i);
    }
    return out;
}

ostream& operator << (ostream& out, vector<line>& lines){
    //print all lines
    for(int i = 0; i < lines.size(); ++i){
        //if lines is a --- line calculate the start and end of the --- line
        if(lines.at(i).op == 1){
            lines.at(i).lenght = max({lines.at(i-1).whitespace + lines.at(i-1).lenght, lines.at(i+1).whitespace + lines.at(i+1).lenght});
            lines.at(i).whitespace = min({lines.at(i-1).whitespace, lines.at(i+1).whitespace});
        }
        //print the specified whitespaces for the current line
        for(int j = 0; j < lines.at(i).whitespace; ++j){
            out << " ";
        }
        //if operator was found and doesnt signal a --- line (--- line => op == 1)
        if(lines.at(i).op != 1) {
            //print out operator if operator was found
            if (lines.at(i).op != 0)
                out << lines.at(i).op;
            //print out content
            out << lines.at(i).content << endl;
        } else {
            //print --- line
            for(int j = lines.at(i).whitespace; j < lines.at(i).lenght; ++j){
                out << "-";
            }
            //end line
            out << endl;
        }
    }
    return out;
}

int main() {
    ifstream inFile ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\6\\arith.in.txt");


    ofstream out("out.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf());

    int cases, l_a, l_b, l_c;
    char op,tmp;
    inFile >> cases;

    for(int i = 0; i < cases; ++i){
        vector<int> a_v, b_v, c_v, empty_v;
        vector<line> lines;

        //read a to vec
        if(inFile.peek() == '\n')
            inFile.ignore(1);
        while ((inFile.peek() != '\n') && (inFile.peek() > 47) && (inFile >> tmp)){
            a_v.push_back(tmp - 48);
        }
        //read operator
        if(inFile.peek() == '\n')
            inFile.ignore(1);
        while ((inFile.peek() != '\n') && (inFile.peek() < 47) && (inFile >> tmp)){
            op = tmp;
        }
        //read b to vec
        if(inFile.peek() == '\n')
            inFile.ignore(1);
        while ((inFile.peek() != '\n') && (inFile.peek() > 47) && (inFile >> tmp)){
            b_v.push_back(tmp - 48);
        }

        //calculate final result
        if(op == 43){
            c_v = a_v + b_v;
        } else if(op == 45){
            c_v = a_v - b_v;
        } else if(op == 42){
            c_v = a_v * b_v;
        }

        l_a = a_v.size();
        l_b = b_v.size();
        l_c = c_v.size();

        int m = max({l_a, l_b + 1, l_c});

        //align the last digits of a and b
        if(l_a > l_b + 1) {
            lines.push_back({0, a_v, 0, l_a});
            lines.push_back({l_a - l_b - 1, b_v, op, l_b + 1});
        } else if (l_a == l_b + 1){
            lines.push_back({0, a_v, 0, l_a});
            lines.push_back({0, b_v, op, l_b + 1});
        } else {
            lines.push_back({l_b + 1 - l_a, a_v, 0, l_a});
            lines.push_back({0, b_v, op, l_b + 1});
        }

        //if addition or subtraction add --- line and result
        if(op == 43 || op == 45){
            lines.push_back({0, empty_v, 1, 0});
            lines.push_back({0, c_v,0, l_c});
            for(int i = 0; i < lines.size(); ++i){
                while(lines.at(i).whitespace + lines.at(i).lenght < m){
                    lines.at(i).whitespace += 1;
                }
            }
        }

        if(op == 42){
            vector<int> tmp;
            int tmp_l, itt = 1;

            //if b has more than one digit
            if(b_v.size() > 1) {
                vector<vector<int>> prec;
                for(int i = 0; i < 10; ++i){
                    prec.push_back(a_v * i);
                }
                //add --- line after b
                lines.push_back({0, empty_v, 1, 0});
                //for all digits of b
                while (itt <= b_v.size()) {
                    //calculate tmp result of a and the digit
                    tmp = prec.at(b_v.at(b_v.size() - itt));
                    tmp_l = tmp.size();
                    //add the tmp result to the lines
                    lines.push_back({0, tmp, 0, tmp_l});
                    //if not first itt
                    if(itt != 1) {
                        //shift all the lines above the current line one to the right
                        for (int i = 0; i < lines.size(); ++i) {
                            lines.at(i).whitespace += 1;
                        }

                        //if the tmp result has less digits shift its to the right until it is aligned correctly
                        int cur_l = lines.at(lines.size() - 1).whitespace + lines.at(lines.size() - 1).lenght;
                        int prev_l = lines.at(lines.size() - 2).whitespace + lines.at(lines.size() - 2).lenght - 1;
                        while (cur_l < prev_l) {
                            lines.at(lines.size() - 1).whitespace += 1;
                            cur_l += 1;
                        }

                        //if the tmp result is larger than the prev result shifts all prev lines one step to the right
                        while (cur_l > prev_l) {
                            for (int i = 0; i < lines.size() - 1; ++i) {
                                lines.at(i).whitespace += 1;
                            }
                            prev_l += 1;
                        }
                    } else {
                        //aligns the last digit of the first tmp result with the last digit of b
                        int cur_l = lines.at(lines.size() - 1).whitespace + lines.at(lines.size() - 1).lenght;
                        int prev_l = lines.at(lines.size() - 3).whitespace + lines.at(lines.size() - 3).lenght;
                        if (cur_l != prev_l) {
                            lines.at(lines.size() - 1).whitespace += prev_l - cur_l;
                        }
                    }
                    itt += 1;
                }
            } else {
                //if b has only one digit
                int max = -1;
                //find the length of the max line above the result
                for(int i = 0; i < lines.size(); ++i){
                    if(lines.at(i).whitespace + lines.at(i).lenght > max){
                        max = lines.at(i).whitespace + lines.at(i).lenght;
                    }
                }

                //if the result is longer than the max line, shift the former lines accordingly
                if(l_c > max){
                    for(int i = 0; i < lines.size(); ++i){
                        lines.at(i).whitespace += l_c - max;
                    }
                }
            }

            //find the minimum whitespace shift of all lines
            int m_w = -1;
            for(int i = 0; i < lines.size(); ++i){
                if(lines.at(i).whitespace < m_w || m_w == -1)
                    m_w = lines.at(i).whitespace;
            }

            if(b_v.size() == 1)
                m_w = 0;

            //remove the minimum whitespace amount from all the prev lines
            for(int i = 0; i < lines.size(); ++i){
                lines.at(i).whitespace = lines.at(i).whitespace - m_w;
            }

            //add the --- lines
            lines.push_back({0, empty_v,1,0});

            //removes the leading zeroes of the result
            int wc = 0;
            for(int i = 0; i < l_c - 1; ++i){
                if(c_v.size() != 1 && c_v.at(0) == 0) {
                    wc += 1;
                    c_v.erase(c_v.begin());
                } else {
                    break;
                }
            }

            l_c = c_v.size();
            //add the result c_v
            lines.push_back({0, c_v, 0, l_c});


        }

        //if second line is longer than last lines bring last lines to the same length as second line
        if(lines.at(1).lenght + lines.at(1).whitespace > lines.at(lines.size() - 1).lenght + lines.at(lines.size() - 1).whitespace){
            lines.at(lines.size() - 1).whitespace +=
                    lines.at(1).lenght + lines.at(1).whitespace - lines.at(lines.size() - 1).lenght + lines.at(lines.size() - 1).whitespace;
        }

        while(lines.at(lines.size() - 1).lenght + lines.at(lines.size() - 1).whitespace > lines.at(3).lenght + lines.at(3).whitespace){
            for(int i = 0; i < lines.size() - 1; ++i){
                lines.at(i).whitespace += 1;
            }
        }

        //print result to console
        cout << lines << endl;
    }
    return 0;
}