/*
    To run this example:
    $ bash scripts/compile.sh render_example && ./build/examples/render_example
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "rlly.hpp"
#include "render.h"


int main()
{
    rlly::render::GraphRender grender;
    rlly::render::TimeGraph2D graph;

    /**
     * Define graph
     */ 
    int n_objects = 12;
    int time = 4;
    rlly::utils::vec::vec_2d x_values = rlly::utils::vec::get_zeros_2d(n_objects, time);
    rlly::utils::vec::vec_2d y_values = rlly::utils::vec::get_zeros_2d(n_objects, time);
    rlly::utils::vec::vec_2d edges = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};


    for(int tt = 0; tt < time; tt ++)
    {
        for(int ii = 0; ii < n_objects; ii++)
        {
            float theta = 3.1415*ii/6.0 + tt;
            x_values[ii][tt] = 0.5*std::cos(theta); // (1.0*ii)/n_objects;
            y_values[ii][tt] = 0.5*std::sin(theta);//(1.0*ii)/n_objects;
        }
    }
    std::cout << "size = " << x_values.size() << std::endl;
    graph.set_nodes(x_values, y_values);
    graph.set_edges(edges);
    grender.set_graph(graph);

    /**
     * Render graph
     */
    grender.run_graphics();
    grender.run_graphics();
    grender.run_graphics();


    std::cout << "Back to execution!" << std::endl;

    std::cout << "hereeeee" << std::endl;
    return 0;
}