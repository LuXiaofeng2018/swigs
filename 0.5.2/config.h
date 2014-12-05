/* config.h.  Generated from config.h.in by configure.  */
/*
SWIGS (Shallow Water in Irregular Geometries Simulator): a software to simulate
transient or steady flows with solute transport in channels, channel networks
and rivers.

Copyright 2005-2014 Javier Burguete Tolosa.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice,
		this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
		this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Javier Burguete Tolosa ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL Javier Burguete Tolosa OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * \file config.h.in
 * \brief Header file to define configuration macros. To analyze the options see
 *   the file "def.h".
 * \authors Javier Burguete Tolosa.
 * \copyright Copyright 2005-2014 Javier Burguete Tolosa.
 */
#ifndef CONFIG__H
#define CONFIG__H 1

// Macros to define configuration options

/**
 * \def INTERFACE
 * \brief Macro to select the user interface.
 * \def GUAD2D
 * \brief Macro to select the user couplement with Guad2D (0: not, 1: yes)
 * \def BLOCK_REALLOC
 * \brief Buffer size to optimize memory reallocations.
 * \def DEBUG_TIME
 * \brief Macro selecting the simulation time to start the debug process.
 * \def MAXIMUM_SOLUTION_ERROR
 * \brief Maximum allowed error in discharge in steady initial conditions.
 * \def CFL_DEFAULT
 * \brief Default CFL number.
 * \def flow_implicit
 * \brief Implicit coefficient for source terms.
 * \def FRICTION_CFL
 * \brief Number controlling the maximum time step size allowed by friction.
 */
#define INTERFACE INTERFACE_MARKET
#define GUAD2D 0
#define BLOCK_REALLOC 1024
#define DEBUG_TIME 0.
#define MAXIMUM_SOLUTION_ERROR 1e-11
#define CFL_DEFAULT 0.9
#define flow_implicit 0.5
#define FRICTION_CFL 20.

#define SECTION_WIDTH_MIN 0.01
#define DEPTH_MIN 1
#define FLOW_DEPTH_MIN 0.01
#define FRICTION_DZ 0.1
#define GRANULOMETRIC_COEFFICIENT 0.12
#define friction_b (1./6.)
#define DIFFUSION_CONSTANT 10.

#define MESH_BOUNDARY MESH_BOUNDARY_REDUCED

#define MODEL_FRICTION MODEL_FRICTION_MINIMIZATION_LOSS
#define MODEL_FRICTION_STRESS MODEL_FRICTION_STRESS_B
#define MODEL_PRESSURE MODEL_PRESSURE_STRONG_SLOPE
#define MODEL_DIFFUSION	MODEL_DIFFUSION_B
#define MODEL_VISCOSITY MODEL_VISCOSITY_NULL

#define TMAX TMAX_POINT

#define BOUNDARY_FLOW BOUNDARY_FLOW_GLOBAL

#define FLOW_LINEARIZATION FLOW_LINEARIZATION_ROE

#define FLOW_ENTROPY_CORRECTION FLOW_ENTROPY_CORRECTION_MEAN_MEAN
#define FLOW_ENTROPY FLOW_ENTROPY_CHARACTERISTIC

#define TRANSPORT_DISCRETIZATION TRANSPORT_DISCRETIZATION_COUPLED

#define FLUX_LIMITER_DISCRETIZATION FLUX_LIMITER_DISCRETIZATION_CHARACTERISTIC
#define FLOW_FLUX_LIMITER FLOW_FLUX_LIMITER_MONOTONIZED_CENTRAL
#define TRANSPORT_FLUX_LIMITER TRANSPORT_FLUX_LIMITER_MONOTONIZED_CENTRAL

#define FLOW_WAVE_DECOMPOSITION FLOW_WAVE_DECOMPOSITION_TVD2
#define DIFFUSION_SCHEME DIFFUSION_SCHEME_EXPLICIT
#define TRANSPORT_SCHEME_PARAMETERS TRANSPORT_SCHEME_PARAMETERS_UPWIND2
#define TRANSPORT_SCHEME TRANSPORT_SCHEME_TVD2
#define TRANSPORT_SCHEME_DIFFUSION 1

#define FRICTION_EXPLICIT FRICTION_EXPLICIT_UPWIND
#define FRICTION_LIMITATION 1

// Macros to debug functions

