/**
 * @file split_strategy.h
 * @brief A strategy for splitting a set of elements into two sets sorted on their bounding volumes according to a specific criterion.
 * @author Tomás Marques
 * @date 02-09-2024
 */

#pragma once

#include "core/geom/aabb.h"
#include "core/geom/axis.h"
#include "core/gl/gl.h"

namespace cobalt {
    namespace core::geom {
        /**
         * @brief A strategy to split a set of elements into two sets sorted on their bounding volumes according to a specific criterion.
         * @tparam ElementType The type of the elements in the array. Must be associated to a bounding volume (even if null).
         */
        template <typename ElementType>
        class SplitStrategy {
            public:
            virtual ~SplitStrategy() noexcept = default;

            /**
             * @brief Splits the elements into two sets.
             * @param elements The array of elements to split.
             * @return A pair containing the two sets of elements.
             */
            virtual std::pair<std::vector<ElementType>, std::vector<ElementType>> split(std::vector<ElementType> elements) const = 0;

            /**
             * @brief Gets the bounding volume for a specific element.
             * @return The bounding volume for the element.
             */
            virtual const AABB& getElementBounds(const ElementType& element) const noexcept = 0;
        };

        /**
         * @brief A strategy for splitting a set of elements into two sets sorted on the longest axis of their bounding volume.
         * @tparam ElementType The type of the elements in the array. Must be associated to a bounding volume (even if null).
         */
        template <typename ElementType>
        class LongestAxisSplitStrategy : public SplitStrategy<ElementType> {
            public:
            /**
             * @brief Splits the elements into two sets sorted on the longest axis of their combined bounding volume.
             * @param elements The array of elements to split.
             * @return A pair containing the two sets of elements.
             * @note You should extend this class and implement the getElementBounds method before instantiating it.
             */
            std::pair<std::vector<ElementType>, std::vector<ElementType>> split(std::vector<ElementType> elements) const override {
                if (elements.empty()) {
                    return {std::vector<ElementType>(), std::vector<ElementType>()};
                }

                AABB combinedBounds;
                for (auto element : elements) {
                    combinedBounds += this->getElementBounds(element);
                }

                glm::vec3 size = combinedBounds.getSize();
                Axis axis = size.x > size.y ? (size.x > size.z ? Axis::X : Axis::Z) : (size.y > size.z ? Axis::Y : Axis::Z);

                sortByAxis(elements, axis);

                size_t half = elements.size() / 2;
                return {std::vector<ElementType>(elements.begin(), elements.begin() + half),
                        std::vector<ElementType>(elements.begin() + half, elements.end())};
            }

            void sortByAxis(std::vector<ElementType>& elements, Axis axis) const {
                std::sort(elements.begin(), elements.end(), [this, axis](const ElementType& a, const ElementType& b) {
                    return this->getElementBounds(a).getCenter()[static_cast<size_t>(axis)] <
                           this->getElementBounds(b).getCenter()[static_cast<size_t>(axis)];
                });
            }
        };
    }  // namespace core::geom
}  // namespace cobalt
