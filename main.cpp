#include <iostream>
#include <utility>
#include <vector>
#include <deque>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <set>
#include <map>

using namespace std;

#define throw_if(c) if (c) { throw std::runtime_error(#c); }

typedef map< int, set<int> > array2_t;

void set_value (array2_t & a, int i, int j)
{
    a[i].insert(j);
}

int count_intersections (array2_t & wire, int h1, int h2)
{
    int c = 0;

    typedef array2_t::iterator A;
    typedef set<int>::iterator S;

    for (A it1 = wire.begin(); it1 != wire.upper_bound(h1-1); it1++)
    {
        set<int> & s = it1->second;
        for (S it2 = s.upper_bound(h2); it2 != s.end(); it2++)
            c++;
    }

    for (A it1 = wire.upper_bound(h1); it1 != wire.end(); it1++)
    {
        set<int> & s = it1->second;
        for (S it2 = s.begin(); it2 != s.upper_bound(h2-1); it2++)
            c++;
    }

    return c;
}



void rope_intranet(string input_file, string output_file)
{
    fstream in(input_file.c_str(), ios::in);
    fstream out(output_file.c_str(), ios::out);

    throw_if (!in.is_open());
    throw_if (!out.is_open());

    int T, N, h1, h2;
    in >> T;
    for (int i=1; i<=T; i++)
    {
        array2_t wirelist;
        int c = 0;
        in >> N;
        while (N--)
        {
            in >> h1 >> h2;
            c += count_intersections (wirelist, h1, h2);
            set_value (wirelist, h1, h2);
        }
        cout << "Case #" << i << ": " << c << "\n";
        out << "Case #" << i << ": " << c << "\n";
    }

    in.close();
    out.close();
}

int main()
{
    string path = "/Users/tyeung/Google Drive/google code jam/rope_intranet/";
    string filename = "A-large-practice";

    try
    {
        rope_intranet(path+filename+".in", path+filename+".txt");
    }
    catch (std::exception & e)
    {
        cout << "exception: " << e.what() << endl;
    }

    return 0;
}