#define DEBUG_POINT2_COPY										0
#define DEBUG_POINT2_OPEN										0
#define DEBUG_POINT3_COPY										0
#define DEBUG_POINT3_OPEN										0
#define DEBUG_SECTION_POINT_COPY								0
#define DEBUG_SECTION_POINT_OPEN								0
#define DEBUG_SECTION_POINT2_COPY								0
#define DEBUG_SECTION_POINT2_OPEN								0
#define DEBUG_SECTION_POINT_TRANSFORM							0
#define DEBUG_TRANSIENT_SECTION_ERROR							0
#define DEBUG_TRANSIENT_SECTION_DELETE							0
#define DEBUG_TRANSIENT_SECTION_CREATE							0
#define DEBUG_TRANSIENT_SECTION_COPY							0
#define DEBUG_TRANSIENT_SECTION_TRANSFORM						0
#define DEBUG_TRANSIENT_SECTION_OPEN_XML						0
#define DEBUG_TRANSIENT_SECTION_SAVE_XML						0
#define DEBUG_INITIAL_FLOW_ERROR								0
#define DEBUG_INITIAL_FLOW_DELETE								0
#define DEBUG_INITIAL_FLOW_COPY									0
#define DEBUG_INITIAL_FLOW_ORDER								0
#define DEBUG_INITIAL_FLOW_OPEN_XML								0
#define DEBUG_INITIAL_FLOW_SAVE_XML								0
#define DEBUG_INITIAL_TRANSPORT_ERROR							0
#define DEBUG_INITIAL_TRANSPORT_DELETE							0
#define DEBUG_INITIAL_TRANSPORT_COPY							0
#define DEBUG_INITIAL_TRANSPORT_ORDER							0
#define DEBUG_INITIAL_TRANSPORT_OPEN_XML						0
#define DEBUG_INITIAL_TRANSPORT_SAVE_XML						0
#define DEBUG_CROSS_SECTION_ERROR								0
#define DEBUG_CROSS_SECTION_DELETE								0
#define DEBUG_CROSS_SECTION_CREATE								0
#define DEBUG_CROSS_SECTION_COPY								0
#define DEBUG_CROSS_SECTION_ORDER								0
#define DEBUG_CROSS_SECTION_OPEN_XML							0
#define DEBUG_CROSS_SECTION_SAVE_XML							0
#define DEBUG_CROSS_SECTION_GET_TRANSIENT						0
#define DEBUG_CHANNEL_GEOMETRY_ERROR							0
#define DEBUG_CHANNEL_GEOMETRY_DELETE_ACTUALIZE_X				0
#define DEBUG_CHANNEL_GEOMETRY_DELETE_SECTION					0
#define DEBUG_CHANNEL_GEOMETRY_INSERT_SECTION					0
#define DEBUG_CHANNEL_GEOMETRY_DELETE							0
#define DEBUG_CHANNEL_GEOMETRY_COPY								0
#define DEBUG_CHANNEL_GEOMETRY_OPEN_XML							0
#define DEBUG_CHANNEL_GEOMETRY_SAVE_XML							0
#define DEBUG_BOUNDARY_FLOW_ERROR								0
#define DEBUG_BOUNDARY_FLOW_DELETE								0
#define DEBUG_BOUNDARY_FLOW_COPY								0
#define DEBUG_BOUNDARY_FLOW_OPEN_XML							0
#define DEBUG_BOUNDARY_FLOW_SAVE_XML							0
#define DEBUG_BOUNDARY_FLOW_PARAMETER							0
#define DEBUG_BOUNDARY_FLOW_PARAMETER2							0
#define DEBUG_BOUNDARY_FLOW_PARAMETER_INTEGRAL					0
#define DEBUG_BOUNDARY_TRANSPORT_ERROR							0
#define DEBUG_BOUNDARY_TRANSPORT_DELETE							0
#define DEBUG_BOUNDARY_TRANSPORT_COPY							0
#define DEBUG_BOUNDARY_TRANSPORT_OPEN_XML						0
#define DEBUG_BOUNDARY_TRANSPORT_SAVE_XML						0
#define DEBUG_BOUNDARY_TRANSPORT_PARAMETER						0
#define DEBUG_TRANSPORT_ERROR									0
#define DEBUG_TRANSPORT_DELETE									0
#define DEBUG_TRANSPORT_CREATE									0
#define DEBUG_TRANSPORT_COPY									0
#define DEBUG_TRANSPORT_OPEN_XML								0
#define DEBUG_TRANSPORT_SAVE_XML								0
#define DEBUG_CHANNEL_TRANSPORT_ERROR							0
#define DEBUG_CHANNEL_TRANSPORT_DELETE_BT						0
#define DEBUG_CHANNEL_TRANSPORT_INSERT_BT						0
#define DEBUG_CHANNEL_TRANSPORT_DELETE							0
#define DEBUG_CHANNEL_TRANSPORT_CREATE							0
#define DEBUG_CHANNEL_TRANSPORT_COPY							0
#define DEBUG_CHANNEL_TRANSPORT_PARSE_NODE						0
#define DEBUG_CHANNEL_TRANSPORT_OPEN_XML						0
#define DEBUG_CHANNEL_TRANSPORT_SAVE_XML						0
#define DEBUG_CHANNEL_ERROR										0
#define DEBUG_CHANNEL_DELETE_BF									0
#define DEBUG_CHANNEL_INSERT_BF									0
#define DEBUG_CHANNEL_DELETE									0
#define DEBUG_CHANNEL_COPY										0
#define DEBUG_CHANNEL_BOUNDARY_TEST								0
#define DEBUG_CHANNEL_PARSE_NODE								0
#define DEBUG_CHANNEL_OPEN_XML									0
#define DEBUG_CHANNEL_SAVE_XML									0
#define DEBUG_SYSTEM_ERROR										0
#define DEBUG_SYSTEM_INIT										0
#define DEBUG_SYSTEM_DELETE										0
#define DEBUG_SYSTEM_COPY										0
#define DEBUG_SYSTEM_CHANNEL_TRANSPORT_TEST						0
#define DEBUG_SYSTEM_JUNCTIONS_TEST								0
#define DEBUG_SYSTEM_CREATE										0
#define DEBUG_SYSTEM_PARSE_NODE									0
#define DEBUG_SYSTEM_OPEN_XML									0
#define DEBUG_SYSTEM_SAVE_XML									0
#define DEBUG_WAVE_VELOCITY										0
#define DEBUG_SECTION_PARAMETERS_PRINT							0
#define DEBUG_FRICTION_PARAMETERS_PRINT							0
#define DEBUG_SECTION_PRINT										0
#define DEBUG_SECTION_TRAPEZOIDAL_LEVEL							0
#define DEBUG_SECTION_LEVEL										0
#define DEBUG_SECTION_BETA										0
#define DEBUG_SECTION_WIDTH										0
#define DEBUG_SECTION_WIDTH_WITH_AREA							0
#define DEBUG_SECTION_PERIMETER									0
#define DEBUG_SECTION_PERIMETER_WITH_AREA						0
#define DEBUG_SECTION_PERIMETER_WITH_DEPTH						0
#define DEBUG_SECTION_AREA										0
#define DEBUG_SECTION_AREA_WITH_DEPTH							0
#define DEBUG_SECTION_WAVE_VELOCITY								0
#define DEBUG_SECTION_CRITICAL_DISCHARGE						0
#define DEBUG_SECTION_CRITICAL_FUNCTION							0
#define DEBUG_SECTION_CRITICAL_AREA								0
#define DEBUG_SECTION_DELETE									0
#define DEBUG_SECTION_CREATE									0
#define DEBUG_SECTION_COPY										0
#define DEBUG_SECTION_BM										0
#define DEBUG_SECTION_BL										0
#define DEBUG_SECTION_BR										0
#define DEBUG_SECTION_BC										0
#define DEBUG_SECTION_B											0
#define DEBUG_SECTION_P											0
#define DEBUG_SECTION_RHPA										0
#define DEBUG_SECTION_RHPB										0
#define DEBUG_SECTION_RHPC										0
#define DEBUG_SECTION_RHLA										0
#define DEBUG_SECTION_RHLB										0
#define DEBUG_SECTION_RHLC										0
#define DEBUG_SECTION_RHA										0
#define DEBUG_SECTION_RHB										0
#define DEBUG_SECTION_RHC										0
#define DEBUG_SECTION_RI										0
#define DEBUG_SECTION_OPEN_PARAMETERS							0
#define DEBUG_SECTION_OPEN										0
#define DEBUG_CHANNEL_SEGMENT_PRINT								0
#define DEBUG_CHANNEL_SEGMENT_DELETE							0
#define DEBUG_CHANNEL_SEGMENT_OPEN_SECTION						0
#define DEBUG_CHANNEL_SEGMENT_OPEN								0
#define DEBUG_SECTION_CHANGES_PRINT								0
#define DEBUG_SECTION_CHANGES_TMAX								0
#define DEBUG_LIST_SECTION_CHANGES_PRINT						0
#define DEBUG_LIST_SECTION_CHANGES_TMAX							0
#define DEBUG_LIST_SECTION_CHANGES_OPEN							0
#define DEBUG_SECTION_GAUGE_PRINT								0
#define DEBUG_SECTION_GAUGE_TMAX								0
#define DEBUG_LIST_SECTION_GAUGE_PRINT							0
#define DEBUG_LIST_SECTION_GAUGE_TMAX							0
#define DEBUG_LIST_SECTION_GAUGE_OPEN							0
#define DEBUG_LIST_VARIABLE_SEGMENTS_OPEN						0
#define DEBUG_PARAMETERS_PRINT									0
#define DEBUG_MASS_START										0
#define DEBUG_MASS_COPY											0
#define DEBUG_FLOW_MASS											0
#define DEBUG_FLOW_MASS_ERROR									0
#define DEBUG_TRANSPORT_MASS									0
#define DEBUG_TRANSPORT_MASS_ERROR								0
#define DEBUG_TRANSPORT_VARIABLES_INTERPOLATE					0
#define DEBUG_TRANSPORT_VARIABLES_OPEN							0
#define DEBUG_VARIABLES_CREATE									0
#define DEBUG_MESH_HMIN											0
#define DEBUG_MESH_ACTUALIZE									0
#define DEBUG_INITIAL_VARIABLES_OPEN							0
#define DEBUG_PART_OPEN											0
#define DEBUG_PART_OPEN_EXIT									0
#define DEBUG_SORT_INT											0
#define DEBUG_SORT_INVERSE_INT									0
#define DEBUG_SYSTEM_LIST										0
#define DEBUG_JUNCTION_DELETE									0
#define DEBUG_JUNCTION_CREATE									0
#define DEBUG_JUNCTION_ADD_PARAMETER							0
#define DEBUG_JUNCTION_ADD_INLET								0
#define DEBUG_JUNCTION_ADD_OUTLET								0
#define DEBUG_JUNCTION_ADD_TRIBUTARY							0
#define DEBUG_JUNCTION_SET_VOLUMES								0
#define DEBUG_JUNCTIONS_DELETE									0
#define DEBUG_JUNCTIONS_OPEN									0
#define DEBUG_MESH_DELETE										0
#define DEBUG_MESH_OPEN											0
#define DEBUG_MODEL_FRICTION									0
#define DEBUG_MODEL_VISCOSITY_TURBULENT							0
#define DEBUG_MODEL_DIFFUSION									0
#define DEBUG_TRANSPORT_PARAMETERS_SATURATION					0
#define DEBUG_TRANSPORT_PARAMETERS_NODE							0
#define DEBUG_TRANSPORT_PARAMETERS_CELL							0
#define DEBUG_PARAMETERS_WAVE_VELOCITY							0
#define DEBUG_PARAMETERS_NODE									0
#define DEBUG_PARAMETERS_CELL									0
#define DEBUG_FLOW_DRY_CORRECTION								0
#define DEBUG_FLOWS												0
#define DEBUG_CHANNEL_DRY_CORRECTION							0
#define DEBUG_CHANNEL_DRY_CORRECTION_EXIT						0
#define DEBUG_SYSTEM_DRY_CORRECTION_PARALLEL					0
#define DEBUG_SYSTEM_DRY_CORRECTION_SIMPLE						0
#define DEBUG_CHANGE_SECTIONS									0
#define DEBUG_LIST_SECTION_GAUGE_STEP							0
#define DEBUG_DIFFUSION_PARAMETERS_EXPLICIT_EXPLICIT			0
#define DEBUG_DIFFUSION_PARAMETERS_EXPLICIT_IMPLICIT			0
#define DEBUG_DIFFUSION_PARAMETERS_IMPLICIT_EXPLICIT			0
#define DEBUG_TRANSPORT_SCHEME_PARAMETERS_UPWIND				0
#define DEBUG_TRANSPORT_SCHEME_PARAMETERS_UPWIND2				0
#define DEBUG_TRANSPORT_SCHEME_UPWIND							0
#define DEBUG_TRANSPORT_SCHEME_TVD								0
#define DEBUG_TRANSPORT_SCHEME_TVD2								0
#define DEBUG_TRANSPORT_SCHEME_DIFFUSION						0
#define DEBUG_TRANSPORT_SCHEME_CONTRIBUTIONS_UPWIND				0
#define DEBUG_TRANSPORT_SCHEME_INLET_UPWIND						0
#define DEBUG_TRANSPORT_SCHEME_OUTLET_UPWIND					0
#define DEBUG_TRANSPORT_BOUNDARY								0
#define DEBUG_PART_PARAMETERS									0
#define DEBUG_PART_PARAMETERS_EXIT								0
#define DEBUG_SYSTEM_PARAMETERS_PARALLEL						0
#define DEBUG_SYSTEM_PARAMETERS_SIMPLE							0
#define DEBUG_PART_PARAMETERS2									0
#define DEBUG_PART_PARAMETERS2_EXIT								0
#define DEBUG_BOUNDARY_FLOW_TMAX								0
#define DEBUG_SYSTEM_PARAMETERS2_PARALLEL						0
#define DEBUG_SYSTEM_PARAMETERS2_SIMPLE							0
#define DEBUG_FLOW_LINEARIZATION								0
#define DEBUG_VARIABLES_ACTUALIZE								0
#define DEBUG_FLOW												0
#define DEBUG_FLOW_WAVE_UPWIND									0
#define DEBUG_FLOW_WAVE_UPWIND2									0
#define DEBUG_FLOW_ENTROPY_CORRECTION							0
#define DEBUG_FLOW_ENTROPY_WAVE									0
#define DEBUG_FLOW_ENTROPY										0
#define DEBUG_FLOW_PARAMETERS_UPWIND							0
#define DEBUG_FLOW_PARAMETERS_UPWIND2							0
#define DEBUG_FLOW_INNER_BOUNDARY								0
#define DEBUG_FLOW_WAVE_DECOMPOSITION_UPWIND					0
#define DEBUG_FLOW_WAVE_DECOMPOSITION							0
#define DEBUG_FLOW_FRICTION_EXPLICIT							0
#define DEBUG_FLOW_INLET_EXPLICIT								0
#define DEBUG_FLOW_OUTLET_EXPLICIT								0
#define DEBUG_PART_DECOMPOSITION_EXPLICIT						0
#define DEBUG_PART_DECOMPOSITION_EXIT							0
#define DEBUG_SYSTEM_DECOMPOSITION_PARALLEL						0
#define DEBUG_SYSTEM_DECOMPOSITION_SIMPLE						0
#define DEBUG_FLOW_IMPLICIT_FRICTION							0
#define DEBUG_PART_SIMULATE_STEP								0
#define DEBUG_PART_SIMULATE_STEP_EXIT							0
#define DEBUG_JUNCTION_FLOW_SCHEME								0
#define DEBUG_SYSTEM_SIMULATE_STEP_PARALLEL						0
#define DEBUG_SYSTEM_SIMULATE_STEP_SIMPLE						0
#define DEBUG_PART_SIMULATE_STEP2								0
#define DEBUG_PART_SIMULATE_STEP2_EXIT							0
#define DEBUG_SYSTEM_SIMULATE_STEP2_PARALLEL					0
#define DEBUG_SYSTEM_SIMULATE_STEP2_SIMPLE						0
#define DEBUG_FLOW_STEADY_ERROR									0
#define DEBUG_TRANSPORT_STEP_IMPLICIT							0
#define DEBUG_TRANSPORT_SIMULATE_STEP							0
#define DEBUG_JUNCTION_TRANSPORT_SCHEME							0
#define DEBUG_PART_TRANSPORT_STEP								0
#define DEBUG_SYSTEM_TRANSPORT_STEP_PARALLEL					0
#define DEBUG_SYSTEM_TRANSPORT_STEP_SIMPLE						0
#define DEBUG_WRITE_DATA										0
#define DEBUG_READ_DATA											0
#define DEBUG_WRITE_VARIABLES									0
#define DEBUG_READ_PROFILE										0
#define DEBUG_WRITE_PROFILE										0
#define DEBUG_WRITE_EVOLUTION									0
#define DEBUG_READ_EVOLUTION									0
#define DEBUG_WRITE_ADVANCES									0
#define DEBUG_WRITE_PLUMES_CHANNEL								0
#define DEBUG_WRITE_PLUMES										0
#define DEBUG_WRITE_CONTRIBUTIONS								0
#define DEBUG_SIMULATE_STEADY									0
#define DEBUG_SIMULATE_START									0
#define DEBUG_SIMULATE											0
#define DEBUG_DRAW												0
#define DEBUG_DRAW_GRAPHIC										0
#define DEBUG_DRAW_ANIMATION									0
#define DEBUG_SOLUTION_WRITE									0
#define DEBUG_PARAMETERS_OPEN									0
#define DEBUG_SIMULATION_OPEN									0
#define DEBUG_MAIN												0

