// Copyright 2020, the Aether Development Team (see doc/dev_team.md for members)
// Full license can be found in License.md

#ifndef INCLUDE_GRID_H_
#define INCLUDE_GRID_H_

// The armadillo library is to allow the use of 3d cubes and other
// array types, with array math built in. This eliminates loops!
#include <armadillo>

#include "inputs.h"
#include "sizes.h"
#include "planets.h"
#include "times.h"

using namespace arma;

// We need a naming convention for the variables that are defined on
// the grid.  These could then match the formulas that are used to find
// the given points on the grid.
/*

  _ - delimiter between main variable name and descriptor
  1 - indication of whether variable is scalar (s) or vector (v)
  2 - physical dimensions:
      3 - 3d (e.g., lon, lat, alt or x, y, z)



For example:
  _s3gc : scalar variable, 3d, include ghost cells, cell centers
  _31ne :


 */

// scgc == scalar cube ghostcells at cell centers


// These are mapping functions from 3d to 1d arrays. They have to be
// pretty precise, which is a bit scary to me.
//
// Assume [Lon][Lat][Alt] layout

// Scalars, 3D, Include Ghostcells, Cell Centers:
#define ijk_geo_s3gc(i,j,k) \
  ((i)*long(nGeoLatsG)*long(nGeoAltsG) + \
   (j)*long(nGeoAltsG) + \
   (k))
#define ijk_mag_s3gc(i,j,k) \
  ((i)*long(nMagLatsG)*long(nGeoAltsG) + \
   (j)*long(nMagAltsG) + \
   (k))

// Scalars, 3D, Include Ghostcells, Cell Edges (Altitude):
#define ijk_geo_s3ge3(i,j,k) \
  ((i)*long(nGeoLatsG)*long(nGeoAltsG+1) + \
   (j)*long(nGeoAltsG+1) + \
   (k));

// Vectors, 3D, Include Ghostcells, Cell Centers:
#define ijkl_geo_v3gc(i,j,k,l) \
  ((i)*long(nGeoLatsG)*long(nGeoAltsG)*long(3) + \
   (j)*long(nGeoAltsG)*long(3) + \
   (k)*long(3) + \
   (l))
// Vectors, 3D, Include Ghostcells, Cell Centers:
#define ijkl_mag_v3gc(i,j,k,l) \
  ((i)*long(nMagLatsG)*long(nMagAltsG)*long(3) + \
   (j)*long(nMagAltsG)*long(3) + \
   (k)*long(3) + \
   (l))


class Grid {

public:

  int get_IsGeoGrid();
  void set_IsGeoGrid(int value);

  int64_t get_nPointsInGrid();

  int64_t get_nX();
  int64_t get_nY();
  int64_t get_nZ();

  int64_t get_nLons();
  int64_t get_nLats();
  int64_t get_nAlts();

  int64_t get_nGCs();

  // Armidillo Cube Versions:
  fcube geoLon_scgc, geoX_scgc;
  fcube geoLat_scgc, geoY_scgc;
  fcube geoAlt_scgc, geoZ_scgc;
  fcube geoLocalTime_scgc;
  
  // These define the magnetic grid:
  // Armidillo Cube Versions:
  fcube magLon_scgc, magX_scgc;
  fcube magLat_scgc, magY_scgc;
  fcube magAlt_scgc, magZ_scgc;
  fcube magLocalTime_scgc;

  std::vector<fcube> GSE_XYZ_vcgc;

  std::string altitude_name = "Altitude";
  std::string altitude_unit = "meters";

  std::string longitude_name = "Longitude";
  std::string longitude_unit = "radians";

  std::string latitude_name = "Latitude";
  std::string latitude_unit = "radians";

  // These are derived variables from the grid:

  // Switch to armadillo variables (float cubes):
  fcube radius_scgc;
  fcube radius2_scgc;
  fcube radius2i_scgc;
  fcube gravity_scgc;

  fcube sza_scgc;
  fcube cos_sza_scgc;

  fcube dalt_center_scgc;
  fcube dalt_lower_scgc;

  std::vector<fcube> bfield_vcgc;
  fcube bfield_mag_scgc;

  Grid(int nX_in, int nY_in, int nZ_in, int nGCs_in);

  void calc_sza(Planets planet, Times time, Report &report);
  void fill_grid(Planets planet, Report &report);
  void fill_grid_radius(Planets planet, Report &report);
  void init_geo_grid(Planets planet, Inputs input, Report &report);
  void fill_grid_bfield(Planets planet, Inputs input, Report &report);

 private:

  int IsGeoGrid;

  int64_t nX, nLons;
  int64_t nY, nLats;
  int64_t nZ, nAlts;

  int nGCs; // number of ghostcells

};

#endif  // INCLUDE_GRID_H_
