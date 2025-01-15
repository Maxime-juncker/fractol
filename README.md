fractol project of 42

## Goals
creating a fractal visualizer

## Features
- support mandelbrot, julia and burning ship
- infinite zoom (while your computer is good enought) `scroll wheel`
- you can move `wasd`
- reset camera `r`
- add / remove symmetry (work in mandelbrot and julia) `e / f`
- increase / decrease threashold `z / x`
- increase / decrease detail `+ / -`
- change color palette `1 / 2 / 3`

## Compile it yourself
clone the repo
```
git clone https://github.com/Maxime-juncker/fractol.git
cd fractol
```
build it using make
```
make
```
then run it

- mandelbrot: `./fractol 1`

- julia: `./fractol 2`

(with julia you can input the constant for example: `./fractol 2 -40 60`

- burning ship: `./fractol 3`