// Macros to make inline functions

#define INLINE_POINT2_PRINT										1
#define INLINE_POINT2_COPY										1
#define INLINE_POINT2_OPEN										0
#define INLINE_POINT3_PRINT										1
#define INLINE_POINT3_COPY										1
#define INLINE_POINT3_OPEN										0
/* editor channel */
#define INLINE_SECTION_POINT_PRINT								1
#define INLINE_SECTION_POINT_COPY								1
#define INLINE_SECTION_POINT_OPEN								1
#define INLINE_SECTION_POINT2_PRINT								1
#define INLINE_SECTION_POINT2_COPY								1
#define INLINE_SECTION_POINT2_OPEN								1
/* editor channel */
#define INLINE_SECTION_POINT_TRANSFORM							1
#define INLINE_TRANSIENT_SECTION_PRINT							1
#define INLINE_TRANSIENT_SECTION_ERROR							0
#define INLINE_TRANSIENT_SECTION_DELETE							0
#define INLINE_TRANSIENT_SECTION_CREATE							1
#define INLINE_TRANSIENT_SECTION_COPY							1
#define INLINE_TRANSIENT_SECTION_TRANSFORM						0
#define INLINE_TRANSIENT_SECTION_OPEN_XML						1
#define INLINE_TRANSIENT_SECTION_SAVE_XML						1
#define INLINE_INITIAL_FLOW_PRINT								1
#define INLINE_INITIAL_FLOW_ERROR								0
#define INLINE_INITIAL_FLOW_DELETE								0
#define INLINE_INITIAL_FLOW_COPY								1
#define INLINE_INITIAL_FLOW_ORDER								1
#define INLINE_INITIAL_FLOW_OPEN_XML							1
#define INLINE_INITIAL_FLOW_SAVE_XML							1
#define INLINE_INITIAL_TRANSPORT_PRINT							1
#define INLINE_INITIAL_TRANSPORT_ERROR							0
#define INLINE_INITIAL_TRANSPORT_DELETE							0
#define INLINE_INITIAL_TRANSPORT_COPY							1
#define INLINE_INITIAL_TRANSPORT_ORDER							1
#define INLINE_INITIAL_TRANSPORT_OPEN_XML						1
#define INLINE_INITIAL_TRANSPORT_SAVE_XML						1
#define INLINE_CROSS_SECTION_PRINT								1
#define INLINE_CROSS_SECTION_ERROR								0
#define INLINE_CROSS_SECTION_DELETE								0
#define INLINE_CROSS_SECTION_CREATE								1
#define INLINE_CROSS_SECTION_COPY								1
#define INLINE_CROSS_SECTION_ORDER								1
#define INLINE_CROSS_SECTION_OPEN_XML							1
#define INLINE_CROSS_SECTION_SAVE_XML							1
#define INLINE_CROSS_SECTION_GET_TRANSIENT						0
#define INLINE_CHANNEL_GEOMETRY_PRINT							1
#define INLINE_CHANNEL_GEOMETRY_ERROR							0
#define INLINE_CHANNEL_GEOMETRY_DELETE_ACTUALIZE_X				1
#define INLINE_CHANNEL_GEOMETRY_DELETE_SECTION					1
#define INLINE_CHANNEL_GEOMETRY_INSERT_SECTION					1
#define INLINE_CHANNEL_GEOMETRY_DELETE							0
#define INLINE_CHANNEL_GEOMETRY_COPY							1
#define INLINE_CHANNEL_GEOMETRY_OPEN_XML						1
#define INLINE_CHANNEL_GEOMETRY_SAVE_XML						1
#define INLINE_BOUNDARY_FLOW_PRINT								1
#define INLINE_BOUNDARY_FLOW_ERROR								0
#define INLINE_BOUNDARY_FLOW_DELETE								0
#define INLINE_BOUNDARY_FLOW_COPY								1
#define INLINE_BOUNDARY_FLOW_OPEN_XML							1
#define INLINE_BOUNDARY_FLOW_SAVE_XML							1
#define INLINE_BOUNDARY_FLOW_PARAMETER							0
#define INLINE_BOUNDARY_FLOW_PARAMETER2							0
#define INLINE_BOUNDARY_FLOW_PARAMETER_INTEGRAL					0
#define INLINE_BOUNDARY_TRANSPORT_ERROR							0
#define INLINE_BOUNDARY_TRANSPORT_DELETE						0
#define INLINE_BOUNDARY_TRANSPORT_COPY							1
#define INLINE_BOUNDARY_TRANSPORT_OPEN_XML						1
#define INLINE_BOUNDARY_TRANSPORT_SAVE_XML						1
#define INLINE_BOUNDARY_TRANSPORT_PARAMETER						0
#define INLINE_TRANSPORT_PRINT									1
#define INLINE_TRANSPORT_ERROR									0
#define INLINE_TRANSPORT_DELETE									0
#define INLINE_TRANSPORT_CREATE									1
#define INLINE_TRANSPORT_COPY									1
#define INLINE_TRANSPORT_OPEN_XML								1
#define INLINE_TRANSPORT_SAVE_XML								1
#define INLINE_CHANNEL_TRANSPORT_PRINT							1
#define INLINE_CHANNEL_TRANSPORT_ERROR							0
#define INLINE_CHANNEL_TRANSPORT_DELETE_BT						1
#define INLINE_CHANNEL_TRANSPORT_INSERT_BT						1
#define INLINE_CHANNEL_TRANSPORT_DELETE							0
#define INLINE_CHANNEL_TRANSPORT_CREATE							1
#define INLINE_CHANNEL_TRANSPORT_COPY							1
#define INLINE_CHANNEL_TRANSPORT_PARSE_NODE						1
#define INLINE_CHANNEL_TRANSPORT_OPEN_XML						1
#define INLINE_CHANNEL_TRANSPORT_SAVE_XML						1
#define INLINE_CHANNEL_PRINT									1
#define INLINE_CHANNEL_ERROR									0
#define INLINE_CHANNEL_DELETE_BF								1
#define INLINE_CHANNEL_INSERT_BF								1
#define INLINE_CHANNEL_DELETE									0
#define INLINE_CHANNEL_COPY										1
#define INLINE_CHANNEL_BOUNDARY_TEST							1
#define INLINE_CHANNEL_PARSE_NODE								1
#define INLINE_CHANNEL_OPEN_XML									1
#define INLINE_CHANNEL_SAVE_XML									1
#define INLINE_SYSTEM_PRINT										1
#define INLINE_SYSTEM_ERROR										0
#define INLINE_SYSTEM_INIT										0
#define INLINE_SYSTEM_DELETE									0
#define INLINE_SYSTEM_COPY										1
#define INLINE_SYSTEM_CHANNEL_TRANSPORT_TEST					1
#define INLINE_SYSTEM_JUNCTIONS_TEST							1
#define INLINE_SYSTEM_CREATE									1
#define INLINE_SYSTEM_PARSE_NODE								1
#define INLINE_SYSTEM_OPEN_XML									1
#define INLINE_SYSTEM_SAVE_XML									1
#define INLINE_WAVE_VELOCITY									0
#define INLINE_SECTION_PARAMETERS_PRINT							1
#define INLINE_FRICTION_PARAMETERS_PRINT						1
#define INLINE_SECTION_PRINT									1
#define INLINE_SECTION_TRAPEZOIDAL_LEVEL						1
#define INLINE_SECTION_LEVEL									0
#define INLINE_SECTION_BETA										0
#define INLINE_SECTION_WIDTH									0
#define INLINE_SECTION_WIDTH_WITH_AREA							0
#define INLINE_SECTION_PERIMETER								0
#define INLINE_SECTION_PERIMETER_WITH_AREA						1
#define INLINE_SECTION_PERIMETER_WITH_DEPTH						1
#define INLINE_SECTION_AREA										0
#define INLINE_SECTION_AREA_WITH_DEPTH							0
#define INLINE_SECTION_WAVE_VELOCITY							0
#define INLINE_SECTION_CRITICAL_DISCHARGE						0
#define INLINE_SECTION_CRITICAL_FUNCTION						0
#define INLINE_SECTION_CRITICAL_AREA							1
#define INLINE_SECTION_DELETE									0
#define INLINE_SECTION_CREATE									0
#define INLINE_SECTION_COPY										0
#define INLINE_SECTION_BM										0
#define INLINE_SECTION_BL										1
#define INLINE_SECTION_BR										1
#define INLINE_SECTION_BC										1
#define INLINE_SECTION_B										0
#define INLINE_SECTION_P										1
#define INLINE_SECTION_RHPA										0
#define INLINE_SECTION_RHPB										0
#define INLINE_SECTION_RHPC										1
#define INLINE_SECTION_RHLA										1
#define INLINE_SECTION_RHLB										1
#define INLINE_SECTION_RHLC										0
#define INLINE_SECTION_RHA										0
#define INLINE_SECTION_RHB										0
#define INLINE_SECTION_RHC										0
#define INLINE_SECTION_RI										1
#define INLINE_SECTION_OPEN_PARAMETERS							0
#define INLINE_SECTION_OPEN										0
#define INLINE_CHANNEL_SEGMENT_PRINT							1
#define INLINE_CHANNEL_SEGMENT_DELETE							0
#define INLINE_CHANNEL_SEGMENT_OPEN_SECTION						0
#define INLINE_CHANNEL_SEGMENT_OPEN								0
#define INLINE_SECTION_CHANGES_PRINT							1
#define INLINE_SECTION_CHANGES_TMAX								1
#define INLINE_LIST_SECTION_CHANGES_PRINT						1
#define INLINE_LIST_SECTION_CHANGES_TMAX						0
#define INLINE_LIST_SECTION_CHANGES_OPEN						1
#define INLINE_SECTION_GAUGE_PRINT								1
#define INLINE_SECTION_GAUGE_TMAX								1
#define INLINE_LIST_SECTION_GAUGE_PRINT							1
#define INLINE_LIST_SECTION_GAUGE_TMAX							0
#define INLINE_LIST_SECTION_GAUGE_OPEN							1
#define INLINE_LIST_VARIABLE_SEGMENTS_OPEN						1
#define INLINE_PARAMETERS_PRINT									1
#define INLINE_MASS_START										0
#define INLINE_MASS_COPY										1
#define INLINE_FLOW_MASS										0
#define INLINE_FLOW_MASS_ERROR									1
#define INLINE_TRANSPORT_MASS									0
#define INLINE_TRANSPORT_MASS_ERROR								1
#define INLINE_TRANSPORT_VARIABLES_INTERPOLATE					1
#define INLINE_TRANSPORT_VARIABLES_OPEN							1
#define INLINE_VARIABLES_CREATE									0
#define INLINE_MESH_HMIN										0
#define INLINE_MESH_ACTUALIZE									1
#define INLINE_INITIAL_VARIABLES_OPEN							1
#define INLINE_PART_OPEN										0
#define INLINE_PART_OPEN_EXIT									0
#define INLINE_SORT_INT											1
#define INLINE_SORT_INVERSE_INT									1
#define INLINE_SYSTEM_LIST										1
#define INLINE_JUNCTION_PRINT									1
#define INLINE_JUNCTION_DELETE									0
#define INLINE_JUNCTION_CREATE									0
#define INLINE_JUNCTION_ADD_PARAMETER							0
#define INLINE_JUNCTION_ADD_INLET								0
#define INLINE_JUNCTION_ADD_OUTLET								0
#define INLINE_JUNCTION_FRONTAL_ADD_TRIBUTARY					0
#define INLINE_JUNCTION_SET_VOLUMES								0
#define INLINE_JUNCTIONS_DELETE									0
#define INLINE_JUNCTIONS_OPEN									0
#define INLINE_MESH_DELETE										1
#define INLINE_MESH_OPEN										0
#define INLINE_MODEL_FRICTION									1
#define INLINE_MODEL_DIFFUSION									1
#define INLINE_MODEL_VISCOSITY_TURBULENT						1
#define INLINE_TRANSPORT_PARAMETERS_SATURATION					1
#define INLINE_TRANSPORT_PARAMETERS_NODE						1
#define INLINE_TRANSPORT_PARAMETERS_CELL						1
#define INLINE_PARAMETERS_WAVE_VELOCITY							1
#define INLINE_PARAMETERS_NODE									1
#define INLINE_PARAMETERS_CELL									1
#define INLINE_FLOW_DRY_CORRECTION								1
#define INLINE_FLOWS											1
#define INLINE_CHANNEL_DRY_CORRECTION							0
#define INLINE_CHANNEL_DRY_CORRECTION_EXIT						0
#define INLINE_SYSTEM_DRY_CORRECTION_PARALLEL					1
#define INLINE_SYSTEM_DRY_CORRECTION_SIMPLE						1
#define INLINE_CHANGE_SECTIONS									1
#define INLINE_LIST_SECTION_GAUGE_STEP							0
#define INLINE_DIFFUSION_PARAMETERS_EXPLICIT_EXPLICIT			0
#define INLINE_DIFFUSION_PARAMETERS_EXPLICIT_IMPLICIT			0
#define INLINE_DIFFUSION_PARAMETERS_IMPLICIT_EXPLICIT			0
#define INLINE_TRANSPORT_SCHEME_PARAMETERS_UPWIND				1
#define INLINE_TRANSPORT_SCHEME_PARAMETERS_UPWIND2				1
#define INLINE_TRANSPORT_SCHEME_UPWIND							1
#define INLINE_TRANSPORT_SCHEME_TVD								1
#define INLINE_TRANSPORT_SCHEME_TVD2							1
#define INLINE_TRANSPORT_SCHEME_DIFFUSION						1
#define INLINE_TRANSPORT_SCHEME_CONTRIBUTIONS_UPWIND			0
#define INLINE_TRANSPORT_SCHEME_INLET_UPWIND					0
#define INLINE_TRANSPORT_SCHEME_OUTLET_UPWIND					0
#define INLINE_TRANSPORT_BOUNDARY								1
#define INLINE_PART_PARAMETERS									0
#define INLINE_PART_PARAMETERS_EXIT								0
#define INLINE_SYSTEM_PARAMETERS_PARALLEL						0
#define INLINE_SYSTEM_PARAMETERS_SIMPLE							0
#define INLINE_PART_PARAMETERS2									0
#define INLINE_PART_PARAMETERS2_EXIT							0
#define INLINE_BOUNDARY_FLOW_TMAX								0
#define INLINE_SYSTEM_PARAMETERS2_PARALLEL						0
#define INLINE_SYSTEM_PARAMETERS2_SIMPLE						0
#define INLINE_FLOW_LINEARIZATION								1
#define INLINE_VARIABLES_ACTUALIZE								0
#define INLINE_FLOW												1
#define INLINE_FLOW_WAVE_UPWIND									1
#define INLINE_FLOW_WAVE_UPWIND2								1
#define INLINE_FLOW_ENTROPY_CORRECTION							1
#define INLINE_FLOW_ENTROPY_WAVE								1
#define INLINE_FLOW_ENTROPY										1
#define INLINE_FLOW_PARAMETERS_UPWIND							1
#define INLINE_FLOW_PARAMETERS_UPWIND2							1
#define INLINE_FLOW_INNER_BOUNDARY								1
#define INLINE_FLOW_WAVE_DECOMPOSITION_UPWIND					1
#define INLINE_FLOW_WAVE_DECOMPOSITION							1
#define INLINE_FLOW_FRICTION_EXPLICIT							1
#define INLINE_FLOW_INLET_EXPLICIT								0
#define INLINE_FLOW_OUTLET_EXPLICIT								0
#define INLINE_PART_DECOMPOSITION_EXPLICIT						0
#define INLINE_PART_DECOMPOSITION_EXIT							0
#define INLINE_SYSTEM_DECOMPOSITION_PARALLEL					0
#define INLINE_SYSTEM_DECOMPOSITION_SIMPLE						0
#define INLINE_FLOW_IMPLICIT_FRICTION							1
#define INLINE_PART_SIMULATE_STEP								0
#define INLINE_JUNCTION_FLOW_SCHEME								0
#define INLINE_PART_SIMULATE_STEP_EXIT							0
#define INLINE_SYSTEM_SIMULATE_STEP_PARALLEL					0
#define INLINE_SYSTEM_SIMULATE_STEP_SIMPLE						0
#define INLINE_PART_SIMULATE_STEP2								0
#define INLINE_PART_SIMULATE_STEP2_EXIT							0
#define INLINE_SYSTEM_SIMULATE_STEP2_PARALLEL					0
#define INLINE_SYSTEM_SIMULATE_STEP2_SIMPLE						0
#define INLINE_FLOW_STEADY_ERROR								1
#define INLINE_TRANSPORT_STEP_IMPLICIT							1
#define INLINE_JUNCTION_TRANSPORT_SCHEME						0
#define INLINE_TRANSPORT_SIMULATE_STEP							1
#define INLINE_PART_TRANSPORT_STEP								0
#define INLINE_SYSTEM_TRANSPORT_STEP_PARALLEL					0
#define INLINE_SYSTEM_TRANSPORT_STEP_SIMPLE						0
#define INLINE_WRITE_DATA										0
#define INLINE_READ_DATA										0
#define INLINE_WRITE_VARIABLES									0
#define INLINE_READ_PROFILE										0
#define INLINE_WRITE_PROFILE									0
#define INLINE_WRITE_EVOLUTION									0
#define INLINE_READ_EVOLUTION									0
#define INLINE_WRITE_ADVANCES									0
#define INLINE_WRITE_PLUMES_CHANNEL								0
#define INLINE_WRITE_PLUMES										0
#define INLINE_WRITE_CONTRIBUTIONS								0
#define INLINE_SIMULATE_STEADY									1
#define INLINE_SIMULATE_START									0
#define INLINE_SIMULATE											0
#define INLINE_DRAW												0
#define INLINE_DRAW_GRAPHIC										0
#define INLINE_DRAW_ANIMATION									1
#define INLINE_SOLUTION_WRITE									1
#define INLINE_PARAMETERS_OPEN									1
#define INLINE_SIMULATION_OPEN									1
#define INLINE_MAIN												0

