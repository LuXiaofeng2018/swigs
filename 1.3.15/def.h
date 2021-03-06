/*
SWIGS (Shallow Water in Irregular Geometries Simulator): a software to simulate
transient or steady flows with solute transport in channels, channel networks
and rivers.

Copyright 2005-2015 Javier Burguete Tolosa.

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
 * \file def.h
 * \brief Header file to define option macros to be used in the config.h file.
 * \authors Javier Burguete Tolosa.
 * \copyright Copyright 2005-2015 Javier Burguete Tolosa.
 */
#ifndef DEF__H
#define DEF__H 1

#include "jb/jb_def.h"

// Macros to select configuration options

/**
 * \def INTERFACE_SCIENTIFIC
 * \brief Macro to select a scientific interface (more accurate and more \
 *   advanced options).
 * \def INTERFACE_MARKET
 * \brief Macro to select a market interface (simpler and faster).
 * \def MESH_BOUNDARY_UNIFORM
 * \brief Macro to select uniform cell sizes at boundaries.
 * \def MESH_BOUNDARY_REDUCED
 * \brief Macro to select half sized cells at boundaries.
 * \def MODEL_FRICTION_SIMPLE
 * \brief Macro to select uniform velocity friction model on compound cross
 *   sections.
 * \def MODEL_FRICTION_CONSTANT_SLOPE
 * \brief Macro to select constant slope friction model on compound cross
 *   sections.
 * \def MODEL_FRICTION_MINIMIZATION_STRESS
 * \brief Macro to select minimization stress friction model on compound cross
 *   sections.
 * \def MODEL_FRICTION_MINIMIZATION_LOSS
 * \brief Macro to select minimization energy losses friction model on compound
 *   cross sections.
 * \def MODEL_FRICTION_STRESS_B
 * \brief Macro to select calculation of friction stress by width.
 * \def MODEL_FRICTION_STRESS_P
 * \brief Macro to select calculation of friction stress by wetted perimeter.
 * \def MODEL_PRESSURE_HYDROSTATIC
 * \brief Macro to select hydrostatic pressure model.
 * \def MODEL_PRESSURE_STRONG_SLOPE
 * \brief Macro to select strong slope pressure model.
 * \def MODEL_PRESSURE_HIGH_ORDER
 * \brief Macro to select high order pressure model.
 * \def MODEL_DIFFUSION_CONSTANT
 * \brief Macro to select constant solute diffusion model.
 * \def MODEL_DIFFUSION_B
 * \brief Macro to select width-based Rutherford solute diffusion model.
 * \def MODEL_DIFFUSION_H
 * \brief Macro to select depth-based Rutherford solute diffusion model.
 * \def MODEL_DIFFUSION_NULL
 * \brief Macro to select null solute diffusion model.
 * \def MODEL_VISCOSITY_NULL
 * \brief Macro to select null flow viscosity model.
 * \def MODEL_VISCOSITY_TURBULENT
 * \brief Macro to select turbulent flow viscosity model.
 * \def TMAX_POINT
 * \brief Macro to select maximum time step size by nodes.
 * \def TMAX_CELL
 * \brief Macro to select maximum time step size by intercells.
 * \def BOUNDARY_FLOW_EXTRAPOLATE
 * \brief Macro to select characteristic variables extrapolation method at flow
 *   boundaries.
 * \def BOUNDARY_FLOW_WAVE
 * \brief Macro to select null characteristic variables method at flow
 *   boundaries.
 * \def BOUNDARY_FLOW_LOCAL
 * \brief Macro to select local mass conservation method at flow boundaries.
 * \def BOUNDARY_FLOW_GLOBAL
 * \brief Macro to select global mass conservation method at flow boundaries.
 * \def FLOW_LINEARIZATION_ROE
 * \brief Macro to select the Roe's averages linearization.
 * \def FLOW_LINEARIZATION_SIMPLE
 * \brief Macro to select the arithmetical averages linearization.
 * \def FLOW_ENTROPY_CORRECTION_HARTEN
 * \brief Macro to select the Harten's entropy correction.
 * \def FLOW_ENTROPY_CORRECTION_MEAN_MAX
 * \brief Macro to select the mean-max entropy correction.
 * \def FLOW_ENTROPY_CORRECTION_MEAN_MEAN
 * \brief Macro to select the mean-mean entropy correction.
 * \def FLOW_ENTROPY_CORRECTION_NULL
 * \brief Macro to select a null entropy correction.
 * \def FLOW_ENTROPY_CORRECTION_INTERPOLATED_MAX
 * \brief Macro to select the interpolated-max entropy correction.
 * \def FLOW_ENTROPY_CORRECTION_INTERPOLATED_MEAN
 * \brief Macro to select the interpolated-mean entropy correction.
 * \def FLOW_ENTROPY_SCALAR
 * \brief Macro to select a scalar entropy fix.
 * \def FLOW_ENTROPY_CHARACTERISTIC
 * \brief Macro to select a characteristic matrix entropy fix.
 * \def TRANSPORT_DISCRETIZATION_SPLIT
 * \brief 
 * \def TRANSPORT_DISCRETIZATION_COUPLED
 * \brief 
 * \def FLUX_LIMITER_DISCRETIZATION_CONSERVATIVE
 * \brief 
 * \def FLUX_LIMITER_DISCRETIZATION_CHARACTERISTIC
 * \brief 
 * \def FLOW_FLUX_LIMITER_MINMOD
 * \brief 
 * \def FLOW_FLUX_LIMITER_VANALBADA
 * \brief 
 * \def FLOW_FLUX_LIMITER_VANLEER
 * \brief 
 * \def FLOW_FLUX_LIMITER_SUPERBEE
 * \brief 
 * \def FLOW_FLUX_LIMITER_NULL
 * \brief 
 * \def FLOW_FLUX_LIMITER_TOTAL
 * \brief 
 * \def FLOW_FLUX_LIMITER_CENTERED
 * \brief 
 * \def FLOW_FLUX_LIMITER_MONOTONIZED_CENTRAL
 * \brief 
 * \def TRANSPORT_FLUX_LIMITER_MINMOD
 * \brief 
 * \def TRANSPORT_FLUX_LIMITER_VANALBADA
 * \brief 
 * \def TRANSPORT_FLUX_LIMITER_VANLEER
 * \brief 
 * \def TRANSPORT_FLUX_LIMITER_SUPERBEE
 * \brief 
 * \def TRANSPORT_FLUX_LIMITER_NULL
 * \brief 
 * \def TRANSPORT_FLUX_LIMITER_TOTAL
 * \brief 
 * \def TRANSPORT_FLUX_LIMITER_CENTERED
 * \brief 
 * \def TRANSPORT_FLUX_LIMITER_MONOTONIZED_CENTRAL
 * \brief 
 * \def FLOW_WAVE_DECOMPOSITION_UPWIND
 * \brief 
 * \def FLOW_WAVE_DECOMPOSITION_TVD
 * \brief 
 * \def FLOW_WAVE_DECOMPOSITION_TVD2
 * \brief 
 * \def DIFFUSION_SCHEME_EXPLICIT
 * \brief 
 * \def DIFFUSION_SCHEME_IMPLICIT
 * \brief 
 * \def TRANSPORT_SCHEME_PARAMETERS_UPWIND
 * \brief 
 * \def TRANSPORT_SCHEME_PARAMETERS_UPWIND2
 * \brief 
 * \def TRANSPORT_SCHEME_UPWIND
 * \brief 
 * \def TRANSPORT_SCHEME_TVD
 * \brief 
 * \def TRANSPORT_SCHEME_TVD2
 * \brief 
 * \def FRICTION_EXPLICIT_POINTWISE
 * \brief 
 * \def FRICTION_EXPLICIT_UPWIND
 * \brief 
 */
