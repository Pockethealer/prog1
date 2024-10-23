#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <../../src/include/SDL2/SDL.h>
#include <../../src/include/SDL2/SDL2_gfxPrimitives.h>
#include <../../src/include/debugmalloc.h>

typedef struct Pont
{
    int x, y;
} Pont;

typedef struct Alakzat
{
    Pont *pontok;
    int pontok_szama
} Alakzat;

typedef struct Terkep
{
    Alakzat *alakzatok;
    int alakzatok_szama;
} Terkep;

int alakzatot_szamol(float *kordinatak)
{
    int mennyi = 0;
    for (int i = 0; kordinatak[i] != -1; i += 2)
    {
        if (kordinatak[i] == 0 && kordinatak[i + 1] == 0)
        {
            mennyi++;
        }
    }
    return mennyi;
}

int pontot_szamol(float *kordinatak, int keresett_alakzat)
{
    int pontok_szama = 0;
    int aktualis_alakzat = 0;
    for (int i = 0; kordinatak[i] != -1; i += 2)
    {
        if (kordinatak[i] == 0 && kordinatak[i + 1] == 0)
        {
            if (aktualis_alakzat = keresett_alakzat)
                return pontok_szama;
            else
                aktualis_alakzat++;
            pontok_szama = 0;
        }
        else
        {
            pontok_szama++
        }
    }
    return 0;
}

Terkep beolvas(const float *tomb)
{
    Terkep terkep = {NULL, 0};
    terkep.alakzatok_szama = alakzatot_szamol(tomb);
    terkep.alakzatok = malloc(terkep.alakzatok_szama * sizeof(Alakzat));
    if (terkep.alakzatok == NULL)
        return terkep;
    for (int i = 0; i < terkep.alakzatok_szama; i++)
    {
        int pontok_szama = pontot_szamol(tomb, i);
        terkep.alakzatok[i] = malloc(pontok_szama * sizeof(Pont))
    }

    int aktualis_alakzat = 0;
    int pontok_szama = 0;
    int max_points = 1000; // Initial buffer size for points

    GeoPoint *temp_points = malloc(max_points * sizeof(GeoPoint));
    if (!temp_points)
    {
        free(map.polygons);
        map.polygons = NULL;
        return map;
    }

    int i = 0;
    while (data[i] != -1)
    {
        if (data[i] == 0 && data[i + 1] == 0)
        {
            if (point_count > 0)
            {
                // Allocate and store the current polygon
                map.polygons[current_polygon].points = malloc(point_count * sizeof(GeoPoint));
                if (map.polygons[current_polygon].points)
                {
                    memcpy(map.polygons[current_polygon].points, temp_points, point_count * sizeof(GeoPoint));
                    map.polygons[current_polygon].num_points = point_count;
                    current_polygon++;
                }
                point_count = 0;
            }
        }
        else
        {
            if (point_count < max_points)
            {
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
void cleanup_map(Map *map)
{
    if (!map || !map->polygons)
        return;

    for (int i = 0; i < map->num_polygons; i++)
    {
        free(map->polygons[i].points);
    }
    free(map->polygons);
    map->polygons = NULL;
    map->num_polygons = 0;
}