// Macros to define XML labels

#define XML_ADVANCES			(const xmlChar*)"advances"
#define XML_ANGLE				(const xmlChar*)"angle"
#define XML_BOUNDARY_TRANSPORT	(const xmlChar*)"boundary"
#define XML_CELL_SIZE	 		(const xmlChar*)"cell_size"
#define XML_CFL			 		(const xmlChar*)"cfl"
#define XML_CHANNEL				(const xmlChar*)"channel"
#define XML_CHANNEL_GEOMETRY	(const xmlChar*)"geometry"
#define XML_CHANNEL_TRANSPORT	(const xmlChar*)"transport"
#define XML_CONTRACTION 		(const xmlChar*)"contraction"
#define XML_CONTRIBUTIONS 		(const xmlChar*)"contributions"
#define XML_CONTROL		 		(const xmlChar*)"control"
#define XML_CROSS_SECTION		(const xmlChar*)"cross_section"
#define XML_DAM 		 		(const xmlChar*)"dam"
#define XML_DANGER 		 		(const xmlChar*)"danger"
#define XML_DELAY				(const xmlChar*)"delay"
#define XML_DEPTH				(const xmlChar*)"depth"
#define XML_DEPTH_MIN			(const xmlChar*)"depth_min"
#define XML_DISCHARGE			(const xmlChar*)"discharge"
#define XML_DRY					(const xmlChar*)"dry"
#define XML_DZ					(const xmlChar*)"dz"
#define XML_EVOLUTION		 	(const xmlChar*)"evolution"
#define XML_FINAL				(const xmlChar*)"final"
#define XML_FINAL_TIME			(const xmlChar*)"final_time"
//#define XML_FRONTAL				(const xmlChar*)"frontal"
#define XML_GATE				(const xmlChar*)"gate"
#define XML_GAUGE		 		(const xmlChar*)"gauge"
#define XML_GRANULOMETRIC_COEFFICIENT \
								(const xmlChar*)"granulometric_coefficient"