#define INTERFACE_SCIENTIFIC	1
#define INTERFACE_MARKET		2
#define MESH_BOUNDARY_UNIFORM	1
#define MESH_BOUNDARY_REDUCED	2
#define MODEL_FRICTION_SIMPLE				1
#define MODEL_FRICTION_CONSTANT_SLOPE		2
#define MODEL_FRICTION_MINIMIZATION_STRESS	3
#define MODEL_FRICTION_MINIMIZATION_LOSS	4
#define MODEL_FRICTION_STRESS_B	1
#define MODEL_FRICTION_STRESS_P	2
#define MODEL_PRESSURE_HYDROSTATIC	1
#define MODEL_PRESSURE_STRONG_SLOPE	2
#define MODEL_PRESSURE_HIGH_ORDER	3
#define MODEL_DIFFUSION_CONSTANT	1
#define MODEL_DIFFUSION_B			2
#define MODEL_DIFFUSION_H			3
#define MODEL_DIFFUSION_NULL		4
#define MODEL_VISCOSITY_NULL		1
#define MODEL_VISCOSITY_TURBULENT	2
#define TMAX_POINT	1
#define TMAX_CELL	2
#define BOUNDARY_FLOW_EXTRAPOLATE	1
#define BOUNDARY_FLOW_WAVE			2
#define BOUNDARY_FLOW_LOCAL			3
#define BOUNDARY_FLOW_GLOBAL		4
#define FLOW_LINEARIZATION_ROE		1
#define FLOW_LINEARIZATION_SIMPLE	2
#define FLOW_ENTROPY_CORRECTION_HARTEN				1
#define FLOW_ENTROPY_CORRECTION_MEAN_MAX			2
#define FLOW_ENTROPY_CORRECTION_MEAN_MEAN			3
#define FLOW_ENTROPY_CORRECTION_NULL				4
#define FLOW_ENTROPY_CORRECTION_INTERPOLATED_MAX	5
#define FLOW_ENTROPY_CORRECTION_INTERPOLATED_MEAN	6
#define FLOW_ENTROPY_SCALAR			1
#define FLOW_ENTROPY_CHARACTERISTIC	1
#define TRANSPORT_DISCRETIZATION_SPLIT		1
#define TRANSPORT_DISCRETIZATION_COUPLED	2
#define FLUX_LIMITER_DISCRETIZATION_CONSERVATIVE	1
#define FLUX_LIMITER_DISCRETIZATION_CHARACTERISTIC	2
#define FLOW_FLUX_LIMITER_MINMOD				1
#define FLOW_FLUX_LIMITER_VANALBADA				2
#define FLOW_FLUX_LIMITER_VANLEER				3
#define FLOW_FLUX_LIMITER_SUPERBEE				4
#define FLOW_FLUX_LIMITER_NULL					5
#define FLOW_FLUX_LIMITER_TOTAL					6
#define FLOW_FLUX_LIMITER_CENTERED				7
#define FLOW_FLUX_LIMITER_MONOTONIZED_CENTRAL	8
#define TRANSPORT_FLUX_LIMITER_MINMOD				1
#define TRANSPORT_FLUX_LIMITER_VANALBADA			2
#define TRANSPORT_FLUX_LIMITER_VANLEER				3
#define TRANSPORT_FLUX_LIMITER_SUPERBEE				4
#define TRANSPORT_FLUX_LIMITER_NULL					5
#define TRANSPORT_FLUX_LIMITER_TOTAL				6
#define TRANSPORT_FLUX_LIMITER_CENTERED				7
#define TRANSPORT_FLUX_LIMITER_MONOTONIZED_CENTRAL	8
#define FLOW_WAVE_DECOMPOSITION_UPWIND	1
#define FLOW_WAVE_DECOMPOSITION_TVD		2
#define FLOW_WAVE_DECOMPOSITION_TVD2	3
#define DIFFUSION_SCHEME_EXPLICIT	1
#define DIFFUSION_SCHEME_IMPLICIT	2
#define TRANSPORT_SCHEME_PARAMETERS_UPWIND	1
#define TRANSPORT_SCHEME_PARAMETERS_UPWIND2	2
#define TRANSPORT_SCHEME_UPWIND	1
#define TRANSPORT_SCHEME_TVD	2
#define TRANSPORT_SCHEME_TVD2	3
#define FRICTION_EXPLICIT_POINTWISE	1
#define FRICTION_EXPLICIT_UPWIND	2

