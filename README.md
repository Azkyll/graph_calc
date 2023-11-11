# Simple graphic calculator for the refined egirl

## Graphic calculator in development, using C++ & SFML 2.5.1.

This program is a basis for future works, but should, in the end, be shipped as a standalone app.

## Current functionality
Draw functions from user input. Currently supported functions : cos, sin, tan, exp, log, constants, identity, cosh, sinh, tanh. Currently supported operations : +, -, \*, /, composition, a^b. Doesn't handle writing negative numbers pretty well -- use "0 - f" when you want to use -f.

What **SHOULD** it do?
  Create function objects from input streams and draw them on the current window.

What **WILL** it eventually (hopefully) do?
  Allow the user to create, draw and manually handle functions, both using in-window keyboard input to interact with the functional/mathematical object, and the mouse to interact with the curve of the function. It will also eventually be linked to a sampler.

## TODO
  - implement complex operation on functions, like differentiating and integrating them, or take convolutions, correlations, transforms and such
  - expand and make a full GUI
