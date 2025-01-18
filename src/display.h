#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * Initializes the SDL library for video subsystem and prints the SDL version information to the console.
 * If initialization fails, it logs an error message and terminates the program with a failure status.
 * 
 */
void init_SDL();


/**
 * Logs an error message along with the SDL error message to the console, quits the SDL subsystems, and terminates the program with a failure status.
 *
 * @param message The custom error message to display.
 */
void SDL_ExitWithError(const char *message);

/**
 * Sets the pixel color at the given coordinates on the SDL renderer to the current color.
 *
 * @param render The SDL renderer to draw on.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 */
void set_pixel (SDL_Renderer* render, int x, int y);

/**
 * Draws a line between the two given points on the SDL renderer with the specified color.
 *
 * @param render The SDL renderer to draw on.
 * @param x1 The x-coordinate of the starting point of the line.
 * @param y1 The y-coordinate of the starting point of the line.
 * @param x2 The x-coordinate of the ending point of the line.
 * @param y2 The y-coordinate of the ending point of the line.
 * @param color The color of the line (SDL_Color struct with RGB and alpha values).
 */
void draw_line (SDL_Renderer* render, int x1, int y1, int x2, int y2, SDL_Color color);

/**
 * Draws a rectangle on the SDL renderer with the specified color and coordinates.
 *
 * @param render The SDL renderer to draw on.
 * @param x1 The x-coordinate of the top-left corner of the rectangle.
 * @param y1 The y-coordinate of the top-left corner of the rectangle.
 * @param x2 The x-coordinate of the bottom-right corner of the rectangle.
 * @param y2 The y-coordinate of the bottom-right corner of the rectangle.
 * @param color The color of the rectangle (SDL_Color struct with RGB and alpha values).
 */
void draw_rectangle(SDL_Renderer* render, int x1, int y1, int x2, int y2, SDL_Color color);

/**
 * Draws a filled rectangle on the SDL renderer with the specified color and coordinates.
 *
 * @param render The SDL renderer to draw on.
 * @param x1 The x-coordinate of the top-left corner of the rectangle.
 * @param y1 The y-coordinate of the top-left corner of the rectangle.
 * @param x2 The x-coordinate of the bottom-right corner of the rectangle.
 * @param y2 The y-coordinate of the bottom-right corner of the rectangle.
 * @param color The color of the rectangle (SDL_Color struct with RGB and alpha values).
 */
void draw_fill_rectangle(SDL_Renderer* render, int x1, int y1, int x2, int y2, SDL_Color color);

/**
 * Draws an empty circle on the SDL renderer with the specified color and center coordinates.
 *
 * @param render The SDL renderer to draw on.
 * @param x0 The x-coordinate of the center of the circle.
 * @param y0 The y-coordinate of the center of the circle.
 * @param radius The radius of the circle.
 * @param color The color of the circle (SDL_Color struct with RGB and alpha values).
 */
void draw_circle(SDL_Renderer* render, int x0, int y0, int radius, SDL_Color color);

/**
 * Draws a filled circle on the SDL renderer with the specified color and center coordinates.
 *
 * @param render The SDL renderer to draw on.
 * @param x0 The x-coordinate of the center of the circle.
 * @param y0 The y-coordinate of the center of the circle.
 * @param radius The radius of the circle.
 * @param color The color of the circle (SDL_Color struct with RGB and alpha values).
 */
void draw_fill_circle(SDL_Renderer* render, int x0, int y0, int radius, SDL_Color color);


#endif