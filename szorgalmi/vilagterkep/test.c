#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <../../src/include/SDL2/SDL.h>
#include <../../src/include/SDL2/SDL2_gfxPrimitives.h>
#include <../../src/include/debugmalloc.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define SCALE_FACTOR 5  // Adjust this to make the map bigger or smaller

typedef struct {
    float lon;  // longitude
    float lat;  // latitude
} GeoPoint;

typedef struct {
    GeoPoint* points;
    int num_points;
} Polygon;

typedef struct {
    Polygon* polygons;
    int num_polygons;
} Map;

// Convert geographic coordinates to screen coordinates
SDL_Point geo_to_screen(float lon, float lat) {
    SDL_Point point;
    // Center the map and scale coordinates
    point.x = (int)((lon + 180) * SCALE_FACTOR) + (WINDOW_WIDTH / 4);
    point.y = (int)((90 - lat) * SCALE_FACTOR) + (WINDOW_HEIGHT / 4);
    return point;
}

// Count number of polygons in the data
int count_polygons(const float* data) {
    int count = 0;
    int i = 0;
    while (data[i] != -1) {
        if (data[i] == 0 && data[i + 1] == 0) {
            count++;
        }
        i += 2;
    }
    return count;
}

// Parse coordinates into polygon structures
Map parse_coordinates(const float* data) {
    Map map = { NULL, 0 };
    int max_polygons = count_polygons(data);
    map.polygons = malloc(max_polygons * sizeof(Polygon));
    if (!map.polygons) return map;

    int current_polygon = 0;
    int point_count = 0;
    int max_points = 1000;  // Initial buffer size for points

    GeoPoint* temp_points = malloc(max_points * sizeof(GeoPoint));
    if (!temp_points) {
        free(map.polygons);
        map.polygons = NULL;
        return map;
    }

    int i = 0;
    while (data[i] != -1) {
        if (data[i] == 0 && data[i + 1] == 0) {
            if (point_count > 0) {
                // Allocate and store the current polygon
                map.polygons[current_polygon].points = malloc(point_count * sizeof(GeoPoint));
                if (map.polygons[current_polygon].points) {
                    memcpy(map.polygons[current_polygon].points, temp_points, point_count * sizeof(GeoPoint));
                    map.polygons[current_polygon].num_points = point_count;
                    current_polygon++;
                }
                point_count = 0;
            }
        }
        else {
            if (point_count < max_points) {
                temp_points[point_count].lon = data[i];
                temp_points[point_count].lat = data[i + 1];
                point_count++;
            }
        }
        i += 2;
    }

    free(temp_points);
    map.num_polygons = current_polygon;
    return map;
}

// Free allocated memory
void cleanup_map(Map* map) {
    if (!map || !map->polygons) return;

    for (int i = 0; i < map->num_polygons; i++) {
        free(map->polygons[i].points);
    }
    free(map->polygons);
    map->polygons = NULL;
    map->num_polygons = 0;
}

int main(int argc, char* argv[]) {
    extern const float vilag[];  // External array declaration

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Geographic Visualization",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Parse the coordinate data
    Map map = parse_coordinates(vilag);
    if (!map.polygons) {
        fprintf(stderr, "Failed to parse coordinates\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw each polygon
        for (int i = 0; i < map.num_polygons; i++) {
            if (map.polygons[i].num_points < 2) continue;

            // Convert geographic coordinates to screen coordinates
            Sint16* vx = malloc(map.polygons[i].num_points * sizeof(Sint16));
            Sint16* vy = malloc(map.polygons[i].num_points * sizeof(Sint16));

            if (vx && vy) {
                for (int j = 0; j < map.polygons[i].num_points; j++) {
                    SDL_Point screen_point = geo_to_screen(
                        map.polygons[i].points[j].lon,
                        map.polygons[i].points[j].lat
                    );
                    vx[j] = screen_point.x;
                    vy[j] = screen_point.y;
                }

                // Draw the polygon
                aapolygonRGBA(renderer, vx, vy, map.polygons[i].num_points,
                    0, 0, 255, 255);  // Blue color
            }

            free(vx);
            free(vy);
        }

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    cleanup_map(&map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}