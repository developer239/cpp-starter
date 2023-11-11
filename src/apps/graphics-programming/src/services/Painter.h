#pragma once

#include <SDL.h>
#include <cmath>
#include <cstdint>
#include <memory>
#include <vector>
#include "../structs/Triangle.h"
#include "Projector.h"

class Painter {
 public:
  std::shared_ptr<Projector> projector;
  int windowWidth;
  int windowHeight;

  std::vector<uint32_t> colorBuffer;
  SDL_Texture* colorBufferTexture = nullptr;

  Painter(int windowWidth, int windowHeight)
      : windowWidth(windowWidth),
        windowHeight(windowHeight),
        colorBuffer(windowWidth * windowHeight) {
    projector = std::make_shared<Projector>();
  }

  void Pixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < windowWidth && y >= 0 && y < windowHeight) {
      colorBuffer[y * windowWidth + x] = color;
    }
  }

  void Line(int x0, int y0, int x1, int y1, uint32_t color = 0xFFFF00FF) {
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;

    int sideLength = std::max(abs(deltaX), abs(deltaY));

    float xIncrement = deltaX / (float)sideLength;
    float yIncrement = deltaY / (float)sideLength;

    float currentX = x0;
    float currentY = y0;

    for (int i = 0; i <= sideLength; i++) {
      Pixel(std::round(currentX), std::round(currentY), color);
      currentX += xIncrement;
      currentY += yIncrement;
    }
  }

  void DrawScaledPixels(const std::vector<Vec2>& pixels) {
    for (Vec2 pixel : pixels) {
      Rectangle(
          pixel.x + windowWidth / 2,
          pixel.y + windowHeight / 2,
          4,
          4,
          0xFFFF00FF
      );
    }
  }

  void Triangle(
      int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color
  ) {
    Line(x0, y0, x1, y1, color);
    Line(x1, y1, x2, y2, color);
    Line(x2, y2, x0, y0, color);
  }

  void Rectangle(
      int x, int y, int width, int height, uint32_t color = 0xFFFFFF00
  ) {
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        int current_x = x + i;
        int current_y = y + j;

        Pixel(current_x, current_y, color);
      }
    }
  }

  void int_swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
  }

  void fill_flat_bottom_triangle(
      int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color
  ) {
    // Find the two slopes (two triangle legs)
    float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
    float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

    // Start x_start and x_end from the top vertex (x0,y0)
    float x_start = x0;
    float x_end = x0;

    // Loop all the scanlines from top to bottom
    for (int y = y0; y <= y2; y++) {
      Line(x_start, y, x_end, y, color);
      x_start += inv_slope_1;
      x_end += inv_slope_2;
    }
  }

  void fill_flat_top_triangle(
      int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color
  ) {
    // Find the two slopes (two triangle legs)
    float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
    float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

    // Start x_start and x_end from the bottom vertex (x2,y2)
    float x_start = x2;
    float x_end = x2;

    // Loop all the scanlines from bottom to top
    for (int y = y2; y >= y0; y--) {
      Line(x_start, y, x_end, y, color);
      x_start -= inv_slope_1;
      x_end -= inv_slope_2;
    }
  }

  void DrawFilledTriangle(
      int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color
  ) {
    // We need to sort the vertices by y-coordinate ascending (y0 < y1 < y2)
    if (y0 > y1) {
      int_swap(&y0, &y1);
      int_swap(&x0, &x1);
    }
    if (y1 > y2) {
      int_swap(&y1, &y2);
      int_swap(&x1, &x2);
    }
    if (y0 > y1) {
      int_swap(&y0, &y1);
      int_swap(&x0, &x1);
    }

    if (y1 == y2) {
      // Draw flat-bottom triangle
      fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
      // Draw flat-top triangle
      fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
    } else {
      // Calculate the new vertex (Mx,My) using triangle similarity
      int My = y1;
      int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

      // Draw flat-bottom triangle
      fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);

      // Draw flat-top triangle
      fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);
    }
  }

  void BackgroundGrid() {
    for (int y = 0; y < windowHeight; y += 10) {
      for (int x = 0; x < windowWidth; x += 10) {
        if (x % 10 == 0 || y % 10 == 0) {
          Pixel(x, y, 0xFFFFFFFF);
        }
      }
    }
  }

  void Render(Core::Renderer& renderer) {
    if (!colorBufferTexture) {
      colorBufferTexture = SDL_CreateTexture(
          renderer.Get().get(),
          SDL_PIXELFORMAT_ARGB8888,
          SDL_TEXTUREACCESS_STREAMING,
          windowWidth,
          windowHeight
      );
    }

    SDL_UpdateTexture(
        colorBufferTexture,
        nullptr,
        colorBuffer.data(),
        windowWidth * sizeof(uint32_t)
    );

    SDL_RenderCopy(renderer.Get().get(), colorBufferTexture, nullptr, nullptr);
  }

  void ClearColorBuffer(uint32_t color) {
    std::fill(colorBuffer.begin(), colorBuffer.end(), color);
  }
};