#include "config.h"

// Checking configuration options

#if INTERFACE<1 || INTERFACE>2
#error "Unknown interface"
#endif

#if MESH_BOUNDARY<1 || MESH_BOUNDARY>2
#error "Unknown boundary mesh"
#endif

#if MODEL_FRICTION<1 || MODEL_FRICTION>4
#error "Unknown friction model"
#endif

#if MODEL_FRICTION_STRESS<1 || MODEL_FRICTION_STRESS>2
#error "Unknown friction stress model"
#endif

#if MODEL_PRESSURE<1 || MODEL_PRESSURE>2
#error "Unknown pressure model"
#endif

#if MODEL_DIFFUSION<1 || MODEL_DIFFUSION>4
#error "Unknown diffusion model"
#endif

#if MODEL_VISCOSITY<1 || MODEL_VISCOSITY>2
#error "Unknown viscosity model"
#endif

#if TMAX<1 || TMAX>2
#error "Unknown tmax"
#endif

#if BOUNDARY_FLOW<1 || BOUNDARY_FLOW>4
#error "Unknown flow boundary condition"
#endif

#if FLOW_LINEARIZATION<1 || FLOW_LINEARIZATION>2
#error "Unknown flow linearization"
#endif

#if FLOW_ENTROPY_CORRECTION<1 || FLOW_ENTROPY_CORRECTION>4
#error "Unknown flow entropy correction"
#endif

#if FLOW_ENTROPY<1 || FLOW_ENTROPY>2
#error "Unknown flow entropy"
#endif

