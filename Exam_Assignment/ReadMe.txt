Minigin- By Dylan Millian

Explaining some design choices i have made

Components:
The entire system is made out of components, which can be added to gameObjects. they all have an update and a renderer minimum.
During the update and the render of the game, all of the components will be run over and they do their job


Animator:
-- The components --
We have two components that are key for animations to work, the texture component and the animator component. Because the animator component looks for a texture component when its doing its job.

-- The system -- 
when there is an animator component in place, it will dictate what texture is shown on the texture component, according to the current state of the parent object.
Internally the animator component also holds the frames, the textures, the width and height and also the speed of the animation.


Collision:
-- The components --
We have two collision components, one for checking and one who holds the data to check.
When you are a collidable object, you register yourself via the collision manager.
That way the collision checker can easily acces all the objects that are colliders via that manager

-- The system -- 
The collision checker will check each frame all the collision object to see if they collide, if they do then a command gets launched, which has the collider, and the collided together with the DeltaTime.
That way the command can easily handle everything.

Finite State machine:
-- The Components --
We only need one component for this one, the AI Component.
To add transition states you have to provide the parent, the goto state, the coming from state and a vector of boolean pointers which are the prerequisites from going from one state to another.

-- The System --
The Ai Component, has another internal class called a transition. the transition takes care of checking all the prerequisites and to usher the change of state.
Whilst the AI component calls these transitions by looping over a vector of these.

Enemy behaviour (Pooka and Fygar):
-- The components --
For this game i had two components a pooka and a fygar one, they handled things like moving and managed the prerequisite booleans given to the FSM. Their behaviour changed according to the state determined by the FSM

-- The System --
Both components had different behaviours according to their state.
For example:
Wandering - Run around the map
Ghosting - Fly around the map as a ghost
(Fygar) Firing - Stand still and fire 
The enemy behaviour relied on the FSM to determine what state it should be in.
and the behaviour supplied the certain booleans for the FSM to work

Score and lifes system:
For this i used the observer pattern, having a messenger tell the score and life system when a certain event occured like; EVENT_POOKADIEDFIRSTLAYER, EVENT_PLAYERDIED etc...
Other objects could then retrieve the information from these observers to display to the player





