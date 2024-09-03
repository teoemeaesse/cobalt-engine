/**
 * @file split_strategy.h
 * @brief A strategy for splitting a set of elements into two sets sorted on their bounding volumes according to a specific criterion.
 * @author Tomás Marques
 * @date 02-09-2024
 */

#pragma once

#include "core/geom/aabb.h"

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
            virtual Pair<Vector<ElementType*>, Vector<ElementType*>> split(Vector<ElementType*> elements) const = 0;

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
            Pair<Vector<ElementType*>, Vector<ElementType*>> split(Vector<ElementType*> elements) const override {
                if (elements.empty()) {
                    return {Vector<ElementType*>(), Vector<ElementType*>()};
                }

                AABB combinedBounds;
                for (ElementType* element : elements) {
                    combinedBounds += getElementBounds(*element);
                }

                glm::vec3 size = combinedBounds.getSize();
                Axis axis = size.x > size.y ? (size.x > size.z ? Axis::X : Axis::Z) : (size.y > size.z ? Axis::Y : Axis::Z);

                std::sort(elements.begin(), elements.end(), AABB::CompareAxis(axis));

                size_t half = elements.size() / 2;
                return {Vector<ElementType*>(elements.begin(), elements.begin() + half),
                        Vector<ElementType*>(elements.begin() + half, elements.end())};
            }

            const AABB& getElementBounds(const ElementType& element) const noexcept = 0;
        };
    }  // namespace core::geom
}  // namespace cobalt
