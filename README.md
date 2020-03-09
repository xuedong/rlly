# rlly - A C++ library for reinforcement learning environments (under development)

![C/C++ CI](https://github.com/omardrwch/rlly/workflows/C/C++%20CI/badge.svg)

The goal of __rlly__ is to implement simple environments for reinforcement learning algorithms in C++, with an interface similar to the [OpenAI gym](https://gym.openai.com/) library for Python.

## Requirements

* C++ 17

* For rendering:
    * OpenGL
    * [freeglut](http://freeglut.sourceforge.net/) 
        ```console
        $ sudo apt-get install freeglut3-dev
        ```
    * __Remark:__ It is possible to use the library without rendering options and avoid these requirements.

* To run the notebooks in `examples`:
    * Jupyter notebook `conda install -c anaconda jupyter`
    * [xeus-cling](https://xeus-cling.readthedocs.io/en/latest/)  `conda install -c conda-forge xeus-cling`


## How to use the library

All you have to do is to copy the file `rlly.hpp` and use it in your project.

The file `rlly.hpp` is generated by running

```console
$ bash generate_header/run.sh
```

and does not include rendering classes and functions by default.

To include code for rendering in `rlly.hpp`, run

```console
$ bash generate_header/run.sh -rendering
```

## Examples

The examples below show how to interact with some __rlly__ envinroments and how to visualize them. For more examples, see folder `examples/`.


### MountainCar 

```cpp
#include <vector>
// the header needs to be generated with -rendering option
#include "rlly.hpp"

int main()
{
    rlly::env::MountainCar env;
    env.set_seed(123);

    int horizon = 200;
    rlly::utils::vec::vec_2d states; // or std::vector<std::vector<double>> states;
    for(int hh = 0; hh < horizon; hh++)
    {
        auto action = env.action_space.sample();
        auto step_result = env.step(action);
        states.push_back(step_result.next_state);
    }

    rlly::render::render_env(states, env);
    return 0;
}
```

![alt text](https://github.com/omardrwch/rlly/blob/master/figures/MountainCar.png "MountainCar rendering")


### CartPole

```cpp
#include <iostream>
#include <vector>
#include "rlly.hpp"

int main()
{
    rlly::env::CartPole env;

    std::vector<double> state = env.reset();
    rlly::utils::vec::vec_2d states;

    int horizon = 200;
    for(int ii = 0; ii < horizon; ii++)
    {
        auto action = env.action_space.sample();
        auto step_result = env.step(action);
        states.push_back(step_result.next_state);
        if (step_result.done) break;
    }

    rlly::render::render_env(states, env);
    return 0;
}
```

![alt text](https://github.com/omardrwch/rlly/blob/master/figures/CartPole.png "CartPole rendering")


### GridWorld

```cpp
#include <iostream>
#include <vector>
#include "rlly.hpp"

int main(void)
{
    double fail_prob = 0.0;          // failure probability
    double reward_smoothness = 0.0;  // reward = exp( - distance(next_state, goal_state)^2 / reward_smoothness^2)
    double sigma = 0.1;              // reward noise (Gaussian)
    rlly::env::GridWorld env(5, 10, fail_prob, reward_smoothness, sigma);
    env.set_seed(123);

     // Rendering (graphic)
    int state = env.reset();
    std::vector<int> states;
    int horizon = 50;
    for(int hh = 0; hh < horizon; hh++)
    {
        int action = env.action_space.sample();
        auto step_result = env.step(action);
        states.push_back(step_result.next_state);
    }
    rlly::render::render_env(states, env);

    // Rendering (text)
    env.render();
    return 0;
}
```

![alt text](https://github.com/omardrwch/rlly/blob/master/figures/GridWorld.png "GridWorld rendering")



## Documentation

To view the documentation, run

```
doxygen Doxyfile
```

and open the file `docs/html/index.html`.


## Testing

### Creating a new test

* Create a file `test/my_test.cpp` using [Catch2](https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md).

* In the file `test/CMakeLists.txt`, include `my_test.cpp` in the list of files in `add_executable()`.

* Run

```
$ bash scripts/run_tests.sh
```

