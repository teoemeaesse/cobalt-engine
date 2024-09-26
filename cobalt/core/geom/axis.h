/**
 * @file axis.h
 * @brief Axis-related utilities.
 * @author Tomás Marques
 * @date 24-09-2024
 */

#pragma once

namespace cobalt {
    namespace core::geom {
        /**
         * @brief The four main axes.
         */
        enum class Axis {
            X,  ///< The X axis.
            Y,  ///< The Y axis.
            Z,  ///< The Z axis.
            W,  ///< The W axis.
        };
    }  // namespace core::geom
}  // namespace cobalt