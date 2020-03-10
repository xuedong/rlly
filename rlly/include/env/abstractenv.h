#ifndef __RLLY_ABSTRACTMDP_H__
#define __RLLY_ABSTRACTMDP_H__

#include <string>
#include <random>
#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include "space.h"
#include "stepresult.h"
#include "utils.h"


/**
 * @file
 * @brief Contains abstract class for reinforcement learning environments
 */


namespace rlly
{
namespace env
{

/**
 * @brief Abstract class for reinforcement learning environments
 * @tparam S type of state variables  (e.g. int, std::vector<double>)
 * @tparam A type of action variables (e.g. int, std::vector<double>)
 * @tparam S_space type of state space  (e.g. spaces::Box, spaces::Discrete)
 * @tparam A_space type of action space (e.g. spaces::Box, spaces::Discrete)
 */
template <typename S, typename A, typename S_space, typename A_space>
class Env
{
protected:
    /**
     * Current state
     */
    S state;

public:
    Env() {};
    ~Env() {};

    /**
     * @brief Put environment in default state
     * @return Default state
     */
    virtual S reset()=0;

    /**
     * @brief Take a step in the MDP
     * @param action
     * @return An instance of mdp::StepResult containing the next state,
     * the reward and the done flag.
     */
    virtual StepResult<S> step(A action)=0;

    /**
     *  Environment identifier
     */
    std::string id;

    /**
     * Pointer to observation space
     */
    S_space observation_space;

    /**
     * Pointer to action space
     */   
    A_space action_space;

    /**
    * For random number generation
    */
    utils::rand::Random randgen;

    /**
     * Function to clone the environment
     */
    virtual std::unique_ptr<Env<S, A, S_space, A_space>> clone() const = 0;

    /**
     * Set the seed of randgen and seed of action space and observation space
     * The seed of randgen is set to _seed, the seed of action space is set to _seed+123
     * and the seed of observation space is set to _seed+456
     * Note: If _seed < 1,  we set _seed = std::rand()
     * @param _seed
     */
    virtual void set_seed(int _seed);
    
    /*

        Methods and attributes used for graph rendering

    */

    /**
     * Set to true if the environment supports 2D rendering.
     * To support 2D rendering, the derived class must:
     *     - set rendering2d_enabled to true
     *     - implement the method get_scene_for_render2d()
     *     - implement the method get_background_for_render()
     *     - optionally, change the value of refresh_interval_for_render2d 
     *     - optionally, define clipping_area_for_render2d;
     */
    bool rendering2d_enabled = false;

    /**
     * Retuns a scene (list of shapes) representing the state
     * @param state_var
     */
    virtual utils::render::Scene get_scene_for_render2d(S state_var) {return utils::render::Scene();};    
    
    /**
     * Retuns a scene (list of shapes) representing the background
     */
    virtual utils::render::Scene get_background_for_render2d(){return utils::render::Scene();};

    /**
     *  Refresh interval of rendering (in milliseconds)
     */
    int refresh_interval_for_render2d = 50;

    /**
     * Clipping area for rendering (left, right, bottom, top). Default = {-1.0, 1.0, -1.0, 1.0}
     */
    std::vector<float> clipping_area_for_render2d = {-1.0, 1.0, -1.0, 1.0};
}; 

template <typename S, typename A, typename S_space, typename A_space>
void Env<S, A, S_space, A_space>::set_seed(int _seed)
{
    if (_seed < 1) 
    {
        _seed = std::rand();
    }
    randgen.set_seed(_seed);
    observation_space.generator.seed(_seed+123);
    action_space.generator.seed(_seed+456);
}; 

}  // namespace env
}  // namespace rlly

#endif
