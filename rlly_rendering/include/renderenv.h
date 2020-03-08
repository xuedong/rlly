/**
 * @file
 * @brief Contains class for rendering environments
 */


#ifndef __RLLY_RENDER_ENV_H__
#define __RLLY_RENDER_ENV_H__

#include <iostream>
#include <vector>
#include "render2d.h"
#include "utils.h"

namespace rlly
{
namespace render
{

/**
 * @param states list of states to render
 * @param env    environment
 * @tparam EnvType represents Env<S, A> (see abstractenv.h)
 * @tparam S type of state space
 */
template <typename EnvType, typename S>
void render_env(std::vector<S> states, EnvType& env)
{
    if (env.rendering2d_enabled)
    {
        // Background
        auto background = env.get_background_for_render2d();

        // Data
        std::vector<utils::render::Scene> data;    
        int n_data = states.size();
        for(int ii = 0; ii < n_data; ii++)
        {
            utils::render::Scene scene = env.get_scene_for_render2d(states[ii]);
            data.push_back(scene);
        }   

        // Render
        Render2D renderer;
        renderer.window_name = env.id;
        renderer.refresh_interval = env.refresh_interval_for_render2d;
        renderer.set_data(data);
        renderer.set_background(background);
        renderer.run_graphics();
    }
    else
    {
        std::cerr << "Error: environement " << env.id << " is not enabled for rendering (flag rendering2d_enabled is false)" << std::endl;
    }
    
}



} // namspace render
} // namespace rlly

#endif