#if TRANSPORT_DISCRETIZATION<1 || TRANSPORT_DISCRETIZATION>2
#error "Unknown transport discretization"
#endif

#if TRANSPORT_SCHEME == TRANSPORT_SCHEME_UPWIND
#define transport_scheme transport_scheme_upwind
#elif TRANSPORT_SCHEME == TRANSPORT_SCHEME_TVD
#define transport_scheme transport_scheme_tvd
#elif TRANSPORT_SCHEME == TRANSPORT_SCHEME_TVD2
#define transport_scheme transport_scheme_tvd2
#else
#error "Unknown transport scheme"
#endif

#if FLUX_LIMITER_DISCRETIZATION<1 || FLUX_LIMITER_DISCRETIZATION>2
#error "Unknown flux limiter discretization"
#endif

#if FLOW_FLUX_LIMITER == FLOW_FLUX_LIMITER_MINMOD
#define flow_flux_limiter jbm_flux_limiter_minmod
#elif FLOW_FLUX_LIMITER == FLOW_FLUX_LIMITER_VANALBADA
#define flow_flux_limiter jbm_flux_limiter_VanAlbada
#elif FLOW_FLUX_LIMITER == FLOW_FLUX_LIMITER_VANLEER
#define flow_flux_limiter jbm_flux_limiter_VanLeer
#elif FLOW_FLUX_LIMITER == FLOW_FLUX_LIMITER_SUPERBEE
#define flow_flux_limiter jbm_flux_limiter_superbee
#elif FLOW_FLUX_LIMITER == FLOW_FLUX_LIMITER_NULL
#define flow_flux_limiter jbm_flux_limiter_null
#elif FLOW_FLUX_LIMITER == FLOW_FLUX_LIMITER_TOTAL
#define flow_flux_limiter jbm_flux_limiter_total
#elif FLOW_FLUX_LIMITER == FLOW_FLUX_LIMITER_CENTERED
#define flow_flux_limiter jbm_flux_limiter_centered
#elif FLOW_FLUX_LIMITER == FLOW_FLUX_LIMITER_MONOTONIZED_CENTRAL
#define flow_flux_limiter jbm_flux_limiter_monotonized_central
#else
#error "Unknown flow limiter"
#endif

#if TRANSPORT_FLUX_LIMITER == TRANSPORT_FLUX_LIMITER_SUPERBEE
#define transport_flux_limiter jbm_flux_limiter_superbee
#elif TRANSPORT_FLUX_LIMITER == TRANSPORT_FLUX_LIMITER_VANLEER
#define transport_flux_limiter jbm_flux_limiter_VanLeer
#elif TRANSPORT_FLUX_LIMITER == TRANSPORT_FLUX_LIMITER_VANALBADA
#define transport_flux_limiter jbm_flux_limiter_VanAlbada
#elif TRANSPORT_FLUX_LIMITER == TRANSPORT_FLUX_LIMITER_MINMOD
#define transport_flux_limiter jbm_flux_limiter_minmod
#elif TRANSPORT_FLUX_LIMITER == TRANSPORT_FLUX_LIMITER_NULL
#define transport_flux_limiter jbm_flux_limiter_null
#elif TRANSPORT_FLUX_LIMITER == TRANSPORT_FLUX_LIMITER_TOTAL
#define transport_flux_limiter jbm_flux_limiter_total
#elif TRANSPORT_FLUX_LIMITER == TRANSPORT_FLUX_LIMITER_CENTERED
#define transport_flux_limiter jbm_flux_limiter_centered
#elif TRANSPORT_FLUX_LIMITER == TRANSPORT_FLUX_LIMITER_MONOTONIZED_CENTRAL
#define transport_flux_limiter jbm_flux_limiter_monotonized_central
#else
#error "Unknown transport flux limiter"
#endif

#if FLOW_WAVE_DECOMPOSITION<1 || FLOW_WAVE_DECOMPOSITION>3
#error "Unknown flow wave decomposition"
#endif

#if DIFFUSION_SCHEME<1 || DIFFUSION_SCHEME>2
#error "Unknown diffusion scheme"
#endif

#if TRANSPORT_SCHEME_PARAMETERS<1 || TRANSPORT_SCHEME_PARAMETERS>2
#error "Unknown transport scheme parameters"
#endif

#if TRANSPORT_SCHEME<1 || TRANSPORT_SCHEME>3
#error "Unknown transport scheme"
#endif

#if FRICTION_EXPLICIT<1 || FRICTION_EXPLICIT>2
#error "Unknown friction explicit"
#endif

extern char *message;

#endif
