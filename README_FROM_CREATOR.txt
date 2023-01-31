Soooooo.....

I made it 4 - 3 days spending around 4 hours each day I think... Maybe more.
Most of the time I spend on designing how to connect everything and how to get slow motion
fmod sound playing which in the end could not figure out. But probably needed to play more
with FMOD stream and sound Hz. 

Added cooldown for shooting as otherwise you would destroy your ears.

A lot of things are still not finnished and there are still a lot of problems.
One of the problems is still with shooting when spacebar is being not released. (Drawing is not correct for some reason... something is going on)
The first bullet is being fired and dissapears while other bullet just goes fine.

I used fixed timestamp as it was faster at the moment to implement then the "Fix your timestamp" (article)

I thought about how to implement scene manager and went other way than other people usually do.
Instead of having each new same object with different positions on the tree. I create only that object once
with it's resources and when I want to add the same object to the tree. I just get that node
and add to it actors( basicly a bunch of instances of it (imagine particles) )

Then I thought about implementing Kd-tree for collsision detection. Sadly, I would have needed more time and experimentation with it. 
So it's not there. Just doing simple way. Looping trhough all alive asteroids and checking if any bullet or ship collided.

If thinking about implementing Kd-tree. Well. kd-tree probably would sit not with scenemanager but would be on it's own and it would have
pointer to all actors.


When we would be doing collision checking. We would get something
KdTree::GetNearest(forCurrentActor) - get nearest neighbour for current actor and check against it.
Also do not forget to re update kdtree for all active actors (ideasss......)

In the end I got really excited about this game as thought about implementing something like slow motion with film grain effect (old school tv effect)
So, will have second project now on my free time to finnish. As probably this will be my first properly finnished game then.
Had couple of games that I made 2-3 years ago. (They worked, but were not good).
One was on android (breakout - used I think libgdx) that made in week and one was when I was in first year uni.

All in all,
Enjoyed the test. Really different from the other companies I got.
Thanks for it :)

COMPILED WITH VS 2015