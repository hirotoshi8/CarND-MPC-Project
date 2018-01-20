# Write up for the MPC project

This is the project for the implementation of the Model Predicted Contoller(MPC).

This document discribes the below techniques about MPC.

- The vehicle model

- Predicted time lenght and duration

- Preprocess about MPC

- Latency

# 1. The vehicle model
This project represent the Vehicle model with kinematic model.
Kinematic model are simplification of dynamic model that ignores tire forces, gravity, and mass.

Due to the simplification, kinemataic model reduces its accuracy but it's enough for the simulation with low speed to approximate the actual vehicle dynamics.

The state vector of vehicle model have 4 elements( x-position, y-position, orientation, speed) and we add the 2 error elements(cross-track-error, orientation-error).

|state vector| Description|
|-----------|----------|
|$x$        |x-position|
|$y$        |y-position|
|$\psi$     |orientation|
|$v$        |sppeed|
|$cte$      |cross-track-error|
|$e\psi$    |orientation-error|

Addition to that, we use 2 input vector as the vehicle controlled.

|input vector| Description|
|-----------|-----|
|$\delta$   |control the steering angle|
|$a$        |control the accelation/brake as throttle|

Based on the above state and input vector, our kinematic model is defined by the following equation.
This formula predicts the time(t+1) state from time(t).

> $x_{t+1} = x_{t} + v_{t} * cos((psi_{t})*dt$ \
> $y_{t+1} = y_{t} + v_{t} * sin((psi_{t})*dt$ \
> $\psi_{t+1} = \psi_{t} + v_{t} / L_f* \delta *dt$ \
> $v_{t+1} = v_{t} + a_{t} *dt$ \
> $cte_{t+1} = f(x_{t}) - y_t + (v_{t} sin(e\psi_{t})*dt)$ \
> $e\psi_{t+1} = \psi_{t} - \psi des_{t} + (v_{t}/L_{t} * \delta_{t} *dt)$


# 2. Predicted time lenght and duration
MPC predicts the trajectory and we need to set the predicterd time length determined by N (time steps) and dt (time duration between actuations).


N * dt is the predicted time length in MPC.
So, these are the hyper parameters and we need to tune these ones struggle for the tradeoff between N and dt.
N is longer is better and dt is smaller is better.

In this project, N is 25[steps] and dt is 0.05[seconds] and this is good result in simulator. It seems enough to control the vehicle and predict the trajectory.

But, in the real world, I think the longer predicted time lenght has problem. Because, if the MPC control the vehicle based on its prediction over driver's one, maybe it's difficult for a driver to understand why the system control the vehicle.(There is dangerous ? or just a failure ? ) So, there is the possibility that driver resist the system control. This means the conflict is occured between the system and drivers.

We must control the vehicles safety using MPC and so on. On the other hand, we must also take care about the human interface. For example, to inform the reasson that system control the vehicle to the driver (and maybe neaby pedestrians).

# 3. MPC Preprocess
Before MPC, Preprocess is necessary as below.

The waypoint (expected x-y position) is given by the global coordinates. Therefore, this project transforms the waypoint to local coordinates(vehicle coordinates).
This means that the x-y positions and orientation can be zero in the initial state vector.

Then, "polyfit" function is 3rd order polynominal function and calculates the coefficients, fitting the waypoints transformed to local coordinates.
Based on this coefficients, we can get the cross-track-error and orientation-error.


# 4. Latency
In the real world, there is the time delay until appying the inputs to the accuators. This is called latency.

We have to take care of the latency and it's represented as "sleep" in main function in this project.
( Latency is set to 0.1[seconds].)

To consider the latency, I select the inputs vector as the actuation depending on the delay.
MPC returnts the predicted state and inputs vectors following the duration, which is defined as hyper parameters N*dt.
So, we adapt the future inputs vectors as the actuation to the vehicle according to the latency.