#define XML_H			 		(const xmlChar*)"h"
#define XML_HEIGHT		 		(const xmlChar*)"height"
#define XML_HERROR  		 	(const xmlChar*)"herror"
#define XML_HMAX				(const xmlChar*)"hmax"
#define XML_HT  		 		(const xmlChar*)"ht"
#define XML_HYDROGRAM	 		(const xmlChar*)"hydrogram"
#define XML_IMPLICIT_NUMBER		(const xmlChar*)"implicit"
#define XML_INFLUENCE			(const xmlChar*)"influence"
#define XML_INITIAL				(const xmlChar*)"initial"
#define XML_INITIAL_FLOW		(const xmlChar*)"initial"
#define XML_INITIAL_TIME		(const xmlChar*)"initial_time"
#define XML_INITIAL_TRANSPORT	(const xmlChar*)"initial"
#define XML_INLET_FLOW			(const xmlChar*)"inlet"
#define XML_INNER_FLOW			(const xmlChar*)"boundary"
#define XML_JUNCTION			(const xmlChar*)"junction"
#define XML_LEVEL  				(const xmlChar*)"level"
//#define XML_PARALLEL			(const xmlChar*)"parallel"
#define XML_M					(const xmlChar*)"m"
#define XML_MASS				(const xmlChar*)"mass"
#define XML_MAX_STEADY_TIME		(const xmlChar*)"max_steady_time"
#define XML_MEASURED_TIME 		(const xmlChar*)"measured_time"
#define XML_NAME				(const xmlChar*)"name"
#define XML_OBSERVATION_TIME	(const xmlChar*)"observation_time"
#define XML_OUTLET_FLOW			(const xmlChar*)"outlet"
#define XML_PARAMETERS			(const xmlChar*)"parameters"
#define XML_PIPE				(const xmlChar*)"pipe"
#define XML_PLUMES				(const xmlChar*)"plumes"
#define XML_POLILYNE			(const xmlChar*)"polilyne"
#define XML_PROFILE				(const xmlChar*)"profile"
#define XML_Q			 		(const xmlChar*)"q"
#define XML_Q_H 		 		(const xmlChar*)"q_h"
#define XML_Q_Z 		 		(const xmlChar*)"q_z"
#define XML_QERROR  		 	(const xmlChar*)"qerror"
#define XML_QH  		 		(const xmlChar*)"qh"
#define XML_QT  		 		(const xmlChar*)"qt"
#define XML_QT_HT		 		(const xmlChar*)"qt_ht"
#define XML_QT_ZT		 		(const xmlChar*)"qt_zt"
#define XML_QZ  		 		(const xmlChar*)"qz"
#define XML_ROUGHNESS			(const xmlChar*)"roughness"
#define XML_SECTION	 			(const xmlChar*)"section"
#define XML_SECTION_WIDTH_MIN	(const xmlChar*)"section_width_min"
//#define XML_SECTION_POINT 		(const xmlChar*)"section_point"
#define XML_SERROR  		 	(const xmlChar*)"serror"
#define XML_SIMULATE			(const xmlChar*)"simulate"
#define XML_SOLUBILITY			(const xmlChar*)"solubility"
#define XML_SOLUTION			(const xmlChar*)"solution"
#define XML_SOLUTION_FILE		(const xmlChar*)"solution_file"
#define XML_STEADY				(const xmlChar*)"steady"
#define XML_STEADY_ERROR		(const xmlChar*)"steady_error"
#define XML_STRAIGHT			(const xmlChar*)"straight"
#define XML_SUPERCRITICAL		(const xmlChar*)"supercritical"
#define XML_SYSTEM	 			(const xmlChar*)"system"
#define XML_TIME 				(const xmlChar*)"time"
#define XML_TOLERANCE			(const xmlChar*)"tolerance"
#define XML_TRANSIENT_SECTION 	(const xmlChar*)"transient_section"
#define XML_TRANSPORT			(const xmlChar*)"transport"
#define XML_TYPE				(const xmlChar*)"type"
#define XML_VELOCITY			(const xmlChar*)"velocity"
#define XML_WIDTH				(const xmlChar*)"width"
#define XML_X					(const xmlChar*)"x"
#define XML_XC					(const xmlChar*)"xc"
#define XML_XUH					(const xmlChar*)"xuh"
#define XML_XUZ					(const xmlChar*)"xuz"
#define XML_XQH					(const xmlChar*)"xqh"
#define XML_XQZ					(const xmlChar*)"xqz"
#define XML_Y					(const xmlChar*)"y"
#define XML_Z			 		(const xmlChar*)"z"
#define XML_ZT  		 		(const xmlChar*)"zt"

#endif
