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
 * @tparam S_space type of state space  (e.g. spaces::Box, spaces::Discrete)
 * @tparam A_space type of action space (e.g. spaces::Box, spaces::Discrete)
 */
template <typename S_space, typename A_space>
class Env
{
public:
    Env() {};
    ~Env() {};


    /**
     * Observation space
     */
    S_space observation_space;

    /**
     * Action space
     */   
    A_space action_space;

    /**
     * type of state variables
     */
    using S_type = decltype(observation_space.sample());

    /**
     *  type of action variables
     */
    using A_type = decltype(action_space.sample());

    /**
     * @brief Put environment in default state
     * @return Default state
     */
    virtual S_type reset()=0;

    /**
     * @brief Take a step in the MDP
     * @param action
     * @return An instance of mdp::StepResult containing the next state,
     * the reward and the done flag.
     */
    virtual StepResult<S_type> step(A_type action)=0;

    /**
     *  Environment identifier
     */
    std::string id;

    /**
    * For random number generation
    */
    utils::rand::Random randgen;

    /**
     * Function to clone the environment
     */
    virtual std::unique_ptr<Env<S_space, A_space>> clone() const = 0;

    /**
     * Set the seed of randgen and seed of action space and observation space
     * The seed of randgen is set to _seed, the seed of action space is set to _seed+123
     * and the seed of observation space is set to _seed+456
     * Note: If _seed < 1,  we set _seed = std::rand()
     * @param _seed
     */
    virtual void set_seed(int _seed);
protected:
    /**
     * Current state
     */
    S_type state;

}; 

template <typename S_space, typename A_space>
void Env<S_space, A_space>::set_seed(int _seed)
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
